################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc.c \
../Core/Src/breakup.c \
../Core/Src/configuration.c \
../Core/Src/counter.c \
../Core/Src/det_cable.c \
../Core/Src/dma.c \
../Core/Src/extinguisher.c \
../Core/Src/fatfs_sd.c \
../Core/Src/fault.c \
../Core/Src/gpio.c \
../Core/Src/led_operation.c \
../Core/Src/main.c \
../Core/Src/rtc.c \
../Core/Src/sdcard.c \
../Core/Src/service.c \
../Core/Src/spi.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/adc.o \
./Core/Src/breakup.o \
./Core/Src/configuration.o \
./Core/Src/counter.o \
./Core/Src/det_cable.o \
./Core/Src/dma.o \
./Core/Src/extinguisher.o \
./Core/Src/fatfs_sd.o \
./Core/Src/fault.o \
./Core/Src/gpio.o \
./Core/Src/led_operation.o \
./Core/Src/main.o \
./Core/Src/rtc.o \
./Core/Src/sdcard.o \
./Core/Src/service.o \
./Core/Src/spi.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/breakup.d \
./Core/Src/configuration.d \
./Core/Src/counter.d \
./Core/Src/det_cable.d \
./Core/Src/dma.d \
./Core/Src/extinguisher.d \
./Core/Src/fatfs_sd.d \
./Core/Src/fault.d \
./Core/Src/gpio.d \
./Core/Src/led_operation.d \
./Core/Src/main.d \
./Core/Src/rtc.d \
./Core/Src/sdcard.d \
./Core/Src/service.d \
./Core/Src/spi.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L452xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/breakup.cyclo ./Core/Src/breakup.d ./Core/Src/breakup.o ./Core/Src/breakup.su ./Core/Src/configuration.cyclo ./Core/Src/configuration.d ./Core/Src/configuration.o ./Core/Src/configuration.su ./Core/Src/counter.cyclo ./Core/Src/counter.d ./Core/Src/counter.o ./Core/Src/counter.su ./Core/Src/det_cable.cyclo ./Core/Src/det_cable.d ./Core/Src/det_cable.o ./Core/Src/det_cable.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/extinguisher.cyclo ./Core/Src/extinguisher.d ./Core/Src/extinguisher.o ./Core/Src/extinguisher.su ./Core/Src/fatfs_sd.cyclo ./Core/Src/fatfs_sd.d ./Core/Src/fatfs_sd.o ./Core/Src/fatfs_sd.su ./Core/Src/fault.cyclo ./Core/Src/fault.d ./Core/Src/fault.o ./Core/Src/fault.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/led_operation.cyclo ./Core/Src/led_operation.d ./Core/Src/led_operation.o ./Core/Src/led_operation.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rtc.cyclo ./Core/Src/rtc.d ./Core/Src/rtc.o ./Core/Src/rtc.su ./Core/Src/sdcard.cyclo ./Core/Src/sdcard.d ./Core/Src/sdcard.o ./Core/Src/sdcard.su ./Core/Src/service.cyclo ./Core/Src/service.d ./Core/Src/service.o ./Core/Src/service.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32l4xx_hal_msp.cyclo ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.cyclo ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src

