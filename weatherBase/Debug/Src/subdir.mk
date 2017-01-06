################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ethernetif.c \
../Src/lwip.c \
../Src/main.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_it.c 

OBJS += \
./Src/ethernetif.o \
./Src/lwip.o \
./Src/main.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_it.o 

C_DEPS += \
./Src/ethernetif.d \
./Src/lwip.d \
./Src/main.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F746xx -I"E:/Documents/F7 Projects/weatherBase/Inc" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/src/include" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/system" -I"E:/Documents/F7 Projects/weatherBase/Drivers/STM32F7xx_HAL_Driver/Inc" -I"E:/Documents/F7 Projects/weatherBase/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/src/include/lwip" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/src/include/netif" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/src/include/netif/ppp/polarssl" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/src/include/posix" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"E:/Documents/F7 Projects/weatherBase/Middlewares/Third_Party/LwIP/system/arch" -I"E:/Documents/F7 Projects/weatherBase/Drivers/CMSIS/Include" -I"E:/Documents/F7 Projects/weatherBase/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/Documents/F7 Projects/weatherBase/Drivers/BSP/STM32746G-Discovery" -I"E:/Documents/F7 Projects/weatherBase/Drivers/BSP/Utilities/Fonts"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


