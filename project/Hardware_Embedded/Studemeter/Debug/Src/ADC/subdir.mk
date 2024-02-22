################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ADC/ADC_program.c 

OBJS += \
./Src/ADC/ADC_program.o 

C_DEPS += \
./Src/ADC/ADC_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/ADC/%.o Src/ADC/%.su Src/ADC/%.cyclo: ../Src/ADC/%.c Src/ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"D:/course/embedded/stm32 workspace/Studemeter/Src/queue" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/RCC" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/GPIO" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/SYSTICK" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/ADC" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/APP" -I"D:/course/embedded/stm32 workspace/Studemeter/Src/USART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-ADC

clean-Src-2f-ADC:
	-$(RM) ./Src/ADC/ADC_program.cyclo ./Src/ADC/ADC_program.d ./Src/ADC/ADC_program.o ./Src/ADC/ADC_program.su

.PHONY: clean-Src-2f-ADC

