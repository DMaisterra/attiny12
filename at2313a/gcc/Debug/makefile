################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
LedBlink.lss \

FLASH_IMAGE += \
LedBlink.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: LedBlink.elf secondary-outputs

# Tool invocations
LedBlink.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,LedBlink.map -mmcu=attiny2313 -o "LedBlink.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

LedBlink.lss: LedBlink.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S -d LedBlink.elf  >"LedBlink.lss"
	@echo 'Finished building: $@'
	@echo ' '

LedBlink.hex: LedBlink.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex LedBlink.elf  "LedBlink.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: LedBlink.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny2313 LedBlink.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) LedBlink.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
