/**
 * \file
 *
 * \brief Instance description for GCLK
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

#ifndef _SAMD21_GCLK_INSTANCE_
#define _SAMD21_GCLK_INSTANCE_

/* ========== Register definition for GCLK peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_GCLK_CTRL              (0x40000C00U) /**< \brief (GCLK) Control */
#define REG_GCLK_STATUS            (0x40000C01U) /**< \brief (GCLK) Status */
#define REG_GCLK_CLKCTRL           (0x40000C02U) /**< \brief (GCLK) Generic Clock Control */
#define REG_GCLK_GENCTRL           (0x40000C04U) /**< \brief (GCLK) Generic Clock Generator Control */
#define REG_GCLK_GENDIV            (0x40000C08U) /**< \brief (GCLK) Generic Clock Generator Division */
#else
#define REG_GCLK_CTRL              (*(RwReg8 *)0x40000C00U) /**< \brief (GCLK) Control */
#define REG_GCLK_STATUS            (*(RoReg8 *)0x40000C01U) /**< \brief (GCLK) Status */
#define REG_GCLK_CLKCTRL           (*(RwReg16*)0x40000C02U) /**< \brief (GCLK) Generic Clock Control */
#define REG_GCLK_GENCTRL           (*(RwReg  *)0x40000C04U) /**< \brief (GCLK) Generic Clock Generator Control */
#define REG_GCLK_GENDIV            (*(RwReg  *)0x40000C08U) /**< \brief (GCLK) Generic Clock Generator Division */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for GCLK peripheral ========== */
#define GCLK_GENDIV_BITS            16      
#define GCLK_GEN_NUM                9        // Number of Generic Clock Generators
#define GCLK_GEN_NUM_MSB            8        // Number of Generic Clock Generators - 1
#define GCLK_GEN_SOURCE_NUM_MSB     8        // Number of Generic Clock Sources - 1
#define GCLK_NUM                    37       // Number of Generic Clock Users
#define GCLK_SOURCE_DFLL48M         7        // DFLL48M output
#define GCLK_SOURCE_FDPLL           8        // FDPLL output
#define GCLK_SOURCE_GCLKGEN1        2        // Generic clock generator 1 output
#define GCLK_SOURCE_GCLKIN          1        // Generator input pad
#define GCLK_SOURCE_NUM             9        // Number of Generic Clock Sources
#define GCLK_SOURCE_OSCULP32K       3        // OSCULP32K oscillator output
#define GCLK_SOURCE_OSC8M           6        // OSC8M oscillator output
#define GCLK_SOURCE_OSC32K          4        // OSC32K oscillator outpur
#define GCLK_SOURCE_XOSC            0        // XOSC oscillator output
#define GCLK_SOURCE_XOSC32K         5        // XOSC32K oscillator output

#endif /* _SAMD21_GCLK_INSTANCE_ */
