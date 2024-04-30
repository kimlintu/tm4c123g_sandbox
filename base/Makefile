# this Makefile was derived from gcc-arm documentation
# see the documenets in gcc-arm/share/doc/gcc-arm-none-eabi

PROJECT=$(notdir $(CURDIR))

BUILD_DIR=out/
SRC_DIR=src/strt/
INC_DIR=inc/strt/

PREFIX=arm-none-eabi
CC=$(PREFIX)-gcc
LD=$(PREFIX)-ld
AS=$(PREFIX)-as

ARCH_FLAGS=-mthumb	\
	-mcpu=cortex-m4	\
	-mfloat-abi=hard\
	-mfpu=fpv4-sp-d16

DEBUG_FLAGS=-g		\
	-gdwarf-3	\
	-gstrict-dwarf	\
	-DDEBUG

MAP=--Map=$(BUILD_DIR)$(PROJECT).map
GC=--gc-sections
LDSCRIPTS=-Lld -T linker.ld

# variables used by make's builtin rules
CFLAGS=$(ARCH_FLAGS) $(DEBUG_FLAGS) -I$(INC_DIR)
ASFLAGS=$(ARCH_FLAGS)
LDFLAGS=$(LDSCRIPTS) $(MAP) $(GC)

SRC_FILES=$(wildcard $(SRC_DIR)*.c)
#take the base name of the file, add the suffix, remove the directory, and replace it with the build dir
ASMS=$(addprefix $(BUILD_DIR), $(notdir $(addsuffix .s, $(basename $(SRC_FILES)))))
OBJS=$(addprefix $(BUILD_DIR), $(notdir $(addsuffix .o, $(basename $(SRC_FILES)))))

EXE=$(BUILD_DIR)$(PROJECT).elf

all: $(EXE)

asm: $(ASMS)

obj: $(OBJS)

$(BUILD_DIR)%.s: $(SRC_DIR)%.c
	$(CC) -S $(CFLAGS) -o $@ $<

$(BUILD_DIR)%.o: $(BUILD_DIR)%.s
	$(AS) $(ASFLAGS) -o $@ $<

#$(EXE): $(OBJS)
#	$(LD) $(LDFLAGS) -o $@ $(OBJS)
#	arm-none-eabi-objcopy -I elf32-littlearm -O binary $(EXE) $(BUILD_DIR)$(PROJECT).bin

clean:
	rm -rf $(BUILD_DIR)

print:
	@echo $(CFLAGS)
	@echo $(ASFLAGS)
	@echo $(LDFLAGS)
	@echo $(SRC_FILES)
	@echo $(ASMS)
	@echo $(OBJS)

.PHONY: clean print

