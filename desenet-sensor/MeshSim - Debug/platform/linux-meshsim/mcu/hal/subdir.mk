################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/platform/linux-meshsim/mcu/hal/timeslotmanager.cpp 

OBJS += \
./platform/linux-meshsim/mcu/hal/timeslotmanager.o 

CPP_DEPS += \
./platform/linux-meshsim/mcu/hal/timeslotmanager.d 


# Each subdirectory must supply rules for building sources it contributes
platform/linux-meshsim/mcu/hal/timeslotmanager.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/platform/linux-meshsim/mcu/hal/timeslotmanager.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


