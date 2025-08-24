################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/74HC/74HC595.c 

C_DEPS += \
./Drivers/74HC/74HC595.d 

OBJS += \
./Drivers/74HC/74HC595.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/74HC/%.o Drivers/74HC/%.su Drivers/74HC/%.cyclo: ../Drivers/74HC/%.c Drivers/74HC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-74HC

clean-Drivers-2f-74HC:
	-$(RM) ./Drivers/74HC/74HC595.cyclo ./Drivers/74HC/74HC595.d ./Drivers/74HC/74HC595.o ./Drivers/74HC/74HC595.su

.PHONY: clean-Drivers-2f-74HC

