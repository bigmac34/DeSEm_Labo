################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/desenet/MultiPDU.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/desenet/beacon.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/desenet/frame.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/desenet/networkinterfacedriver.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/desenet/networktimeprovider.cpp 

OBJS += \
./mdw/desenet/MultiPDU.o \
./mdw/desenet/beacon.o \
./mdw/desenet/frame.o \
./mdw/desenet/networkinterfacedriver.o \
./mdw/desenet/networktimeprovider.o 

CPP_DEPS += \
./mdw/desenet/MultiPDU.d \
./mdw/desenet/beacon.d \
./mdw/desenet/frame.d \
./mdw/desenet/networkinterfacedriver.d \
./mdw/desenet/networktimeprovider.d 


# Each subdirectory must supply rules for building sources it contributes
mdw/desenet/MultiPDU.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/desenet/MultiPDU.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mdw/desenet/beacon.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/desenet/beacon.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mdw/desenet/frame.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/desenet/frame.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mdw/desenet/networkinterfacedriver.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/desenet/networkinterfacedriver.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mdw/desenet/networktimeprovider.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/mdw/desenet/networktimeprovider.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


