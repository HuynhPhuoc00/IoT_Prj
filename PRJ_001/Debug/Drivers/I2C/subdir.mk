################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/I2C/I2C_u.c 

C_DEPS += \
./Drivers/I2C/I2C_u.d 

OBJS += \
./Drivers/I2C/I2C_u.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/I2C/%.o Drivers/I2C/%.su Drivers/I2C/%.cyclo: ../Drivers/I2C/%.c Drivers/I2C/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-I2C

clean-Drivers-2f-I2C:
	-$(RM) ./Drivers/I2C/I2C_u.cyclo ./Drivers/I2C/I2C_u.d ./Drivers/I2C/I2C_u.o ./Drivers/I2C/I2C_u.su

.PHONY: clean-Drivers-2f-I2C

