#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Release.mk)" "nbproject/Makefile-local-Release.mk"
include nbproject/Makefile-local-Release.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Release
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Device_Startup/startup_samd51.c ../Device_Startup/system_samd51.c ../examples/driver_examples.c ../hal/src/hal_atomic.c ../hal/src/hal_cache.c ../hal/src/hal_delay.c ../hal/src/hal_ext_irq.c ../hal/src/hal_flash.c ../hal/src/hal_gpio.c ../hal/src/hal_init.c ../hal/src/hal_io.c ../hal/src/hal_rand_sync.c ../hal/src/hal_sleep.c ../hal/src/hal_usart_sync.c ../hal/src/hal_usb_device.c ../hal/src/hal_wdt.c ../hal/utils/src/utils_assert.c ../hal/utils/src/utils_event.c ../hal/utils/src/utils_list.c ../hal/utils/src/utils_syscalls.c ../hpl/cmcc/hpl_cmcc.c ../hpl/core/hpl_core_m4.c ../hpl/core/hpl_init.c ../hpl/dmac/hpl_dmac.c ../hpl/eic/hpl_eic.c ../hpl/gclk/hpl_gclk.c ../hpl/mclk/hpl_mclk.c ../hpl/nvmctrl/hpl_nvmctrl.c ../hpl/osc32kctrl/hpl_osc32kctrl.c ../hpl/oscctrl/hpl_oscctrl.c ../hpl/pm/hpl_pm.c ../hpl/ramecc/hpl_ramecc.c ../hpl/sercom/hpl_sercom.c ../hpl/systick/hpl_systick.c ../hpl/trng/hpl_trng.c ../hpl/usb/hpl_usb.c ../hpl/wdt/hpl_wdt.c ../persistent_storage/nv_internal_flash_ultra.c ../persistent_storage/nv_storage.c ../stdio_redirect/gcc/read.c ../stdio_redirect/gcc/write.c ../stdio_redirect/stdio_io.c ../atmel_start.c ../console.c ../driver_init.c ../LCD.c ../LCDBus.c ../main.c ../persistent_storage_start.c ../splash.c ../stdio_start.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1301743165/startup_samd51.o ${OBJECTDIR}/_ext/1301743165/system_samd51.o ${OBJECTDIR}/_ext/1381494712/driver_examples.o ${OBJECTDIR}/_ext/991121639/hal_atomic.o ${OBJECTDIR}/_ext/991121639/hal_cache.o ${OBJECTDIR}/_ext/991121639/hal_delay.o ${OBJECTDIR}/_ext/991121639/hal_ext_irq.o ${OBJECTDIR}/_ext/991121639/hal_flash.o ${OBJECTDIR}/_ext/991121639/hal_gpio.o ${OBJECTDIR}/_ext/991121639/hal_init.o ${OBJECTDIR}/_ext/991121639/hal_io.o ${OBJECTDIR}/_ext/991121639/hal_rand_sync.o ${OBJECTDIR}/_ext/991121639/hal_sleep.o ${OBJECTDIR}/_ext/991121639/hal_usart_sync.o ${OBJECTDIR}/_ext/991121639/hal_usb_device.o ${OBJECTDIR}/_ext/991121639/hal_wdt.o ${OBJECTDIR}/_ext/447684357/utils_assert.o ${OBJECTDIR}/_ext/447684357/utils_event.o ${OBJECTDIR}/_ext/447684357/utils_list.o ${OBJECTDIR}/_ext/447684357/utils_syscalls.o ${OBJECTDIR}/_ext/232827772/hpl_cmcc.o ${OBJECTDIR}/_ext/232825383/hpl_core_m4.o ${OBJECTDIR}/_ext/232825383/hpl_init.o ${OBJECTDIR}/_ext/232798043/hpl_dmac.o ${OBJECTDIR}/_ext/561698107/hpl_eic.o ${OBJECTDIR}/_ext/232717931/hpl_gclk.o ${OBJECTDIR}/_ext/232539185/hpl_mclk.o ${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o ${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o ${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o ${OBJECTDIR}/_ext/1126497609/hpl_pm.o ${OBJECTDIR}/_ext/9468513/hpl_ramecc.o ${OBJECTDIR}/_ext/41939163/hpl_sercom.o ${OBJECTDIR}/_ext/1874121072/hpl_systick.o ${OBJECTDIR}/_ext/232316175/hpl_trng.o ${OBJECTDIR}/_ext/561682422/hpl_usb.o ${OBJECTDIR}/_ext/561680947/hpl_wdt.o ${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o ${OBJECTDIR}/_ext/1902934654/nv_storage.o ${OBJECTDIR}/_ext/565800185/read.o ${OBJECTDIR}/_ext/565800185/write.o ${OBJECTDIR}/_ext/433002239/stdio_io.o ${OBJECTDIR}/_ext/1472/atmel_start.o ${OBJECTDIR}/_ext/1472/console.o ${OBJECTDIR}/_ext/1472/driver_init.o ${OBJECTDIR}/_ext/1472/LCD.o ${OBJECTDIR}/_ext/1472/LCDBus.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/persistent_storage_start.o ${OBJECTDIR}/_ext/1472/splash.o ${OBJECTDIR}/_ext/1472/stdio_start.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1301743165/startup_samd51.o.d ${OBJECTDIR}/_ext/1301743165/system_samd51.o.d ${OBJECTDIR}/_ext/1381494712/driver_examples.o.d ${OBJECTDIR}/_ext/991121639/hal_atomic.o.d ${OBJECTDIR}/_ext/991121639/hal_cache.o.d ${OBJECTDIR}/_ext/991121639/hal_delay.o.d ${OBJECTDIR}/_ext/991121639/hal_ext_irq.o.d ${OBJECTDIR}/_ext/991121639/hal_flash.o.d ${OBJECTDIR}/_ext/991121639/hal_gpio.o.d ${OBJECTDIR}/_ext/991121639/hal_init.o.d ${OBJECTDIR}/_ext/991121639/hal_io.o.d ${OBJECTDIR}/_ext/991121639/hal_rand_sync.o.d ${OBJECTDIR}/_ext/991121639/hal_sleep.o.d ${OBJECTDIR}/_ext/991121639/hal_usart_sync.o.d ${OBJECTDIR}/_ext/991121639/hal_usb_device.o.d ${OBJECTDIR}/_ext/991121639/hal_wdt.o.d ${OBJECTDIR}/_ext/447684357/utils_assert.o.d ${OBJECTDIR}/_ext/447684357/utils_event.o.d ${OBJECTDIR}/_ext/447684357/utils_list.o.d ${OBJECTDIR}/_ext/447684357/utils_syscalls.o.d ${OBJECTDIR}/_ext/232827772/hpl_cmcc.o.d ${OBJECTDIR}/_ext/232825383/hpl_core_m4.o.d ${OBJECTDIR}/_ext/232825383/hpl_init.o.d ${OBJECTDIR}/_ext/232798043/hpl_dmac.o.d ${OBJECTDIR}/_ext/561698107/hpl_eic.o.d ${OBJECTDIR}/_ext/232717931/hpl_gclk.o.d ${OBJECTDIR}/_ext/232539185/hpl_mclk.o.d ${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o.d ${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o.d ${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o.d ${OBJECTDIR}/_ext/1126497609/hpl_pm.o.d ${OBJECTDIR}/_ext/9468513/hpl_ramecc.o.d ${OBJECTDIR}/_ext/41939163/hpl_sercom.o.d ${OBJECTDIR}/_ext/1874121072/hpl_systick.o.d ${OBJECTDIR}/_ext/232316175/hpl_trng.o.d ${OBJECTDIR}/_ext/561682422/hpl_usb.o.d ${OBJECTDIR}/_ext/561680947/hpl_wdt.o.d ${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o.d ${OBJECTDIR}/_ext/1902934654/nv_storage.o.d ${OBJECTDIR}/_ext/565800185/read.o.d ${OBJECTDIR}/_ext/565800185/write.o.d ${OBJECTDIR}/_ext/433002239/stdio_io.o.d ${OBJECTDIR}/_ext/1472/atmel_start.o.d ${OBJECTDIR}/_ext/1472/console.o.d ${OBJECTDIR}/_ext/1472/driver_init.o.d ${OBJECTDIR}/_ext/1472/LCD.o.d ${OBJECTDIR}/_ext/1472/LCDBus.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/persistent_storage_start.o.d ${OBJECTDIR}/_ext/1472/splash.o.d ${OBJECTDIR}/_ext/1472/stdio_start.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1301743165/startup_samd51.o ${OBJECTDIR}/_ext/1301743165/system_samd51.o ${OBJECTDIR}/_ext/1381494712/driver_examples.o ${OBJECTDIR}/_ext/991121639/hal_atomic.o ${OBJECTDIR}/_ext/991121639/hal_cache.o ${OBJECTDIR}/_ext/991121639/hal_delay.o ${OBJECTDIR}/_ext/991121639/hal_ext_irq.o ${OBJECTDIR}/_ext/991121639/hal_flash.o ${OBJECTDIR}/_ext/991121639/hal_gpio.o ${OBJECTDIR}/_ext/991121639/hal_init.o ${OBJECTDIR}/_ext/991121639/hal_io.o ${OBJECTDIR}/_ext/991121639/hal_rand_sync.o ${OBJECTDIR}/_ext/991121639/hal_sleep.o ${OBJECTDIR}/_ext/991121639/hal_usart_sync.o ${OBJECTDIR}/_ext/991121639/hal_usb_device.o ${OBJECTDIR}/_ext/991121639/hal_wdt.o ${OBJECTDIR}/_ext/447684357/utils_assert.o ${OBJECTDIR}/_ext/447684357/utils_event.o ${OBJECTDIR}/_ext/447684357/utils_list.o ${OBJECTDIR}/_ext/447684357/utils_syscalls.o ${OBJECTDIR}/_ext/232827772/hpl_cmcc.o ${OBJECTDIR}/_ext/232825383/hpl_core_m4.o ${OBJECTDIR}/_ext/232825383/hpl_init.o ${OBJECTDIR}/_ext/232798043/hpl_dmac.o ${OBJECTDIR}/_ext/561698107/hpl_eic.o ${OBJECTDIR}/_ext/232717931/hpl_gclk.o ${OBJECTDIR}/_ext/232539185/hpl_mclk.o ${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o ${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o ${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o ${OBJECTDIR}/_ext/1126497609/hpl_pm.o ${OBJECTDIR}/_ext/9468513/hpl_ramecc.o ${OBJECTDIR}/_ext/41939163/hpl_sercom.o ${OBJECTDIR}/_ext/1874121072/hpl_systick.o ${OBJECTDIR}/_ext/232316175/hpl_trng.o ${OBJECTDIR}/_ext/561682422/hpl_usb.o ${OBJECTDIR}/_ext/561680947/hpl_wdt.o ${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o ${OBJECTDIR}/_ext/1902934654/nv_storage.o ${OBJECTDIR}/_ext/565800185/read.o ${OBJECTDIR}/_ext/565800185/write.o ${OBJECTDIR}/_ext/433002239/stdio_io.o ${OBJECTDIR}/_ext/1472/atmel_start.o ${OBJECTDIR}/_ext/1472/console.o ${OBJECTDIR}/_ext/1472/driver_init.o ${OBJECTDIR}/_ext/1472/LCD.o ${OBJECTDIR}/_ext/1472/LCDBus.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/persistent_storage_start.o ${OBJECTDIR}/_ext/1472/splash.o ${OBJECTDIR}/_ext/1472/stdio_start.o

# Source Files
SOURCEFILES=../Device_Startup/startup_samd51.c ../Device_Startup/system_samd51.c ../examples/driver_examples.c ../hal/src/hal_atomic.c ../hal/src/hal_cache.c ../hal/src/hal_delay.c ../hal/src/hal_ext_irq.c ../hal/src/hal_flash.c ../hal/src/hal_gpio.c ../hal/src/hal_init.c ../hal/src/hal_io.c ../hal/src/hal_rand_sync.c ../hal/src/hal_sleep.c ../hal/src/hal_usart_sync.c ../hal/src/hal_usb_device.c ../hal/src/hal_wdt.c ../hal/utils/src/utils_assert.c ../hal/utils/src/utils_event.c ../hal/utils/src/utils_list.c ../hal/utils/src/utils_syscalls.c ../hpl/cmcc/hpl_cmcc.c ../hpl/core/hpl_core_m4.c ../hpl/core/hpl_init.c ../hpl/dmac/hpl_dmac.c ../hpl/eic/hpl_eic.c ../hpl/gclk/hpl_gclk.c ../hpl/mclk/hpl_mclk.c ../hpl/nvmctrl/hpl_nvmctrl.c ../hpl/osc32kctrl/hpl_osc32kctrl.c ../hpl/oscctrl/hpl_oscctrl.c ../hpl/pm/hpl_pm.c ../hpl/ramecc/hpl_ramecc.c ../hpl/sercom/hpl_sercom.c ../hpl/systick/hpl_systick.c ../hpl/trng/hpl_trng.c ../hpl/usb/hpl_usb.c ../hpl/wdt/hpl_wdt.c ../persistent_storage/nv_internal_flash_ultra.c ../persistent_storage/nv_storage.c ../stdio_redirect/gcc/read.c ../stdio_redirect/gcc/write.c ../stdio_redirect/stdio_io.c ../atmel_start.c ../console.c ../driver_init.c ../LCD.c ../LCDBus.c ../main.c ../persistent_storage_start.c ../splash.c ../stdio_start.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${DFP_DIR}/samd51a/include"  -I "${CMSIS_DIR}/CMSIS/Core/Include"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Release.mk dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=SAMD51N19A
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1301743165/startup_samd51.o: ../Device_Startup/startup_samd51.c  .generated_files/flags/Release/22ada2342fd127b1d9480ae370109a7a7fb0a9af .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1301743165" 
	@${RM} ${OBJECTDIR}/_ext/1301743165/startup_samd51.o.d 
	@${RM} ${OBJECTDIR}/_ext/1301743165/startup_samd51.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1301743165/startup_samd51.o.d" -o ${OBJECTDIR}/_ext/1301743165/startup_samd51.o ../Device_Startup/startup_samd51.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1301743165/system_samd51.o: ../Device_Startup/system_samd51.c  .generated_files/flags/Release/88486437acaa5d772991be1f36371ce84a8ef17c .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1301743165" 
	@${RM} ${OBJECTDIR}/_ext/1301743165/system_samd51.o.d 
	@${RM} ${OBJECTDIR}/_ext/1301743165/system_samd51.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1301743165/system_samd51.o.d" -o ${OBJECTDIR}/_ext/1301743165/system_samd51.o ../Device_Startup/system_samd51.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1381494712/driver_examples.o: ../examples/driver_examples.c  .generated_files/flags/Release/38004469ba6da6886d5c0bcb73ecb17c5b78becf .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1381494712" 
	@${RM} ${OBJECTDIR}/_ext/1381494712/driver_examples.o.d 
	@${RM} ${OBJECTDIR}/_ext/1381494712/driver_examples.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1381494712/driver_examples.o.d" -o ${OBJECTDIR}/_ext/1381494712/driver_examples.o ../examples/driver_examples.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_atomic.o: ../hal/src/hal_atomic.c  .generated_files/flags/Release/333d9ce5290ab3012fe3c7a26f5e0cdb67b27a8e .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_atomic.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_atomic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_atomic.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_atomic.o ../hal/src/hal_atomic.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_cache.o: ../hal/src/hal_cache.c  .generated_files/flags/Release/17f77c95a3099969132627095f3fc9f227701cd5 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_cache.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_cache.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_cache.o ../hal/src/hal_cache.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_delay.o: ../hal/src/hal_delay.c  .generated_files/flags/Release/90a5d12bf74b16e0da8912380f834ca9d94c4c6 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_delay.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_delay.o ../hal/src/hal_delay.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_ext_irq.o: ../hal/src/hal_ext_irq.c  .generated_files/flags/Release/54e11722447b176a9aa2c9f6b8296b67a2262519 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_ext_irq.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_ext_irq.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_ext_irq.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_ext_irq.o ../hal/src/hal_ext_irq.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_flash.o: ../hal/src/hal_flash.c  .generated_files/flags/Release/da5ef8bb2935b0fac03fc273ff397c00290aa4b1 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_flash.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_flash.o ../hal/src/hal_flash.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_gpio.o: ../hal/src/hal_gpio.c  .generated_files/flags/Release/14e54b85ee11739fe27e63f427dc72b951e5c78a .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_gpio.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_gpio.o ../hal/src/hal_gpio.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_init.o: ../hal/src/hal_init.c  .generated_files/flags/Release/5abcd80332b416831aacbe1807effacb3099cd9b .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_init.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_init.o ../hal/src/hal_init.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_io.o: ../hal/src/hal_io.c  .generated_files/flags/Release/5013987043f589bf9c49f41f7c246ac8e7ce88e4 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_io.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_io.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_io.o ../hal/src/hal_io.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_rand_sync.o: ../hal/src/hal_rand_sync.c  .generated_files/flags/Release/70cf413287839eb9a68ffffe62f95b9a7b617f6d .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_rand_sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_rand_sync.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_rand_sync.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_rand_sync.o ../hal/src/hal_rand_sync.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_sleep.o: ../hal/src/hal_sleep.c  .generated_files/flags/Release/d70fa2f7f65793b3a04a75941e59752ea80cceba .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_sleep.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_sleep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_sleep.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_sleep.o ../hal/src/hal_sleep.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_usart_sync.o: ../hal/src/hal_usart_sync.c  .generated_files/flags/Release/a20705d90799c245b5a1756395898aafe5addd07 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_usart_sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_usart_sync.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_usart_sync.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_usart_sync.o ../hal/src/hal_usart_sync.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_usb_device.o: ../hal/src/hal_usb_device.c  .generated_files/flags/Release/242869ad285d653fc56d7ee6f6ffb7d87f600af4 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_usb_device.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_usb_device.o ../hal/src/hal_usb_device.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_wdt.o: ../hal/src/hal_wdt.c  .generated_files/flags/Release/2645cc5edd013ab445639cd94913a9260c1140b4 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_wdt.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_wdt.o ../hal/src/hal_wdt.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/447684357/utils_assert.o: ../hal/utils/src/utils_assert.c  .generated_files/flags/Release/714233d660310130dd7d567e9469d57eaf9ccc30 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/447684357" 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_assert.o.d 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_assert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/447684357/utils_assert.o.d" -o ${OBJECTDIR}/_ext/447684357/utils_assert.o ../hal/utils/src/utils_assert.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/447684357/utils_event.o: ../hal/utils/src/utils_event.c  .generated_files/flags/Release/11fa6d3e89db7df0b7303a9eeb15dcf4ffb78276 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/447684357" 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_event.o.d 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_event.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/447684357/utils_event.o.d" -o ${OBJECTDIR}/_ext/447684357/utils_event.o ../hal/utils/src/utils_event.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/447684357/utils_list.o: ../hal/utils/src/utils_list.c  .generated_files/flags/Release/a405346fb107338fc8b10d0a7face29c662d9ac8 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/447684357" 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_list.o.d 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/447684357/utils_list.o.d" -o ${OBJECTDIR}/_ext/447684357/utils_list.o ../hal/utils/src/utils_list.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/447684357/utils_syscalls.o: ../hal/utils/src/utils_syscalls.c  .generated_files/flags/Release/54f31a68967ccfc0a5ae9c3a5dafad4e81c03a1b .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/447684357" 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/447684357/utils_syscalls.o.d" -o ${OBJECTDIR}/_ext/447684357/utils_syscalls.o ../hal/utils/src/utils_syscalls.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232827772/hpl_cmcc.o: ../hpl/cmcc/hpl_cmcc.c  .generated_files/flags/Release/5c1d57515d5e53911d82a68d409686495a00a628 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232827772" 
	@${RM} ${OBJECTDIR}/_ext/232827772/hpl_cmcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/232827772/hpl_cmcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232827772/hpl_cmcc.o.d" -o ${OBJECTDIR}/_ext/232827772/hpl_cmcc.o ../hpl/cmcc/hpl_cmcc.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232825383/hpl_core_m4.o: ../hpl/core/hpl_core_m4.c  .generated_files/flags/Release/5fecf204e208a03591104ce81007f32301d3fcf0 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232825383" 
	@${RM} ${OBJECTDIR}/_ext/232825383/hpl_core_m4.o.d 
	@${RM} ${OBJECTDIR}/_ext/232825383/hpl_core_m4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232825383/hpl_core_m4.o.d" -o ${OBJECTDIR}/_ext/232825383/hpl_core_m4.o ../hpl/core/hpl_core_m4.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232825383/hpl_init.o: ../hpl/core/hpl_init.c  .generated_files/flags/Release/d7eb667c3e02c67aef135f1c69d7e6a54eec2701 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232825383" 
	@${RM} ${OBJECTDIR}/_ext/232825383/hpl_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/232825383/hpl_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232825383/hpl_init.o.d" -o ${OBJECTDIR}/_ext/232825383/hpl_init.o ../hpl/core/hpl_init.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232798043/hpl_dmac.o: ../hpl/dmac/hpl_dmac.c  .generated_files/flags/Release/af632beac71ab5f96002872011c671b9edb65b24 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232798043" 
	@${RM} ${OBJECTDIR}/_ext/232798043/hpl_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/232798043/hpl_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232798043/hpl_dmac.o.d" -o ${OBJECTDIR}/_ext/232798043/hpl_dmac.o ../hpl/dmac/hpl_dmac.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/561698107/hpl_eic.o: ../hpl/eic/hpl_eic.c  .generated_files/flags/Release/15a6198fc4b1b9ce3b5653e564ecff045e4ea258 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/561698107" 
	@${RM} ${OBJECTDIR}/_ext/561698107/hpl_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/561698107/hpl_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/561698107/hpl_eic.o.d" -o ${OBJECTDIR}/_ext/561698107/hpl_eic.o ../hpl/eic/hpl_eic.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232717931/hpl_gclk.o: ../hpl/gclk/hpl_gclk.c  .generated_files/flags/Release/6f78d613a87f1089cd35a8309acabf0722281831 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232717931" 
	@${RM} ${OBJECTDIR}/_ext/232717931/hpl_gclk.o.d 
	@${RM} ${OBJECTDIR}/_ext/232717931/hpl_gclk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232717931/hpl_gclk.o.d" -o ${OBJECTDIR}/_ext/232717931/hpl_gclk.o ../hpl/gclk/hpl_gclk.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232539185/hpl_mclk.o: ../hpl/mclk/hpl_mclk.c  .generated_files/flags/Release/38cf08d421b7356effe5c8cd29a7682b86bbdefd .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232539185" 
	@${RM} ${OBJECTDIR}/_ext/232539185/hpl_mclk.o.d 
	@${RM} ${OBJECTDIR}/_ext/232539185/hpl_mclk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232539185/hpl_mclk.o.d" -o ${OBJECTDIR}/_ext/232539185/hpl_mclk.o ../hpl/mclk/hpl_mclk.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o: ../hpl/nvmctrl/hpl_nvmctrl.c  .generated_files/flags/Release/aae572422dfd5d216a2f563e4d08bb14484a1754 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1639645974" 
	@${RM} ${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o ../hpl/nvmctrl/hpl_nvmctrl.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o: ../hpl/osc32kctrl/hpl_osc32kctrl.c  .generated_files/flags/Release/c75c7ea1236899db059c63230135b14ab06766cb .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/833842894" 
	@${RM} ${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o.d" -o ${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o ../hpl/osc32kctrl/hpl_osc32kctrl.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o: ../hpl/oscctrl/hpl_oscctrl.c  .generated_files/flags/Release/3d386c11802e57a981bc998f02440c2f83ff7403 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1862940304" 
	@${RM} ${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o.d" -o ${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o ../hpl/oscctrl/hpl_oscctrl.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1126497609/hpl_pm.o: ../hpl/pm/hpl_pm.c  .generated_files/flags/Release/8c3c25c78ed6e2ab5a313b58a528bccf72fea044 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1126497609" 
	@${RM} ${OBJECTDIR}/_ext/1126497609/hpl_pm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1126497609/hpl_pm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1126497609/hpl_pm.o.d" -o ${OBJECTDIR}/_ext/1126497609/hpl_pm.o ../hpl/pm/hpl_pm.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/9468513/hpl_ramecc.o: ../hpl/ramecc/hpl_ramecc.c  .generated_files/flags/Release/6a3bb4a826a92f5eaed657db4744ed5747877ba9 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/9468513" 
	@${RM} ${OBJECTDIR}/_ext/9468513/hpl_ramecc.o.d 
	@${RM} ${OBJECTDIR}/_ext/9468513/hpl_ramecc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/9468513/hpl_ramecc.o.d" -o ${OBJECTDIR}/_ext/9468513/hpl_ramecc.o ../hpl/ramecc/hpl_ramecc.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/41939163/hpl_sercom.o: ../hpl/sercom/hpl_sercom.c  .generated_files/flags/Release/80861d0c5bbf48fefd81ea804edc6e22435fa6da .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/41939163" 
	@${RM} ${OBJECTDIR}/_ext/41939163/hpl_sercom.o.d 
	@${RM} ${OBJECTDIR}/_ext/41939163/hpl_sercom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/41939163/hpl_sercom.o.d" -o ${OBJECTDIR}/_ext/41939163/hpl_sercom.o ../hpl/sercom/hpl_sercom.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1874121072/hpl_systick.o: ../hpl/systick/hpl_systick.c  .generated_files/flags/Release/bd67acff88712b5eb61e1ee942cee77423a516a3 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1874121072" 
	@${RM} ${OBJECTDIR}/_ext/1874121072/hpl_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1874121072/hpl_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1874121072/hpl_systick.o.d" -o ${OBJECTDIR}/_ext/1874121072/hpl_systick.o ../hpl/systick/hpl_systick.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232316175/hpl_trng.o: ../hpl/trng/hpl_trng.c  .generated_files/flags/Release/ef2feee2f337966f19f72d9eb3bb3325b9bf1e0e .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232316175" 
	@${RM} ${OBJECTDIR}/_ext/232316175/hpl_trng.o.d 
	@${RM} ${OBJECTDIR}/_ext/232316175/hpl_trng.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232316175/hpl_trng.o.d" -o ${OBJECTDIR}/_ext/232316175/hpl_trng.o ../hpl/trng/hpl_trng.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/561682422/hpl_usb.o: ../hpl/usb/hpl_usb.c  .generated_files/flags/Release/744f518b73f64375600b2efc2a8ded0f26a70e0c .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/561682422" 
	@${RM} ${OBJECTDIR}/_ext/561682422/hpl_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/561682422/hpl_usb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/561682422/hpl_usb.o.d" -o ${OBJECTDIR}/_ext/561682422/hpl_usb.o ../hpl/usb/hpl_usb.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/561680947/hpl_wdt.o: ../hpl/wdt/hpl_wdt.c  .generated_files/flags/Release/d1c9cc4c7a3aec733305a0ffea005deb5042a8f5 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/561680947" 
	@${RM} ${OBJECTDIR}/_ext/561680947/hpl_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/561680947/hpl_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/561680947/hpl_wdt.o.d" -o ${OBJECTDIR}/_ext/561680947/hpl_wdt.o ../hpl/wdt/hpl_wdt.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o: ../persistent_storage/nv_internal_flash_ultra.c  .generated_files/flags/Release/81971094045f117ba9408c522af6662046137994 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1902934654" 
	@${RM} ${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o.d 
	@${RM} ${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o.d" -o ${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o ../persistent_storage/nv_internal_flash_ultra.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1902934654/nv_storage.o: ../persistent_storage/nv_storage.c  .generated_files/flags/Release/a1310a933957675181e3f179a8d132d701f5cf8f .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1902934654" 
	@${RM} ${OBJECTDIR}/_ext/1902934654/nv_storage.o.d 
	@${RM} ${OBJECTDIR}/_ext/1902934654/nv_storage.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1902934654/nv_storage.o.d" -o ${OBJECTDIR}/_ext/1902934654/nv_storage.o ../persistent_storage/nv_storage.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/565800185/read.o: ../stdio_redirect/gcc/read.c  .generated_files/flags/Release/fb225870fedc6c842a8d5ff71add0048e9802fcf .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/565800185" 
	@${RM} ${OBJECTDIR}/_ext/565800185/read.o.d 
	@${RM} ${OBJECTDIR}/_ext/565800185/read.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/565800185/read.o.d" -o ${OBJECTDIR}/_ext/565800185/read.o ../stdio_redirect/gcc/read.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/565800185/write.o: ../stdio_redirect/gcc/write.c  .generated_files/flags/Release/20d2a5c84d812203d2e9ae4ef786f08c77ace3a0 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/565800185" 
	@${RM} ${OBJECTDIR}/_ext/565800185/write.o.d 
	@${RM} ${OBJECTDIR}/_ext/565800185/write.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/565800185/write.o.d" -o ${OBJECTDIR}/_ext/565800185/write.o ../stdio_redirect/gcc/write.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/433002239/stdio_io.o: ../stdio_redirect/stdio_io.c  .generated_files/flags/Release/aa017be0881ea2af57b6ce50611d8f45e1f204bb .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/433002239" 
	@${RM} ${OBJECTDIR}/_ext/433002239/stdio_io.o.d 
	@${RM} ${OBJECTDIR}/_ext/433002239/stdio_io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/433002239/stdio_io.o.d" -o ${OBJECTDIR}/_ext/433002239/stdio_io.o ../stdio_redirect/stdio_io.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/atmel_start.o: ../atmel_start.c  .generated_files/flags/Release/88cd9c794856f029f50492cd0566aacd2f32c846 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/atmel_start.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/atmel_start.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/atmel_start.o.d" -o ${OBJECTDIR}/_ext/1472/atmel_start.o ../atmel_start.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/console.o: ../console.c  .generated_files/flags/Release/f0a5e9450b93d3cf45afe7d6d4c07607977a7d89 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/console.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/console.o.d" -o ${OBJECTDIR}/_ext/1472/console.o ../console.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/driver_init.o: ../driver_init.c  .generated_files/flags/Release/5164ee986e8a88df0ce6dd6518b5bd454acdd2fc .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/driver_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/driver_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/driver_init.o.d" -o ${OBJECTDIR}/_ext/1472/driver_init.o ../driver_init.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/LCD.o: ../LCD.c  .generated_files/flags/Release/bf663e38aca59d13ed5d1eb44871066dc2d0553c .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LCD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/LCD.o.d" -o ${OBJECTDIR}/_ext/1472/LCD.o ../LCD.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/LCDBus.o: ../LCDBus.c  .generated_files/flags/Release/e97dea424b5d492e599be56cbc7248631a1053fc .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LCDBus.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LCDBus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/LCDBus.o.d" -o ${OBJECTDIR}/_ext/1472/LCDBus.o ../LCDBus.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/Release/15a48739839c3370b631df13b2b8c74cd138f2d5 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/persistent_storage_start.o: ../persistent_storage_start.c  .generated_files/flags/Release/d66c50d1185326741fec98de89907c916dd77140 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/persistent_storage_start.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/persistent_storage_start.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/persistent_storage_start.o.d" -o ${OBJECTDIR}/_ext/1472/persistent_storage_start.o ../persistent_storage_start.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/splash.o: ../splash.c  .generated_files/flags/Release/cab948e8e37b25709591a5e645f9d885e7637cdb .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/splash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/splash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/splash.o.d" -o ${OBJECTDIR}/_ext/1472/splash.o ../splash.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/stdio_start.o: ../stdio_start.c  .generated_files/flags/Release/f62772e0c486348febc131008d8152c7bfc15385 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/stdio_start.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/stdio_start.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4 -g -D__DEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/stdio_start.o.d" -o ${OBJECTDIR}/_ext/1472/stdio_start.o ../stdio_start.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
else
${OBJECTDIR}/_ext/1301743165/startup_samd51.o: ../Device_Startup/startup_samd51.c  .generated_files/flags/Release/18b0f2f797a530fa67f43fd6966c331cbc2cf50b .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1301743165" 
	@${RM} ${OBJECTDIR}/_ext/1301743165/startup_samd51.o.d 
	@${RM} ${OBJECTDIR}/_ext/1301743165/startup_samd51.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1301743165/startup_samd51.o.d" -o ${OBJECTDIR}/_ext/1301743165/startup_samd51.o ../Device_Startup/startup_samd51.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1301743165/system_samd51.o: ../Device_Startup/system_samd51.c  .generated_files/flags/Release/a7c91d87207ad71ef5a48fd3aeb3fbb43ba5e605 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1301743165" 
	@${RM} ${OBJECTDIR}/_ext/1301743165/system_samd51.o.d 
	@${RM} ${OBJECTDIR}/_ext/1301743165/system_samd51.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1301743165/system_samd51.o.d" -o ${OBJECTDIR}/_ext/1301743165/system_samd51.o ../Device_Startup/system_samd51.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1381494712/driver_examples.o: ../examples/driver_examples.c  .generated_files/flags/Release/bd42f0206656f4ff4ae973df32893a680a25c82 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1381494712" 
	@${RM} ${OBJECTDIR}/_ext/1381494712/driver_examples.o.d 
	@${RM} ${OBJECTDIR}/_ext/1381494712/driver_examples.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1381494712/driver_examples.o.d" -o ${OBJECTDIR}/_ext/1381494712/driver_examples.o ../examples/driver_examples.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_atomic.o: ../hal/src/hal_atomic.c  .generated_files/flags/Release/5dd38c739793489255bf56a951c8813f5ffd88d9 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_atomic.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_atomic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_atomic.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_atomic.o ../hal/src/hal_atomic.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_cache.o: ../hal/src/hal_cache.c  .generated_files/flags/Release/c52643d58ca557ec096895a7f0c7d595a255f91a .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_cache.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_cache.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_cache.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_cache.o ../hal/src/hal_cache.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_delay.o: ../hal/src/hal_delay.c  .generated_files/flags/Release/a58a49a2b51d6f5ebb2b283cc69b7fd575b6c521 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_delay.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_delay.o ../hal/src/hal_delay.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_ext_irq.o: ../hal/src/hal_ext_irq.c  .generated_files/flags/Release/6ad754db27331b4c6d58d4128a4e868d941c55b9 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_ext_irq.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_ext_irq.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_ext_irq.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_ext_irq.o ../hal/src/hal_ext_irq.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_flash.o: ../hal/src/hal_flash.c  .generated_files/flags/Release/9d0b8827e0d477c47a48a8d838cbba349c80397a .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_flash.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_flash.o ../hal/src/hal_flash.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_gpio.o: ../hal/src/hal_gpio.c  .generated_files/flags/Release/c63768739cb2890d7af4dd4f75776b6f101bd531 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_gpio.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_gpio.o ../hal/src/hal_gpio.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_init.o: ../hal/src/hal_init.c  .generated_files/flags/Release/368b6b7a3be7da9676ba8727106e8001524ea101 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_init.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_init.o ../hal/src/hal_init.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_io.o: ../hal/src/hal_io.c  .generated_files/flags/Release/de7636fcd77e8c43a421b792a14c69ba3091d666 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_io.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_io.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_io.o ../hal/src/hal_io.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_rand_sync.o: ../hal/src/hal_rand_sync.c  .generated_files/flags/Release/48e9dbc00c03691fd24f9e27a07b2335163a27bb .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_rand_sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_rand_sync.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_rand_sync.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_rand_sync.o ../hal/src/hal_rand_sync.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_sleep.o: ../hal/src/hal_sleep.c  .generated_files/flags/Release/29ee526a0e53edd5a4ecd4e24f75074ceeb2fba7 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_sleep.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_sleep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_sleep.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_sleep.o ../hal/src/hal_sleep.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_usart_sync.o: ../hal/src/hal_usart_sync.c  .generated_files/flags/Release/81c53cc83052c19285a2e3ed446cc68736c91e10 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_usart_sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_usart_sync.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_usart_sync.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_usart_sync.o ../hal/src/hal_usart_sync.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_usb_device.o: ../hal/src/hal_usb_device.c  .generated_files/flags/Release/d4799490ad2d60add6866bc49a59d795a35a43d6 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_usb_device.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_usb_device.o ../hal/src/hal_usb_device.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/991121639/hal_wdt.o: ../hal/src/hal_wdt.c  .generated_files/flags/Release/16346650b18dd8fa29fade6b2513b5083a6f0f58 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/991121639" 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/991121639/hal_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/991121639/hal_wdt.o.d" -o ${OBJECTDIR}/_ext/991121639/hal_wdt.o ../hal/src/hal_wdt.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/447684357/utils_assert.o: ../hal/utils/src/utils_assert.c  .generated_files/flags/Release/b7cda0212cb4bdd8a56e4831ea2df12ec57c86e2 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/447684357" 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_assert.o.d 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_assert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/447684357/utils_assert.o.d" -o ${OBJECTDIR}/_ext/447684357/utils_assert.o ../hal/utils/src/utils_assert.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/447684357/utils_event.o: ../hal/utils/src/utils_event.c  .generated_files/flags/Release/5fc00e8399d2cf13435d4911698e6b5d5d94b3d3 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/447684357" 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_event.o.d 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_event.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/447684357/utils_event.o.d" -o ${OBJECTDIR}/_ext/447684357/utils_event.o ../hal/utils/src/utils_event.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/447684357/utils_list.o: ../hal/utils/src/utils_list.c  .generated_files/flags/Release/5e7a31701c4cac147ffac63be71c4e2c58c64076 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/447684357" 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_list.o.d 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/447684357/utils_list.o.d" -o ${OBJECTDIR}/_ext/447684357/utils_list.o ../hal/utils/src/utils_list.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/447684357/utils_syscalls.o: ../hal/utils/src/utils_syscalls.c  .generated_files/flags/Release/1d7935b5a972ec301d7e5a12e8b16c4e2e482a91 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/447684357" 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/447684357/utils_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/447684357/utils_syscalls.o.d" -o ${OBJECTDIR}/_ext/447684357/utils_syscalls.o ../hal/utils/src/utils_syscalls.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232827772/hpl_cmcc.o: ../hpl/cmcc/hpl_cmcc.c  .generated_files/flags/Release/fc0f8652fa8ba4bc10543d0c13a16f5d351b0d43 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232827772" 
	@${RM} ${OBJECTDIR}/_ext/232827772/hpl_cmcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/232827772/hpl_cmcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232827772/hpl_cmcc.o.d" -o ${OBJECTDIR}/_ext/232827772/hpl_cmcc.o ../hpl/cmcc/hpl_cmcc.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232825383/hpl_core_m4.o: ../hpl/core/hpl_core_m4.c  .generated_files/flags/Release/42220806e04a33a09bc64db17f37c66839de5ca8 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232825383" 
	@${RM} ${OBJECTDIR}/_ext/232825383/hpl_core_m4.o.d 
	@${RM} ${OBJECTDIR}/_ext/232825383/hpl_core_m4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232825383/hpl_core_m4.o.d" -o ${OBJECTDIR}/_ext/232825383/hpl_core_m4.o ../hpl/core/hpl_core_m4.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232825383/hpl_init.o: ../hpl/core/hpl_init.c  .generated_files/flags/Release/d6ce43485acf8b0c4eea577e970e71076406879d .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232825383" 
	@${RM} ${OBJECTDIR}/_ext/232825383/hpl_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/232825383/hpl_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232825383/hpl_init.o.d" -o ${OBJECTDIR}/_ext/232825383/hpl_init.o ../hpl/core/hpl_init.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232798043/hpl_dmac.o: ../hpl/dmac/hpl_dmac.c  .generated_files/flags/Release/3feff06efd728656a33ca22444fe78356927cc90 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232798043" 
	@${RM} ${OBJECTDIR}/_ext/232798043/hpl_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/232798043/hpl_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232798043/hpl_dmac.o.d" -o ${OBJECTDIR}/_ext/232798043/hpl_dmac.o ../hpl/dmac/hpl_dmac.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/561698107/hpl_eic.o: ../hpl/eic/hpl_eic.c  .generated_files/flags/Release/7009d2caaa2be84186f15c6a687a6b65d4da39e3 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/561698107" 
	@${RM} ${OBJECTDIR}/_ext/561698107/hpl_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/561698107/hpl_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/561698107/hpl_eic.o.d" -o ${OBJECTDIR}/_ext/561698107/hpl_eic.o ../hpl/eic/hpl_eic.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232717931/hpl_gclk.o: ../hpl/gclk/hpl_gclk.c  .generated_files/flags/Release/ea380bbb3eb6cd38ea1a505a310096f7abe76df2 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232717931" 
	@${RM} ${OBJECTDIR}/_ext/232717931/hpl_gclk.o.d 
	@${RM} ${OBJECTDIR}/_ext/232717931/hpl_gclk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232717931/hpl_gclk.o.d" -o ${OBJECTDIR}/_ext/232717931/hpl_gclk.o ../hpl/gclk/hpl_gclk.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232539185/hpl_mclk.o: ../hpl/mclk/hpl_mclk.c  .generated_files/flags/Release/f1b50b5243f411e2aef6ea60ab440bb8c166f14f .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232539185" 
	@${RM} ${OBJECTDIR}/_ext/232539185/hpl_mclk.o.d 
	@${RM} ${OBJECTDIR}/_ext/232539185/hpl_mclk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232539185/hpl_mclk.o.d" -o ${OBJECTDIR}/_ext/232539185/hpl_mclk.o ../hpl/mclk/hpl_mclk.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o: ../hpl/nvmctrl/hpl_nvmctrl.c  .generated_files/flags/Release/83416032c6f9c31bf40ca44c8f989d79a7f4278c .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1639645974" 
	@${RM} ${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1639645974/hpl_nvmctrl.o ../hpl/nvmctrl/hpl_nvmctrl.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o: ../hpl/osc32kctrl/hpl_osc32kctrl.c  .generated_files/flags/Release/f7d4dd06199d695bdf825ae37d50641ae1ef1d41 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/833842894" 
	@${RM} ${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o.d" -o ${OBJECTDIR}/_ext/833842894/hpl_osc32kctrl.o ../hpl/osc32kctrl/hpl_osc32kctrl.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o: ../hpl/oscctrl/hpl_oscctrl.c  .generated_files/flags/Release/b6a90bb0b1501cdb25283824c74524ebdd8b385f .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1862940304" 
	@${RM} ${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o.d" -o ${OBJECTDIR}/_ext/1862940304/hpl_oscctrl.o ../hpl/oscctrl/hpl_oscctrl.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1126497609/hpl_pm.o: ../hpl/pm/hpl_pm.c  .generated_files/flags/Release/499bd734be0eb399e53649e375f3de4b38901e10 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1126497609" 
	@${RM} ${OBJECTDIR}/_ext/1126497609/hpl_pm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1126497609/hpl_pm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1126497609/hpl_pm.o.d" -o ${OBJECTDIR}/_ext/1126497609/hpl_pm.o ../hpl/pm/hpl_pm.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/9468513/hpl_ramecc.o: ../hpl/ramecc/hpl_ramecc.c  .generated_files/flags/Release/d8b5ae59321c4c5cdcac7a31c03097f6cc2b5747 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/9468513" 
	@${RM} ${OBJECTDIR}/_ext/9468513/hpl_ramecc.o.d 
	@${RM} ${OBJECTDIR}/_ext/9468513/hpl_ramecc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/9468513/hpl_ramecc.o.d" -o ${OBJECTDIR}/_ext/9468513/hpl_ramecc.o ../hpl/ramecc/hpl_ramecc.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/41939163/hpl_sercom.o: ../hpl/sercom/hpl_sercom.c  .generated_files/flags/Release/212b23b0efaaab9f9f2e22a621e11c009200f495 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/41939163" 
	@${RM} ${OBJECTDIR}/_ext/41939163/hpl_sercom.o.d 
	@${RM} ${OBJECTDIR}/_ext/41939163/hpl_sercom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/41939163/hpl_sercom.o.d" -o ${OBJECTDIR}/_ext/41939163/hpl_sercom.o ../hpl/sercom/hpl_sercom.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1874121072/hpl_systick.o: ../hpl/systick/hpl_systick.c  .generated_files/flags/Release/65d2a4631c3f40dd3c3e132b50af577a75592b7b .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1874121072" 
	@${RM} ${OBJECTDIR}/_ext/1874121072/hpl_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1874121072/hpl_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1874121072/hpl_systick.o.d" -o ${OBJECTDIR}/_ext/1874121072/hpl_systick.o ../hpl/systick/hpl_systick.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/232316175/hpl_trng.o: ../hpl/trng/hpl_trng.c  .generated_files/flags/Release/47e36a49a97399d0008ad7d200ad8334a814b66e .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/232316175" 
	@${RM} ${OBJECTDIR}/_ext/232316175/hpl_trng.o.d 
	@${RM} ${OBJECTDIR}/_ext/232316175/hpl_trng.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/232316175/hpl_trng.o.d" -o ${OBJECTDIR}/_ext/232316175/hpl_trng.o ../hpl/trng/hpl_trng.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/561682422/hpl_usb.o: ../hpl/usb/hpl_usb.c  .generated_files/flags/Release/7ab85ea45463ac932a61fc28f863ad88d07a7b47 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/561682422" 
	@${RM} ${OBJECTDIR}/_ext/561682422/hpl_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/561682422/hpl_usb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/561682422/hpl_usb.o.d" -o ${OBJECTDIR}/_ext/561682422/hpl_usb.o ../hpl/usb/hpl_usb.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/561680947/hpl_wdt.o: ../hpl/wdt/hpl_wdt.c  .generated_files/flags/Release/4f89a074f8f93994d6fcf3cd1fc6bc6f97900b36 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/561680947" 
	@${RM} ${OBJECTDIR}/_ext/561680947/hpl_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/561680947/hpl_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/561680947/hpl_wdt.o.d" -o ${OBJECTDIR}/_ext/561680947/hpl_wdt.o ../hpl/wdt/hpl_wdt.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o: ../persistent_storage/nv_internal_flash_ultra.c  .generated_files/flags/Release/70df413c1bdca432dd8fdd9d232b8c327aa170cc .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1902934654" 
	@${RM} ${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o.d 
	@${RM} ${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o.d" -o ${OBJECTDIR}/_ext/1902934654/nv_internal_flash_ultra.o ../persistent_storage/nv_internal_flash_ultra.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1902934654/nv_storage.o: ../persistent_storage/nv_storage.c  .generated_files/flags/Release/b89be28e9cf73dfe2f0762f753c3251133e0b029 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1902934654" 
	@${RM} ${OBJECTDIR}/_ext/1902934654/nv_storage.o.d 
	@${RM} ${OBJECTDIR}/_ext/1902934654/nv_storage.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1902934654/nv_storage.o.d" -o ${OBJECTDIR}/_ext/1902934654/nv_storage.o ../persistent_storage/nv_storage.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/565800185/read.o: ../stdio_redirect/gcc/read.c  .generated_files/flags/Release/8c66967d416ae34bbc375d410a38b9b83284c990 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/565800185" 
	@${RM} ${OBJECTDIR}/_ext/565800185/read.o.d 
	@${RM} ${OBJECTDIR}/_ext/565800185/read.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/565800185/read.o.d" -o ${OBJECTDIR}/_ext/565800185/read.o ../stdio_redirect/gcc/read.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/565800185/write.o: ../stdio_redirect/gcc/write.c  .generated_files/flags/Release/e7ae4cde282d3de678c412bd64fffd048a1e9c42 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/565800185" 
	@${RM} ${OBJECTDIR}/_ext/565800185/write.o.d 
	@${RM} ${OBJECTDIR}/_ext/565800185/write.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/565800185/write.o.d" -o ${OBJECTDIR}/_ext/565800185/write.o ../stdio_redirect/gcc/write.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/433002239/stdio_io.o: ../stdio_redirect/stdio_io.c  .generated_files/flags/Release/681ea895bc0428603a25e47eb64cef96ed5c6341 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/433002239" 
	@${RM} ${OBJECTDIR}/_ext/433002239/stdio_io.o.d 
	@${RM} ${OBJECTDIR}/_ext/433002239/stdio_io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/433002239/stdio_io.o.d" -o ${OBJECTDIR}/_ext/433002239/stdio_io.o ../stdio_redirect/stdio_io.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/atmel_start.o: ../atmel_start.c  .generated_files/flags/Release/f0c16a9b03a813eaec24e7aa67403a8665b4e7ef .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/atmel_start.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/atmel_start.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/atmel_start.o.d" -o ${OBJECTDIR}/_ext/1472/atmel_start.o ../atmel_start.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/console.o: ../console.c  .generated_files/flags/Release/dbcba10264e0e4a9d66a61f632d651450f6436a5 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/console.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/console.o.d" -o ${OBJECTDIR}/_ext/1472/console.o ../console.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/driver_init.o: ../driver_init.c  .generated_files/flags/Release/6501c5ea08da256f0547f07446f159fc8e0f30c2 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/driver_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/driver_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/driver_init.o.d" -o ${OBJECTDIR}/_ext/1472/driver_init.o ../driver_init.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/LCD.o: ../LCD.c  .generated_files/flags/Release/1b9a41ad489ddee1e8e8b19449a73d39d76c47e6 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LCD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/LCD.o.d" -o ${OBJECTDIR}/_ext/1472/LCD.o ../LCD.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/LCDBus.o: ../LCDBus.c  .generated_files/flags/Release/bd3921b6d61791c0fae8d86bacef802de641d28d .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LCDBus.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LCDBus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/LCDBus.o.d" -o ${OBJECTDIR}/_ext/1472/LCDBus.o ../LCDBus.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/Release/1e0169de09609154abd2c390c1965b9d3deee8b3 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/persistent_storage_start.o: ../persistent_storage_start.c  .generated_files/flags/Release/9eb5e9823be1a8e655149232f857d777e5eeca19 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/persistent_storage_start.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/persistent_storage_start.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/persistent_storage_start.o.d" -o ${OBJECTDIR}/_ext/1472/persistent_storage_start.o ../persistent_storage_start.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/splash.o: ../splash.c  .generated_files/flags/Release/4d093ac18a4a157c9920ad3946f405801691092a .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/splash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/splash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/splash.o.d" -o ${OBJECTDIR}/_ext/1472/splash.o ../splash.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
${OBJECTDIR}/_ext/1472/stdio_start.o: ../stdio_start.c  .generated_files/flags/Release/131fc86739865a23002c345d6cc965804d8f52a6 .generated_files/flags/Release/3b303312db47ae655ae30f1a4f5c404ded159ca3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/stdio_start.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/stdio_start.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m4  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb  -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/Atmel/SAMD51_DFP/1.2.139/samd51a/include" -I "C:/Program Files/Microchip/MPLABX/v5.50/packs/arm/CMSIS/5.4.0/CMSIS/Core/Include"  -Os -ffunction-sections -mlong-calls -DNDEBUG -I "../Config" -I "../" -I "../examples" -I "../hal/include" -I "../hal/utils/include" -I "../hpl/cmcc" -I "../hpl/core" -I "../hpl/dmac" -I "../hpl/eic" -I "../hpl/gclk" -I "../hpl/mclk" -I "../hpl/nvmctrl" -I "../hpl/osc32kctrl" -I "../hpl/oscctrl" -I "../hpl/pm" -I "../hpl/port" -I "../hpl/ramecc" -I "../hpl/sercom" -I "../hpl/systick" -I "../hpl/trng" -I "../hpl/usb" -I "../hpl/wdt" -I "../hri" -I "../persistent_storage" -I "../stdio_redirect" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/stdio_start.o.d" -o ${OBJECTDIR}/_ext/1472/stdio_start.o ../stdio_start.c  -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=cortex-m4   -gdwarf-2  -D__$(MP_PROCESSOR_OPTION)__    -mthumb --specs=nano.specs -Wl,-Map="dist\${CND_CONF}\${IMAGE_TYPE}\VT69.X.${IMAGE_TYPE}.map"  -o dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1  -L"../Device_Startup" -Wl,--gc-sections  -Wl,-lm  -Tsamd51n19a_flash.ld
	${MP_CC_DIR}\\arm-none-eabi-objcopy -O binary "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.bin"
	
	${MP_CC_DIR}\\arm-none-eabi-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O binary "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.eep" || exit 0
	${MP_CC_DIR}\\arm-none-eabi-objdump -h -S "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.lss"
	${MP_CC_DIR}\\arm-none-eabi-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.srec"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=cortex-m4  -D__$(MP_PROCESSOR_OPTION)__    -mthumb --specs=nano.specs -Wl,-Map="dist\${CND_CONF}\${IMAGE_TYPE}\VT69.X.${IMAGE_TYPE}.map"  -o dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_Release=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)  -L"../Device_Startup" -Wl,--gc-sections  -Wl,-lm  -Tsamd51n19a_flash.ld
	${MP_CC_DIR}\\arm-none-eabi-objcopy -O binary "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.bin"
	${MP_CC_DIR}\\arm-none-eabi-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.hex"
	${MP_CC_DIR}\\arm-none-eabi-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O binary "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.eep" || exit 0
	${MP_CC_DIR}\\arm-none-eabi-objdump -h -S "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.lss"
	${MP_CC_DIR}\\arm-none-eabi-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/VT69.X.${IMAGE_TYPE}.srec"
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} -r dist/Release

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
