/**
 * \file
 *
 * \brief Persistent Storage implementation.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include <nv_storage.h>
#include <nv.h>
#include <utils.h>
#include <nv_storage_config.h>
#include <string.h>
#include <utils_assert.h>

#define SECTOR_SIGNATURE "STORAGE"

COMPILER_PACK_SET(1)

/**
 * \brief Sector header, located at sector start.
 */
struct sector_header {
	/*!< Activity flag. Active sector has it set to 0. */
	uint8_t active;
	/*!< Number of the sector. Sector with largest number is used. */
	uint32_t number;
	/*!< Sector signature, to prevent occasional sector recognition as active. */
	uint8_t signature[7];
};

/**
 * \brief Block header, located before each block of item data.
 */
struct block_header {
	/*!< Activity flag. Active block has it set to 0. */
	uint16_t active;
	/*!< Id of stored item. */
	uint16_t id;
	/*!< Offset of data within item. */
	uint16_t offset;
	/*!< The size of data in this block. */
	uint16_t block_size;
	/*!< The size of the whole item. */
	uint16_t item_size;
	/*!< Location of previous block in nv-memory. */
	uint16_t prev_block;
	/*!< Checksum of the header excluding "active" field. */
	uint16_t checksum;
};
COMPILER_PACK_RESET()

/**
 * \internal Item structure for faster search of item
 */
struct nv_item {
	/*!< Id of an item. */
	uint16_t id;
	/*!< Location of the last written block of this item. */
	uint16_t last_block;
};

/**
 * \brief Internal helper structure grouping static variable in one
 */
struct nv_storage_memory {
	/*!< The pointer to the top of a sector.
	     Location at which next writing operation starts. */
	uint16_t pow;
	/*!< Array of item, for quick search. */
	struct nv_item items[CONF_MAX_ITEM_NUMBER];
	/*!< The amount of stored items. */
	uint16_t items_amount;
	/*!< The number of active sector. */
	uint8_t active_sector;
};

#define NV_SECTOR_END(sector_num) ((CONF_STORAGE_MEMORY_START) + ((sector_num + 1) * CONF_SECTOR_SIZE) - 1)

static struct nv_storage_memory mem;

static bool            create_sector(const uint8_t sector, const uint32_t number, const bool activate);
static void            load_data_from_sector(const uint8_t number);
static bool            write_and_verify(const uint8_t sector, const uint16_t offset, const uint8_t *const data,
                                        const uint16_t size);
static struct nv_item *find_item(const uint16_t id);
static uint16_t        calculate_block_header_checksum(struct block_header *header);
static bool            copy_data_to_new_sector(void);
static bool            collect_item_data(const struct nv_item *const item, uint8_t *const data, const uint16_t offset,
                                         const uint16_t size);
static bool            write_block_header(const struct block_header *const header);
static bool            activate_block_header(const uint16_t size);
static inline void     fill_block_header(struct block_header *const header, const uint16_t id, const uint16_t offset,
                                         const uint16_t block_size, const uint16_t item_size, const uint16_t prev_block);
static bool            copy_sector_if_needed(const uint16_t size);
static int32_t         copy_item_to_new_sector(const uint16_t item, const uint8_t sector, const uint16_t pow);

/**
 * \brief Initialize persistent storage
 */
void nv_storage_init(void)
{
	uint8_t              sector = 0, last_sector = 0xFF;
	struct sector_header header;
	uint32_t             last_sector_number = 0;

	/* Look for last (smallest value) active sector */
	for (; sector < SECTOR_AMOUNT; sector++) {
		nv_read(sector, 0, (uint8_t *)&header, sizeof(struct sector_header));
		if ((header.active == 0) && (memcmp(header.signature, SECTOR_SIGNATURE, 7) == 0)) {
			if (header.number >= last_sector_number) {
				last_sector_number = header.number;
				last_sector        = sector;
			}
		}
	}
	/* No active/valid sector found. Try to create one. */
	if (last_sector == 0xFF) {
		for (sector = 0; sector < SECTOR_AMOUNT; sector++) {
			if (create_sector(sector, last_sector_number + 1, true)) {
				return;
			}
		}
		/* No sector was initialized */
		if (sector == SECTOR_AMOUNT) {
			ASSERT(false);
			return;
		}
	}

	mem.active_sector = last_sector;
	/* There is an active sector, load data from it */
	load_data_from_sector(mem.active_sector);
}

/**
 * \brief Write an item to the persistent storage
 */
