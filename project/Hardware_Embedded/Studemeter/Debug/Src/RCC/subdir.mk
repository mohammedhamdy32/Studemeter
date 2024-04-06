################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/RCC/RCC_program.c 

OBJS += \
./Src/RCC/RCC_program.o 

C_DEPS += \
./Src/RCC/RCC_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/RCC/%.o Src/RCC/%.su Src/RCC/%.cyclo: ../Src/RCC/%.c Src/RCC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/course/embedded/stm32 workspace/Studemeter/Src/queue" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/RCC" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/GPIO" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/SYSTICK" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/ADC" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/APP" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/USART" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/ESP_AT_Commands" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-RCC

clean-Src-2f-RCC:
	-$(RM) ./Src/RCC/RCC_program.cyclo ./Src/RCC/RCC_program.d ./Src/RCC/RCC_program.o ./Src/RCC/RCC_program.su

.PHONY: clean-Src-2f-RCC

