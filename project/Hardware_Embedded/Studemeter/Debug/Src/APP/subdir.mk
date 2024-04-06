################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/APP.c 

OBJS += \
./Src/APP/APP.o 

C_DEPS += \
./Src/APP/APP.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/%.o Src/APP/%.su Src/APP/%.cyclo: ../Src/APP/%.c Src/APP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/course/embedded/stm32 workspace/Studemeter/Src/queue" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/RCC" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/GPIO" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/SYSTICK" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/ADC" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/APP" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/USART" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/ESP_AT_Commands" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-APP

clean-Src-2f-APP:
	-$(RM) ./Src/APP/APP.cyclo ./Src/APP/APP.d ./Src/APP/APP.o ./Src/APP/APP.su

.PHONY: clean-Src-2f-APP

