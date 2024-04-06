################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GPIO/GPIO_Program.c 

OBJS += \
./Src/GPIO/GPIO_Program.o 

C_DEPS += \
./Src/GPIO/GPIO_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/GPIO/%.o Src/GPIO/%.su Src/GPIO/%.cyclo: ../Src/GPIO/%.c Src/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/course/embedded/stm32 workspace/Studemeter/Src/queue" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/RCC" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/GPIO" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/SYSTICK" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/ADC" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/APP" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/USART" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/ESP_AT_Commands" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-GPIO

clean-Src-2f-GPIO:
	-$(RM) ./Src/GPIO/GPIO_Program.cyclo ./Src/GPIO/GPIO_Program.d ./Src/GPIO/GPIO_Program.o ./Src/GPIO/GPIO_Program.su

.PHONY: clean-Src-2f-GPIO

