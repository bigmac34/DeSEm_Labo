################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include xf/subdir.mk
-include platform/platform-common/board/subdir.mk
-include platform/olimex-stm32f103-stk/mcu/stm32f1xx/system/src/stm32f1-stdperiph/subdir.mk
-include platform/olimex-stm32f103-stk/mcu/stm32f1xx/system/src/newlib/subdir.mk
-include platform/olimex-stm32f103-stk/mcu/stm32f1xx/system/src/diag/subdir.mk
-include platform/olimex-stm32f103-stk/mcu/stm32f1xx/system/src/cortexm/subdir.mk
-include platform/olimex-stm32f103-stk/mcu/stm32f1xx/system/src/cmsis/subdir.mk
-include platform/olimex-stm32f103-stk/mcu/stm32f1xx/hal/subdir.mk
-include platform/olimex-stm32f103-stk/mcu/stm32f1xx/critical/subdir.mk
-include platform/olimex-stm32f103-stk/mcu/subdir.mk
-include platform/olimex-stm32f103-stk/desenet/subdir.mk
-include platform/olimex-stm32f103-stk/board/transceiver/subdir.mk
-include platform/olimex-stm32f103-stk/board/shared-spi/subdir.mk
-include platform/olimex-stm32f103-stk/board/display/subdir.mk
-include platform/olimex-stm32f103-stk/board/accel/subdir.mk
-include platform/olimex-stm32f103-stk/board/subdir.mk
-include platform/olimex-stm32f103-stk/subdir.mk
-include mdw/gui/subdir.mk
-include mdw/desenet/sensor/subdir.mk
-include mdw/desenet/subdir.mk
-include mdw/clockwork/subdir.mk
-include app/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
desenet-sensor.hex \

SECONDARY_SIZE += \
desenet-sensor.siz \


# All Target
all: desenet-sensor.elf secondary-outputs

# Tool invocations
desenet-sensor.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L/home/desem/svn/desem-folders/deployment/desenet-work/desenet-sensor/../desenet-common/platform/olimex-stm32f103-stk/mcu/stm32f1xx/ldscripts -Wl,-Map,"desenet-sensor.map" --specs=nano.specs -o "desenet-sensor.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

desenet-sensor.hex: desenet-sensor.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "desenet-sensor.elf"  "desenet-sensor.hex"
	@echo 'Finished building: $@'
	@echo ' '

desenet-sensor.siz: desenet-sensor.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "desenet-sensor.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(SECONDARY_FLASH)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) desenet-sensor.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
