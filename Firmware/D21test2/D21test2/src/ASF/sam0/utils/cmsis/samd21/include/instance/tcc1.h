/**
 * \file
 *
 * \brief Instance description for TCC1
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

#ifndef _SAMD21_TCC1_INSTANCE_
#define _SAMD21_TCC1_INSTANCE_

/* ========== Register definition for TCC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TCC1_CTRLA             (0x42002400U) /**< \brief (TCC1) Control A */
#define REG_TCC1_CTRLBCLR          (0x42002404U) /**< \brief (TCC1) Control B Clear */
#define REG_TCC1_CTRLBSET          (0x42002405U) /**< \brief (TCC1) Control B Set */
#define REG_TCC1_SYNCBUSY          (0x42002408U) /**< \brief (TCC1) Synchronization Busy */
#define REG_TCC1_FCTRLA            (0x4200240CU) /**< \brief (TCC1) Recoverable Fault A Configuration */
#define REG_TCC1_FCTRLB            (0x42002410U) /**< \brief (TCC1) Recoverable Fault B Configuration */
#define REG_TCC1_DRVCTRL           (0x42002418U) /**< \brief (TCC1) Driver Control */
#define REG_TCC1_DBGCTRL           (0x4200241EU) /**< \brief (TCC1) Debug Control */
#define REG_TCC1_EVCTRL            (0x42002420U) /**< \brief (TCC1) Event Control */
#define REG_TCC1_INTENCLR          (0x42002424U) /**< \brief (TCC1) Interrupt Enable Clear */
#define REG_TCC1_INTENSET          (0x42002428U) /**< \brief (TCC1) Interrupt Enable Set */
#define REG_TCC1_INTFLAG           (0x4200242CU) /**< \brief (TCC1) Interrupt Flag Status and Clear */
#define REG_TCC1_STATUS            (0x42002430U) /**< \brief (TCC1) Status */
#define REG_TCC1_COUNT             (0x42002434U) /**< \brief (TCC1) Count */
#define REG_TCC1_PATT              (0x42002438U) /**< \brief (TCC1) Pattern */
#define REG_TCC1_WAVE              (0x4200243CU) /**< \brief (TCC1) Waveform Control */
#define REG_TCC1_PER               (0x42002440U) /**< \brief (TCC1) Period */
#define REG_TCC1_CC0               (0x42002444U) /**< \brief (TCC1) Compare and Capture 0 */
#define REG_TCC1_CC1               (0x42002448U) /**< \brief (TCC1) Compare and Capture 1 */
#define REG_TCC1_PATTB             (0x42002464U) /**< \brief (TCC1) Pattern Buffer */
#define REG_TCC1_WAVEB             (0x42002468U) /**< \brief (TCC1) Waveform Control Buffer */
#define REG_TCC1_PERB              (0x4200246CU) /**< \brief (TCC1) Period Buffer */
#define REG_TCC1_CCB0              (0x42002470U) /**< \brief (TCC1) Compare and Capture Buffer 0 */
#define REG_TCC1_CCB1              (0x42002474U) /**< \brief (TCC1) Compare and Capture Buffer 1 */
#else
#define REG_TCC1_CTRLA             (*(RwReg  *)0x42002400U) /**< \brief (TCC1) Control A */
#define REG_TCC1_CTRLBCLR          (*(RwReg8 *)0x42002404U) /**< \brief (TCC1) Control B Clear */
#define REG_TCC1_CTRLBSET          (*(RwReg8 *)0x42002405U) /**< \brief (TCC1) Control B Set */
#define REG_TCC1_SYNCBUSY          (*(RoReg  *)0x42002408U) /**< \brief (TCC1) Synchronization Busy */
#define REG_TCC1_FCTRLA            (*(RwReg  *)0x4200240CU) /**< \brief (TCC1) Recoverable Fault A Configuration */
#define REG_TCC1_FCTRLB            (*(RwReg  *)0x42002410U) /**< \brief (TCC1) Recoverable Fault B Configuration */
#define REG_TCC1_DRVCTRL           (*(RwReg  *)0x42002418U) /**< \brief (TCC1) Driver Control */
#define REG_TCC1_DBGCTRL           (*(RwReg8 *)0x4200241EU) /**< \brief (TCC1) Debug Control */
#define REG_TCC1_EVCTRL            (*(RwReg  *)0x42002420U) /**< \brief (TCC1) Event Control */
#define REG_TCC1_INTENCLR          (*(RwReg  *)0x42002424U) /**< \brief (TCC1) Interrupt Enable Clear */
#define REG_TCC1_INTENSET          (*(RwReg  *)0x42002428U) /**< \brief (TCC1) Interrupt Enable Set */
#define REG_TCC1_INTFLAG           (*(RwReg  *)0x4200242CU) /**< \brief (TCC1) Interrupt Flag Status and Clear */
#define REG_TCC1_STATUS            (*(RwReg  *)0x42002430U) /**< \brief (TCC1) Status */
#define REG_TCC1_COUNT             (*(RwReg  *)0x42002434U) /**< \brief (TCC1) Count */
#define REG_TCC1_PATT              (*(RwReg16*)0x42002438U) /**< \brief (TCC1) Pattern */
#define REG_TCC1_WAVE              (*(RwReg  *)0x4200243CU) /**< \brief (TCC1) Waveform Control */
#define REG_TCC1_PER               (*(RwReg  *)0x42002440U) /**< \brief (TCC1) Period */
#define REG_TCC1_CC0               (*(RwReg  *)0x42002444U) /**< \brief (TCC1) Compare and Capture 0 */
#define REG_TCC1_CC1               (*(RwReg  *)0x42002448U) /**< \brief (TCC1) Compare and Capture 1 */
#define REG_TCC1_PATTB             (*(RwReg16*)0x42002464U) /**< \brief (TCC1) Pattern Buffer */
#define REG_TCC1_WAVEB             (*(RwReg  *)0x42002468U) /**< \brief (TCC1) Waveform Control Buffer */
#define REG_TCC1_PERB              (*(RwReg  *)0x4200246CU) /**< \brief (TCC1) Period Buffer */
#define REG_TCC1_CCB0              (*(RwReg  *)0x42002470U) /**< \brief (TCC1) Compare and Capture Buffer 0 */
#define REG_TCC1_CCB1              (*(RwReg  *)0x42002474U) /**< \brief (TCC1) Compare and Capture Buffer 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TCC1 peripheral ========== */
#define TCC1_CC_NUM                 2        // Number of Compare/Capture units
#define TCC1_DITHERING              1        // Dithering feature implemented
#define TCC1_DMAC_ID_MC_0           19
#define TCC1_DMAC_ID_MC_1           20
#define TCC1_DMAC_ID_MC_LSB         19
#define TCC1_DMAC_ID_MC_MSB         20
#define TCC1_DMAC_ID_MC_SIZE        2
#define TCC1_DMAC_ID_OVF            18       // DMA overflow/underflow/retrigger trigger
#define TCC1_DTI                    0        // Dead-Time-Insertion feature implemented
#define TCC1_EXT                    24       // Coding of implemented extended features
#define TCC1_GCLK_ID                26       // Index of Generic Clock
#define TCC1_MASTER                 1       
#define TCC1_OTMX                   0        // Output Matrix feature implemented
#define TCC1_OW_NUM                 4        // Number of Output Waveforms
#define TCC1_PG                     1        // Pattern Generation feature implemented
#define TCC1_SIZE                   24      
#define TCC1_SWAP                   0        // DTI outputs swap feature implemented
#define TCC1_TYPE                   2        // TCC type 0 : NA, 1 : Master, 2 : Slave

#endif /* _SAMD21_TCC1_INSTANCE_ */
