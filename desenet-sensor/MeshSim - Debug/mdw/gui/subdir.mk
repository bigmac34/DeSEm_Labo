################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/gui/fontlookup.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/gui/monochromedisplaypainter.cpp 

OBJS += \
./mdw/gui/fontlookup.o \
./mdw/gui/monochromedisplaypainter.o 

CPP_DEPS += \
./mdw/gui/fontlookup.d \
./mdw/gui/monochromedisplaypainter.d 


# Each subdirectory must supply rules for building sources it contributes
mdw/gui/fontlookup.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/gui/fontlookup.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mdw/gui/monochromedisplaypainter.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/gui/monochromedisplaypainter.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


