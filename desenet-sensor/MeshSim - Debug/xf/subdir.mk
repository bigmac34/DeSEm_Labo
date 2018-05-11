################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/initialevent.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xf.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xfevent.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xfnulltransition.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xfreactive.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xfstaticevent.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xfthread.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xftimeout.cpp \
/mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xftimeoutmanager.cpp 

OBJS += \
./xf/initialevent.o \
./xf/xf.o \
./xf/xfevent.o \
./xf/xfnulltransition.o \
./xf/xfreactive.o \
./xf/xfstaticevent.o \
./xf/xfthread.o \
./xf/xftimeout.o \
./xf/xftimeoutmanager.o 

CPP_DEPS += \
./xf/initialevent.d \
./xf/xf.d \
./xf/xfevent.d \
./xf/xfnulltransition.d \
./xf/xfreactive.d \
./xf/xfstaticevent.d \
./xf/xfthread.d \
./xf/xftimeout.d \
./xf/xftimeoutmanager.d 


# Each subdirectory must supply rules for building sources it contributes
xf/initialevent.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/initialevent.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

xf/xf.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xf.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

xf/xfevent.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xfevent.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

xf/xfnulltransition.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xfnulltransition.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

xf/xfreactive.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xfreactive.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

xf/xfstaticevent.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xfstaticevent.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

xf/xfthread.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xfthread.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

xf/xftimeout.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xftimeout.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

xf/xftimeoutmanager.o: /mnt/hgfs/DeSEm/desenet-work/desenet-common/xf/xftimeoutmanager.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DDEBUG -DTC_MESHSIM -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/app -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/xf -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-sensor -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/mdw/desenet -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/platform-common/board -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/mcu -I/mnt/hgfs/DeSEm/desenet-work/desenet-sensor/../desenet-common/platform/linux-meshsim/board -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


