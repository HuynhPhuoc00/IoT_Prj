################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/Src/Delay.c \
../Lib/Src/GPIO.c \
../Lib/Src/I2C.c \
../Lib/Src/MPU6050.c \
../Lib/Src/SPI.c \
../Lib/Src/USART.c \
../Lib/Src/stm32f411.c 

C_DEPS += \
./Lib/Src/Delay.d \
./Lib/Src/GPIO.d \
./Lib/Src/I2C.d \
./Lib/Src/MPU6050.d \
./Lib/Src/SPI.d \
./Lib/Src/USART.d \
./Lib/Src/stm32f411.d 

OBJS += \
./Lib/Src/Delay.o \
./Lib/Src/GPIO.o \
./Lib/Src/I2C.o \
./Lib/Src/MPU6050.o \
./Lib/Src/SPI.o \
./Lib/Src/USART.o \
./Lib/Src/stm32f411.o 


# Each subdirectory must supply rules for building sources it contributes
Lib/Src/%.o Lib/Src/%.su Lib/Src/%.cyclo: ../Lib/Src/%.c Lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411VETx -DSTM32 -DSTM32F4 -c -I../Inc -I"C:/Users/Administrator/STM32CubeIDE/workspace_1.18.1/Final_Prj/Lib/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib-2f-Src

clean-Lib-2f-Src:
	-$(RM) ./Lib/Src/Delay.cyclo ./Lib/Src/Delay.d ./Lib/Src/Delay.o ./Lib/Src/Delay.su ./Lib/Src/GPIO.cyclo ./Lib/Src/GPIO.d ./Lib/Src/GPIO.o ./Lib/Src/GPIO.su ./Lib/Src/I2C.cyclo ./Lib/Src/I2C.d ./Lib/Src/I2C.o ./Lib/Src/I2C.su ./Lib/Src/MPU6050.cyclo ./Lib/Src/MPU6050.d ./Lib/Src/MPU6050.o ./Lib/Src/MPU6050.su ./Lib/Src/SPI.cyclo ./Lib/Src/SPI.d ./Lib/Src/SPI.o ./Lib/Src/SPI.su ./Lib/Src/USART.cyclo ./Lib/Src/USART.d ./Lib/Src/USART.o ./Lib/Src/USART.su ./Lib/Src/stm32f411.cyclo ./Lib/Src/stm32f411.d ./Lib/Src/stm32f411.o ./Lib/Src/stm32f411.su

.PHONY: clean-Lib-2f-Src

