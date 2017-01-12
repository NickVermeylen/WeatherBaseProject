################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Utilities/Fonts/font12.c \
../Drivers/BSP/Utilities/Fonts/font16.c \
../Drivers/BSP/Utilities/Fonts/font20.c \
../Drivers/BSP/Utilities/Fonts/font24.c \
../Drivers/BSP/Utilities/Fonts/font8.c 

OBJS += \
./Drivers/BSP/Utilities/Fonts/font12.o \
./Drivers/BSP/Utilities/Fonts/font16.o \
./Drivers/BSP/Utilities/Fonts/font20.o \
./Drivers/BSP/Utilities/Fonts/font24.o \
./Drivers/BSP/Utilities/Fonts/font8.o 

C_DEPS += \
./Drivers/BSP/Utilities/Fonts/font12.d \
./Drivers/BSP/Utilities/Fonts/font16.d \
./Drivers/BSP/Utilities/Fonts/font20.d \
./Drivers/BSP/Utilities/Fonts/font24.d \
./Drivers/BSP/Utilities/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Utilities/Fonts/%.o: ../Drivers/BSP/Utilities/Fonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F746xx -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Inc" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/src/include" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/system" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Drivers/STM32F7xx_HAL_Driver/Inc" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/src/include/lwip" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/src/include/netif" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/src/include/netif/ppp/polarssl" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/src/include/posix" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Middlewares/Third_Party/LwIP/system/arch" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Drivers/CMSIS/Include" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Drivers/BSP/STM32746G-Discovery" -I"E:/Documents/F7 Projects/WeatherBaseProject/weatherBase/Drivers/BSP/Utilities/Fonts"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


