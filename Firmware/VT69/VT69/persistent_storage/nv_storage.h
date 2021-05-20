/**
 * \file
 *
 * \brief Persistent Storage declaration.
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

#ifndef _NV_STORAGE_H_INCLUDED
#define _NV_STORAGE_H_INCLUDED

#include <compiler.h>
#include <err_codes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialize persistent storage
 */
void nv_storage_init(void);

/**
 * \brief Write an item to the persistent storage
 *
 * \param[in] id The ID of an item to store
 * \param[in] offset The offset inside the given item to start writing to
 * \param[in] data Data to write
 * \param[in] size The size of the data to write
 *
 * \return Status of the operation
 */
int32_t nv_storage_write(const uint16_t id, const uint16_t offset, const uint8_t *const data, const uint16_t size);

/**
 * \brief Read an item from the persistent storage
 *
 * \param[in] id The ID of an item to store
 * \param[in] offset The offset inside the given item to start reading from
 * \param[in] data Data buffer to read data to
 * \param[in] size The size of the data buffer
 *
 * \return Status of the operation
 */
int32_t nv_storage_read(const uint16_t id, const uint16_t offset, uint8_t *const data, const uint16_t size);

/**
 * \brief Retrieve the size of the given item
 *
 * \param[in] id The ID of an item
 *
 * \return The size of the given item or 0 if item does not exist
 */
uint16_t nv_storage_item_size(const uint16_t id);

/**
 * \brief Delete an item from the persistent storage
 *
 * \param[in] id The ID of an item to delete
 *
 * \return Status of the operation
 */
int32_t nv_storage_delete(const uint16_t id);

/**
 * \brief Delete all the items in the persistent storage
 *
 * \return Status of the operation
 */
int32_t nv_storage_erase_all(void);

/**
 * \brief Check whether an item with given ID exists in the persistent storage
 *
 * \param[in] id The ID of an item to store
 *
 * \return True if the item exists, otherwise false
 */
bool nv_storage_item_exists(const uint16_t id);

/**
 * \brief Force storage areas swapping.
 */
void nv_storage_force_packing(void);

/**
 * \brief Retrieve the amount of space left in storage
 *
 * \return The amount of space left in storage
 */
uint16_t nv_storage_space_left(void);

#ifdef __cplusplus
}
#endif

#endif /* _NV_STORAGE_H_INCLUDED */
