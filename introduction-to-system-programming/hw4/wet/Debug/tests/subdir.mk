################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tests/EscapeRoomWrapper_test.cpp \
../tests/enigma_test.cpp \
../tests/list_test.cpp \
../tests/node_test.cpp 

OBJS += \
./tests/EscapeRoomWrapper_test.o \
./tests/enigma_test.o \
./tests/list_test.o \
./tests/node_test.o 

CPP_DEPS += \
./tests/EscapeRoomWrapper_test.d \
./tests/enigma_test.d \
./tests/list_test.d \
./tests/node_test.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ../tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -pedantic-errors -Wall -Werror -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