int32_t nv_storage_write(const uint16_t id, const uint16_t offset, const uint8_t *const data, const uint16_t size)
{
	struct nv_item *    item;
	struct block_header header;
	uint16_t            last_block;

	ASSERT(data && size && id);

	if (!copy_sector_if_needed(sizeof(struct block_header) + size)) {
		ASSERT(false);
		return ERR_FAILURE;
	}

	item = find_item(id);
	/* Fill the block header */
	if (!item) {
		fill_block_header(&header, id, 0, size, size, 0);
	} else {
		nv_read(mem.active_sector, item->last_block, (uint8_t *)&header, sizeof(struct block_header));
		fill_block_header(&header, id, offset, size, header.item_size, item->last_block);
		/* Trying to write more data than fits or outside of the item */
		if (((uint32_t)offset + (uint32_t)size) > header.item_size) {
			return ERR_WRONG_LENGTH;
		}
	}

	last_block = mem.pow;

	if (!write_block_header(&header)) {
		return ERR_FAILURE;
	}
	/*  Write data */
	if (!write_and_verify(mem.active_sector, mem.pow + sizeof(struct block_header), data, size)) {
		mem.pow += sizeof(struct block_header) + size;
		mem.pow = nv_align_next_access_address(mem.pow, BLOCK_WITH_DATA_ALIGNMENT);

		return ERR_FAILURE;
	}
	if (!activate_block_header(size)) {
		return ERR_FAILURE;
	}

	mem.pow += sizeof(struct block_header) + size;
	mem.pow = nv_align_next_access_address(mem.pow, BLOCK_WITH_DATA_ALIGNMENT);

	/* Update information stored in RAM for newly created items */
	if (!item) {
		item     = &mem.items[mem.items_amount++];
		item->id = id;
	}
	item->last_block = last_block;

	return ERR_NONE;
}

/**
 * \brief Read an item from the persistent storage
 */
int32_t nv_storage_read(const uint16_t id, const uint16_t offset, uint8_t *const data, const uint16_t size)
{
	struct nv_item *    item;
	struct block_header header;

	ASSERT(data && size && id);

	item = find_item(id);
	if (!item) {
		return ERR_NOT_FOUND;
	}

	nv_read(mem.active_sector, item->last_block, (uint8_t *)&header, sizeof(struct block_header));
	if (((uint32_t)size + (uint32_t)offset) > header.item_size) {
		return ERR_WRONG_LENGTH;
	}

	if (!collect_item_data(item, data, offset, size)) {
		return ERR_FAILURE;
	}

	return ERR_NONE;
}

/**
 * \brief Retrieve the size of the given item
 */
uint16_t nv_storage_item_size(const uint16_t id)
{
	struct nv_item *    item;
	struct block_header header;

	ASSERT(id);

	item = find_item(id);
	if (item) {
		nv_read(mem.active_sector, item->last_block, (uint8_t *)&header, sizeof(struct block_header));

		return header.item_size;
	}

	return 0;
}

/**
 * \brief Delete an item from the persistent storage
 */
int32_t nv_storage_delete(const uint16_t id)
{
	struct nv_item *    item;
	struct block_header header;

	ASSERT(id);

	if (!copy_sector_if_needed(sizeof(struct block_header))) {
		ASSERT(false);
		return ERR_FAILURE;
	}

	item = find_item(id);
	if (item) {
		/* Delete at item by writing its header with size of zero */
		fill_block_header(&header, id, 0, 0, 0, 0);

		if (!write_block_header(&header)) {
			return ERR_FAILURE;
		}
		if (!activate_block_header(0)) {
			return ERR_FAILURE;
		}

		mem.pow += sizeof(struct block_header);
		mem.pow = nv_align_next_access_address(mem.pow, BLOCK_WITH_DATA_ALIGNMENT);
		*item   = mem.items[--mem.items_amount];

		return ERR_NONE;
	}

	return ERR_NOT_FOUND;
}

/**
 * \brief Delete all the items in the persistent storage
 */
int32_t nv_storage_erase_all(void)
{
	uint8_t i = 0;

	for (; i < SECTOR_AMOUNT; i++) {
		nv_erase_sector(i);
	}

	return ERR_NONE;
}

/**
 * \brief Check whether an item with given ID exists in the persistent storage
 */
bool nv_storage_item_exists(const uint16_t id)
{
	ASSERT(id);

	return (find_item(id) != NULL);
}

/**
 * \brief Force storage areas swapping.
 */
