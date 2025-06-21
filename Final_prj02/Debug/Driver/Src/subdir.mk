################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Driver/Src/Device.cpp \
../Driver/Src/Room.cpp 

C_SRCS += \
../Driver/Src/74HC595.c \
../Driver/Src/Delay.c \
../Driver/Src/GPIO.c \
../Driver/Src/I2C.c \
../Driver/Src/LCD1602.c \
../Driver/Src/MPU6050.c \
../Driver/Src/SPI.c \
../Driver/Src/USART.c \
../Driver/Src/fonts.c \
../Driver/Src/ili9341.c \
../Driver/Src/stm32f411.c 

C_DEPS += \
./Driver/Src/74HC595.d \
./Driver/Src/Delay.d \
./Driver/Src/GPIO.d \
./Driver/Src/I2C.d \
./Driver/Src/LCD1602.d \
./Driver/Src/MPU6050.d \
./Driver/Src/SPI.d \
./Driver/Src/USART.d \
./Driver/Src/fonts.d \
./Driver/Src/ili9341.d \
./Driver/Src/stm32f411.d 

OBJS += \
./Driver/Src/74HC595.o \
./Driver/Src/Delay.o \
./Driver/Src/Device.o \
./Driver/Src/GPIO.o \
./Driver/Src/I2C.o \
./Driver/Src/LCD1602.o \
./Driver/Src/MPU6050.o \
./Driver/Src/Room.o \
./Driver/Src/SPI.o \
./Driver/Src/USART.o \
./Driver/Src/fonts.o \
./Driver/Src/ili9341.o \
./Driver/Src/stm32f411.o 

CPP_DEPS += \
./Driver/Src/Device.d \
./Driver/Src/Room.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Src/%.o Driver/Src/%.su Driver/Src/%.cyclo: ../Driver/Src/%.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411VETx -DSTM32 -DSTM32F4 -c -I../Inc -I"C:/Users/Administrator/STM32CubeIDE/workspace_1.18.1/Final_prj02/Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Driver/Src/%.o Driver/Src/%.su Driver/Src/%.cyclo: ../Driver/Src/%.cpp Driver/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DSTM32F411VETx -DSTM32 -DSTM32F4 -c -I../Inc -I"C:/Users/Administrator/STM32CubeIDE/workspace_1.18.1/Final_prj02/Driver/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Src

clean-Driver-2f-Src:
	-$(RM) ./Driver/Src/74HC595.cyclo ./Driver/Src/74HC595.d ./Driver/Src/74HC595.o ./Driver/Src/74HC595.su ./Driver/Src/Delay.cyclo ./Driver/Src/Delay.d ./Driver/Src/Delay.o ./Driver/Src/Delay.su ./Driver/Src/Device.cyclo ./Driver/Src/Device.d ./Driver/Src/Device.o ./Driver/Src/Device.su ./Driver/Src/GPIO.cyclo ./Driver/Src/GPIO.d ./Driver/Src/GPIO.o ./Driver/Src/GPIO.su ./Driver/Src/I2C.cyclo ./Driver/Src/I2C.d ./Driver/Src/I2C.o ./Driver/Src/I2C.su ./Driver/Src/LCD1602.cyclo ./Driver/Src/LCD1602.d ./Driver/Src/LCD1602.o ./Driver/Src/LCD1602.su ./Driver/Src/MPU6050.cyclo ./Driver/Src/MPU6050.d ./Driver/Src/MPU6050.o ./Driver/Src/MPU6050.su ./Driver/Src/Room.cyclo ./Driver/Src/Room.d ./Driver/Src/Room.o ./Driver/Src/Room.su ./Driver/Src/SPI.cyclo ./Driver/Src/SPI.d ./Driver/Src/SPI.o ./Driver/Src/SPI.su ./Driver/Src/USART.cyclo ./Driver/Src/USART.d ./Driver/Src/USART.o ./Driver/Src/USART.su ./Driver/Src/fonts.cyclo ./Driver/Src/fonts.d ./Driver/Src/fonts.o ./Driver/Src/fonts.su ./Driver/Src/ili9341.cyclo ./Driver/Src/ili9341.d ./Driver/Src/ili9341.o ./Driver/Src/ili9341.su ./Driver/Src/stm32f411.cyclo ./Driver/Src/stm32f411.d ./Driver/Src/stm32f411.o ./Driver/Src/stm32f411.su

.PHONY: clean-Driver-2f-Src

