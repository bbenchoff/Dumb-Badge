/**
 * \file
 *
 * \brief Non-volatile level declaration.
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

#ifndef _NV_INCLUDED
#define _NV_INCLUDED

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief The amount of sectors in the storage
 */
#ifndef SECTOR_AMOUNT
#define SECTOR_AMOUNT 2
#endif

enum nv_alignment_type { SECTOR_HEADER_ALIGNMENT, BLOCK_WITH_DATA_ALIGNMENT };

/**
 * \brief Initialize non-volatile storage
 *
 * \param[in] descr Descriptor of a driver or middleware used by NV-storage
 */
void nv_init(void *descr);

/**
 * \brief Write data to non-volatile storage
 *
 * \param[in] sector Sector of the storage to write to
 * \param[in] offset The offset inside the sector to start writing to
 * \param[in] data Data to write
 * \param[in] size The size of the data to write
 */
void nv_write(const uint8_t sector, const uint16_t offset, const uint8_t *const data, const uint16_t size);

/**
 * \brief Read data from non-volatile storage
 *
 * \param[in] sector Sector of the storage to read from
 * \param[in] offset The offset inside the sector to start reading from
 * \param[in] data Data buffer to read data to
 * \param[in] size The size of the data buffer
 */
void nv_read(const uint8_t sector, const uint16_t offset, uint8_t *const data, const uint16_t size);

/**
 * \brief Erase a sector
 *
 * \param[in] sector Sector to erase
 */
void nv_erase_sector(uint8_t sector);

/**
 * \brief Compare given data and data stored in non-volatile storage
 *
 * \param[in] sector Sector of the storage with data to compare to
 * \param[in] offset The offset inside the sector to start comparing from
 * \param[in] data Data to compare to
 * \param[in] size The size of the data buffer
 *
 * \return True if content of non-volatile storage and data buffer matches,
 *	otherwise false
 */
bool nv_is_equal(const uint8_t sector, const uint16_t offset, const uint8_t *const data, const uint16_t size);

/**
 * \brief Check if given area is empty
 *
 * \param[in] sector Sector of the storage to perform the check in
 * \param[in] offset The offset inside the sector to start checking from
 * \param[in] size The size of the data to check
 *
 * \return True if content of non-volatile storage is empty, otherwise false
 */
bool nv_is_empty(const uint8_t sector, const uint16_t offset, const uint16_t size);

/**
 * \brief Align current point of write to actual based on type of previous write
 *        access
 *
 * \param[in] address The address to align
 * \param[in] type The type of access
 *
 * \return Aligned point-of-write (offset from storage base address)
 */
uint16_t nv_align_next_access_address(const uint16_t address, const enum nv_alignment_type type);

#ifdef __cplusplus
}
#endif

#endif /* _NV_INCLUDED */