void nv_storage_force_packing(void)
{
	copy_data_to_new_sector();
}

/**
 * \brief Retrieve the amount of space left in storage
 *
 */
uint16_t nv_storage_space_left(void)
{
	return CONF_SECTOR_SIZE - mem.pow;
}

/**
 * \brief Create new sector with given number
 *
 * \param[in] sector The number of a sector in NV memory
 * \param[in] number The number of sector to store in sector's header
 * \param[in] activate Activate created sector
 *
 * \return True if sector was successfully created, otherwise false
 */
static bool create_sector(const uint8_t sector, const uint32_t number, const bool activate)
{
	struct sector_header header;
	uint8_t              active = 0;

	/* Make sure to erase the whole sector */
	if (!nv_is_empty(sector, 0, CONF_SECTOR_SIZE)) {
		nv_erase_sector(sector);
		if (!nv_is_empty(sector, 0, CONF_SECTOR_SIZE)) {
			return false;
		}
	}

	/* Fill and write inactive sector header firstly */
	memcpy(header.signature, SECTOR_SIGNATURE, 7);
	header.active = 0xFF;
	header.number = number;

	if (!write_and_verify(sector, 0, (uint8_t *)&header, sizeof(struct sector_header))) {
		return false;
	}
	if (activate) {
		/* Activate the sector */
		if (!write_and_verify(sector, 0, &active, sizeof(active))) {
			return false;
		}

		mem.pow           = sizeof(struct sector_header);
		mem.pow           = nv_align_next_access_address(mem.pow, SECTOR_HEADER_ALIGNMENT);
		mem.active_sector = sector;
	}

	return true;
}

/**
 * \brief Loads stored data from the given sector
 *
 * \param[in] number The number of the sector to load data from
 */
static void load_data_from_sector(const uint8_t number)
{
	struct block_header header;
	uint32_t            address;

	mem.pow = nv_align_next_access_address(sizeof(struct sector_header), SECTOR_HEADER_ALIGNMENT);
	while (true) {
		uint8_t i;

		nv_read(number, mem.pow, (uint8_t *)&header, sizeof(struct block_header));
		/* Check whether block header is empty */
		for (i = 0; i < sizeof(struct block_header); i++) {
			if (((uint8_t *)&header)[i] != 0xFF) {
				break;
			}
		}
		if (i == sizeof(struct block_header)) {
			break; /* Empty sector */
		} else if (header.checksum != calculate_block_header_checksum(&header)) {
			/* Invalid header, skip it */
			mem.pow = nv_align_next_access_address(mem.pow + sizeof(struct block_header), BLOCK_WITH_DATA_ALIGNMENT);
		} else if (header.active) {
			/* The block is not active */
			mem.pow += sizeof(struct block_header) + header.block_size;
			mem.pow = nv_align_next_access_address(mem.pow, BLOCK_WITH_DATA_ALIGNMENT);
		} else {
			struct nv_item *item = find_item(header.id);

			if (!item) {
				item     = &mem.items[mem.items_amount++];
				item->id = header.id;
			}
			/* Item was deleted, remove information about it */
			if (header.item_size == 0) {
				*item = mem.items[--mem.items_amount];
			}

			item->last_block = mem.pow;
			mem.pow += sizeof(struct block_header) + header.block_size;
			mem.pow = nv_align_next_access_address(mem.pow, BLOCK_WITH_DATA_ALIGNMENT);

			address = CONF_STORAGE_MEMORY_START + number * CONF_SECTOR_SIZE + mem.pow;
			if (address >= NV_SECTOR_END(number)) {
				break;
			}
		}
	}
}

/**
 * \brief Write data to the persistent storage and verify that writing was
 *        successful
 *
 * \param[in] sector Sector of the storage to read from
 * \param[in] offset The offset inside the sector to start reading from
 * \param[in] data Data buffer to read data to
 * \param[in] size The size of the data buffer
 *
 * \return True if written data matches the given data, otherwise false
 */
static bool write_and_verify(const uint8_t sector, const uint16_t offset, const uint8_t *const data,
                             const uint16_t size)
{
	nv_write(sector, offset, data, size);
	if (!nv_is_equal(sector, offset, data, size)) {
		return false;
	}

	return true;
}

/**
 * \brief Look for item with the given ID
 *
 * \param[in] ID ID of the item it is required to fins
 *
 * \return Pointer to found item, or NULL
 */
static struct nv_item *find_item(const uint16_t id)
{
	uint16_t i = 0;

