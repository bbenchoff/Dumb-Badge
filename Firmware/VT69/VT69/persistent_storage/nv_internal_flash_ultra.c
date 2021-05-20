/**
 * \file
 *
 * \brief Non-volatile level implementation.
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

#include <nv.h>
#include <hal_flash.h>
#include <utils_assert.h>
#include <utils.h>
#include <nv_storage_config.h>
#include <string.h>

static struct flash_descriptor *flash;

#define NV_MEMORY_END (CONF_STORAGE_MEMORY_START + CONF_SECTOR_SIZE * SECTOR_AMOUNT) - 1

/**
 * \brief Initialize non-volatile storage
 */
void nv_init(void *descr)
{
	flash = (struct flash_descriptor *)descr;

	/* Storage must start at row start */
	ASSERT((CONF_STORAGE_MEMORY_START % (flash_get_page_size(flash) * 4)) == 0);
	/* Sector must be of integer number of rows */
	ASSERT((CONF_SECTOR_SIZE % ((flash_get_page_size(flash) * 4)) == 0));
}

/**
 * \brief Write data to non-volatile storage
 */
void nv_write(const uint8_t sector, const uint16_t offset, const uint8_t *const data, const uint16_t size)
{
	uint32_t address = CONF_STORAGE_MEMORY_START + sector * CONF_SECTOR_SIZE + offset;

	/* Write access must start and end within the storage and must not write
	   more than a sector. */
	ASSERT((address <= NV_MEMORY_END) && ((address + size) <= (NV_MEMORY_END + 1))
	       && ((offset + size) <= CONF_SECTOR_SIZE));

	flash_append(flash, address, (uint8_t *)data, size);
}

/**
 * \brief Read data from non-volatile storage
 */
void nv_read(const uint8_t sector, const uint16_t offset, uint8_t *const data, const uint16_t size)
{
	uint32_t address = CONF_STORAGE_MEMORY_START + sector * CONF_SECTOR_SIZE + offset;

	/* Read access must start and end within the storage and must not read more
	   than a sector. */
	ASSERT((address <= NV_MEMORY_END) && ((address + size) <= (NV_MEMORY_END + 1))
	       && ((offset + size) <= CONF_SECTOR_SIZE));

	flash_read(flash, address, data, size);
}

/**
 * \brief Erase a sector
 */
void nv_erase_sector(uint8_t sector)
{
	uint32_t address = CONF_STORAGE_MEMORY_START + sector * CONF_SECTOR_SIZE;

	ASSERT(address <= NV_MEMORY_END);

	flash_erase(flash, address, CONF_SECTOR_SIZE / flash_get_page_size(flash));
}

/**
 * \brief Compare given data and data stored in non-volatile storage
 */
bool nv_is_equal(const uint8_t sector, const uint16_t offset, const uint8_t *const data, const uint16_t size)
{
	uint8_t  tmp[64];
	uint16_t pos     = 0;
	uint32_t address = CONF_STORAGE_MEMORY_START + sector * CONF_SECTOR_SIZE + offset;

	/* Read access must start and end within the storage and must not read more
	   than a sector. There must be at least one byte to compare to. */
	ASSERT((address <= NV_MEMORY_END) && ((address + size) <= (NV_MEMORY_END + 1))
	       && ((offset + size) <= CONF_SECTOR_SIZE) && size);

	while (pos != size) {
		uint8_t cur_size = min(64, size - pos);

		flash_read(flash, address + pos, tmp, cur_size);
		if (memcmp(data + pos, tmp, cur_size)) {
			return false;
		}

		pos += cur_size;
	}

	return true;
}

/**
 * \brief Check if given area is empty
 */
bool nv_is_empty(const uint8_t sector, const uint16_t offset, const uint16_t size)
{
	uint8_t  tmp[64];
	uint16_t pos     = 0;
	uint32_t address = CONF_STORAGE_MEMORY_START + sector * CONF_SECTOR_SIZE + offset;

	/* Read access must start and end within the storage and must not read more
	   than a sector. There must be at least one byte to compare to. */
	ASSERT((address <= NV_MEMORY_END) && ((address + size) <= (NV_MEMORY_END + 1))
	       && ((offset + size) <= CONF_SECTOR_SIZE) && size);

	memset(tmp, 0xFF, 64);

	while (pos != size) {
		uint8_t cur_size = min(64, size - pos);
		uint8_t i        = 0;

		flash_read(flash, address + pos, tmp, cur_size);
		for (; i < 64; i++) {
			if (tmp[i] != 0xFF) {
				return false;
			}
		}

		pos += cur_size;
	}

	return true;
}

/**
 * \brief Align current point of write to actual based on type of previous write
 *        access
 */
uint16_t nv_align_next_access_address(const uint16_t address, const enum nv_alignment_type type)
{
	switch (type) {
	case SECTOR_HEADER_ALIGNMENT:
		return address;

	case BLOCK_WITH_DATA_ALIGNMENT:
		return (address + 127) & 0xFF80;

	default:
		ASSERT(false);
		return address;
	}
}
