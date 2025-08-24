################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32/stm32f411.c 

C_DEPS += \
./Drivers/STM32/stm32f411.d 

OBJS += \
./Drivers/STM32/stm32f411.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32/%.o Drivers/STM32/%.su Drivers/STM32/%.cyclo: ../Drivers/STM32/%.c Drivers/STM32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32

clean-Drivers-2f-STM32:
	-$(RM) ./Drivers/STM32/stm32f411.cyclo ./Drivers/STM32/stm32f411.d ./Drivers/STM32/stm32f411.o ./Drivers/STM32/stm32f411.su

.PHONY: clean-Drivers-2f-STM32