	for (; i < mem.items_amount; i++) {
		if (mem.items[i].id == id) {
			return &mem.items[i];
		}
	}
	return NULL;
}

/**
 * \brief Calculate checksum of the given array
 *
 * \param[in] header The pointer to block header to calculate checksum of
 *
 * \return Checksum of a block header
 */
static uint16_t calculate_block_header_checksum(struct block_header *header)
{
	uint8_t *tmp = (uint8_t *)header + sizeof(header->active);
	uint16_t crc = 0xFFFF;
	uint8_t  i   = 0;

	for (; i < sizeof(struct block_header) - sizeof(header->active) - sizeof(header->checksum); i++) {
		uint8_t value;

		value = (uint8_t)((crc >> 8) ^ tmp[i]);
		value = value ^ (value >> 4);
		crc   = (crc << 8) ^ ((uint16_t)value << 12) ^ ((uint16_t)value << 5) ^ (uint16_t)value;
	}
	return crc;
}

/**
 * \brief Copy data to empty storage, performing item compressing on the way
 *
 * \return True if copying succeeds, otherwise false
 */
static bool copy_data_to_new_sector(void)
{
	uint8_t              sector = mem.active_sector;
	struct sector_header sector_header;
	uint32_t             number;
	uint16_t             i       = 0;
	uint16_t             new_pow = nv_align_next_access_address(sizeof(struct sector_header), SECTOR_HEADER_ALIGNMENT);
	const uint8_t        active  = 0;

	nv_read(mem.active_sector, 0, (uint8_t *)&sector_header, sizeof(struct sector_header));
	number = sector_header.number + 1;

	/* Look for new sector to store items */
	do {
		if (++sector >= SECTOR_AMOUNT) {
			sector = 0;
		}
		if (sector == mem.active_sector) {
			/* Could not initialize a sector */
			return false;
		}
	} while (!create_sector(sector, number, false));

	/* Cycle through all the items */
	for (; i < mem.items_amount; i++) {
		int32_t result = copy_item_to_new_sector(i, sector, new_pow);

		if (-1 == result) {
			return false;
		} else {
			/* After successful write, update item information in RAM */
			mem.items[i].last_block = new_pow;
			new_pow += result + sizeof(struct block_header);
			new_pow = nv_align_next_access_address(new_pow, BLOCK_WITH_DATA_ALIGNMENT);
		}
	}
	/* Activate sector */
	if (!write_and_verify(sector, 0, &active, sizeof(uint8_t))) {
		return false;
	}
	/* Erase previously active sector */
	nv_erase_sector(mem.active_sector);
	/* Update information about active sector and point-of-write */
	mem.pow           = new_pow;
	mem.active_sector = sector;

	return true;
}

/**
 * \brief Collect items data into one buffer
 *
 * \param[in] item The item data is collected for
 * \param[in] data The buffer to collect item data to
 * \param[in] offset The offset inside item's data to start collecting from
 * \param[in] size The size of data to collect
 *
 * \return True if copying succeeds, otherwise false
 */
static bool collect_item_data(const struct nv_item *const item, uint8_t *const data, const uint16_t offset,
                              const uint16_t size)
{
	uint16_t            start = offset, end = offset + size;
	uint16_t            current_block      = item->last_block;
	uint16_t            destination_offset = 0;
	struct block_header header;

	/* Need to gather item data between offset and offset + size.
	   Start with the latest written block and check if it contains required
	   data. Keep going to previous blocks until all the data is collected. */
	while (start != end) {
		uint16_t bytes_to_read;
		uint16_t block_end;
		uint16_t por;

		/* Find block which contains the first bytes it is required to read */
		while (42) {
			/* Get the header of current block */
			nv_read(mem.active_sector, current_block, (uint8_t *)&header, sizeof(struct block_header));
			block_end = header.offset + header.block_size;
			/* NV memory is corrupted */
			if (current_block == 0) {
				return false;
			}
			/* Check if current block has no required data */
			if ((start >= block_end) || (end <= header.offset)) {
				/* Just continue the loop */
			} else if (start < header.offset) {
				/* This block contains some bytes of the required data,
				   but not the first bytes */
				end = header.offset;
			} else {
				break; /* This block contains first bytes */
			}
			current_block = header.prev_block;
		}

		por = current_block + sizeof(struct block_header) + start - header.offset;
		if (block_end < end) {
			/* This is the case when none of the blocks above contain new
			   "first bytes". Thus, we go further down in block chain */
			bytes_to_read = block_end - start;
			current_block = header.prev_block;
		} else {
			/* One of the blocks above (newer) contains new "first bytes". Need
			   to start scanning all over */
			bytes_to_read = end - start;
			current_block = item->last_block;
			end           = offset + size;
		}
		/* Read the data from the block found above */
		nv_read(mem.active_sector, por, data + destination_offset, bytes_to_read);
		/* Adjust starting point of read and
		   start looking for "first bytes" again */
		start += bytes_to_read;
		destination_offset += bytes_to_read;
	}

	return true;
}

