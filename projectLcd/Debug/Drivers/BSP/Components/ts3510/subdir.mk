################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/ts3510/ts3510.c 

OBJS += \
./Drivers/BSP/Components/ts3510/ts3510.o 

C_DEPS += \
./Drivers/BSP/Components/ts3510/ts3510.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/ts3510/%.o: ../Drivers/BSP/Components/ts3510/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F746xx -I"E:/Documents/F7 Projects/projectLcd/Drivers/BSP/STM32746G-Discovery" -I"E:/Documents/F7 Projects/projectLcd/Drivers/BSP/Utilities/Fonts" -I"E:/Documents/F7 Projects/projectLcd/Inc" -I"E:/Documents/F7 Projects/projectLcd/Drivers/STM32F7xx_HAL_Driver/Inc" -I"E:/Documents/F7 Projects/projectLcd/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"E:/Documents/F7 Projects/projectLcd/Drivers/CMSIS/Include" -I"E:/Documents/F7 Projects/projectLcd/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/Documents/F7 Projects/projectLcd/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


