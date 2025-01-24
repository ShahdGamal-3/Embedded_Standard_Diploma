################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Control.c \
../Control_main.c \
../buzzer.c \
../dc_motor.c \
../external_eeprom.c \
../gpio.c \
../pir_sensor.c \
../timer.c \
../twi.c \
../uart.c 

OBJS += \
./Control.o \
./Control_main.o \
./buzzer.o \
./dc_motor.o \
./external_eeprom.o \
./gpio.o \
./pir_sensor.o \
./timer.o \
./twi.o \
./uart.o 

C_DEPS += \
./Control.d \
./Control_main.d \
./buzzer.d \
./dc_motor.d \
./external_eeprom.d \
./gpio.d \
./pir_sensor.d \
./timer.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