/**
 * \brief Write block header to nv memory
 *
 * \param[in] header The header to write
 *
 * \return True if writing succeeds, otherwise false
 */
static bool write_block_header(const struct block_header *const header)
{
	if (!write_and_verify(mem.active_sector, mem.pow, (const uint8_t *const)header, sizeof(struct block_header))) {
		if (!nv_is_empty(mem.active_sector, mem.pow, sizeof(struct block_header))) {
			mem.pow = nv_align_next_access_address(mem.pow + sizeof(struct block_header), BLOCK_WITH_DATA_ALIGNMENT);
		}
		return false;
	}

	return true;
}

/**
 * \brief Activate block header to nv memory
 *
 * \param[in] size The size of written block
 *
 * \return True if writing succeeds, otherwise false
 */
static bool activate_block_header(const uint16_t size)
{
	uint16_t active = 0;

	if (!write_and_verify(mem.active_sector, mem.pow, (uint8_t *)&active, sizeof(active))) {
		mem.pow += sizeof(struct block_header) + size;
		mem.pow = nv_align_next_access_address(mem.pow, BLOCK_WITH_DATA_ALIGNMENT);

		return false;
	}

	return true;
}

/**
 * \brief Fill block header
 *
 * \param[out] header The header to fill
 * \param[in] id Item ID
 * \param[in] offset Offset inside item
 * \param[in] block_size Size of block within an item
 * \param[in] item_size The size of an item
 * \param[in] prev_block Previous written block
 *
 * \return True if writing succeeds, otherwise false
 */
static inline void fill_block_header(struct block_header *const header, const uint16_t id, const uint16_t offset,
                                     const uint16_t block_size, const uint16_t item_size, const uint16_t prev_block)
{
	header->active     = 0xFFFF;
	header->id         = id;
	header->offset     = offset;
	header->block_size = block_size;
	header->item_size  = item_size;
	header->prev_block = prev_block;
	header->checksum   = calculate_block_header_checksum(header);
}

/**
 * \brief Check if sector copying is required and perform it
 *
 * \param[in] size The size required for new item
 *
 * \return True if copying succeeds, otherwise false
 */
static bool copy_sector_if_needed(const uint16_t size)
{
	if (CONF_SECTOR_SIZE - mem.pow < size) {
		return copy_data_to_new_sector();
	}

	return true;
}

/**
 * \brief Collect item data and copy it to new sector
 *
 * \param[in] item Item number
 * \param[in] sector The sector to write to
 * \param[in] pow The offset to apply during writing
 *
 * \return The size of item written, or -1 if writing failed
 */
static int32_t copy_item_to_new_sector(const uint16_t item, const uint8_t sector, const uint16_t pow)
{
	uint16_t            active = 0;
	uint16_t            item_size;
	uint16_t            offset = 0;
	struct block_header header;

	nv_read(mem.active_sector, mem.items[item].last_block, (uint8_t *)&header, sizeof(struct block_header));
	item_size = header.item_size;

	/* Fill new block header... */
	fill_block_header(&header, header.id, 0, header.item_size, header.item_size, 0);
	/* ...and write it to new sector */
	if (!write_and_verify(sector, pow, (uint8_t *)&header, sizeof(struct block_header))) {
		return -1;
	}

	/* Read and copy item by 64 bytes blocks */
	while (item_size) {
		uint8_t  data[64];
		uint16_t size = min(64, item_size);
		/* Collect and write item to new sector */
		if (!collect_item_data(&mem.items[item], data, offset, size)) {
			return -1;
		}
		if (!write_and_verify(sector, pow + offset + sizeof(struct block_header), data, size)) {
			return -1;
		}
		offset += size;
		item_size -= size;
	}
	/* Activate data block */
	if (!write_and_verify(sector, pow, (uint8_t *)&active, sizeof(active))) {
		return -1;
	}

	return header.item_size;
}
