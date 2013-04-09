################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../old/DTMC.c \
../old/DT_Battery.c \
../old/DT_MotorControl.c 

OBJS += \
./old/DTMC.o \
./old/DT_Battery.o \
./old/DT_MotorControl.o 

C_DEPS += \
./old/DTMC.d \
./old/DT_Battery.d \
./old/DT_MotorControl.d 


# Each subdirectory must supply rules for building sources it contributes
old/%.o: ../old/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


