################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ESP_AT_Commands/ESP01.c \
../Src/ESP_AT_Commands/USART_Program.c 

OBJS += \
./Src/ESP_AT_Commands/ESP01.o \
./Src/ESP_AT_Commands/USART_Program.o 

C_DEPS += \
./Src/ESP_AT_Commands/ESP01.d \
./Src/ESP_AT_Commands/USART_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/ESP_AT_Commands/%.o Src/ESP_AT_Commands/%.su Src/ESP_AT_Commands/%.cyclo: ../Src/ESP_AT_Commands/%.c Src/ESP_AT_Commands/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/course/embedded/stm32 workspace/Studemeter/Src/queue" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/RCC" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/GPIO" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/SYSTICK" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/ADC" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/APP" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/USART" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/ESP_AT_Commands" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-ESP_AT_Commands

clean-Src-2f-ESP_AT_Commands:
	-$(RM) ./Src/ESP_AT_Commands/ESP01.cyclo ./Src/ESP_AT_Commands/ESP01.d ./Src/ESP_AT_Commands/ESP01.o ./Src/ESP_AT_Commands/ESP01.su ./Src/ESP_AT_Commands/USART_Program.cyclo ./Src/ESP_AT_Commands/USART_Program.d ./Src/ESP_AT_Commands/USART_Program.o ./Src/ESP_AT_Commands/USART_Program.su

.PHONY: clean-Src-2f-ESP_AT_Commands

