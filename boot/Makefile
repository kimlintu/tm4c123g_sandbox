
BUILD_DIR=out/
SRC_DIR=src/

ARCH_FLAGS=-mthumb	\
	-mcpu=cortex-m4	\
	-mfloat-abi=hard\
	-mfpu=fpv4-sp-d16

LDSCRIPTS=--library-path ld --script linker.ld

CFLAGS=$(ARCH_FLAGS) -g -D DEBUG
ASFLAGS=$(ARCH_FLAGS)
LDFLAGS=$(LDSCRIPTS) --Map=$(BUILD_DIR)boot.map --gc-sections

EXE_ELF=$(BUILD_DIR)boot.elf
EXE_BIN=$(BUILD_DIR)boot.bin

SRC_FILES=$(wildcard $(SRC_DIR)*.c)
OBJS=$(addprefix $(BUILD_DIR), $(notdir $(addsuffix .o, $(basename $(SRC_FILES)))))

all: $(EXE_BIN)

# Assembly
.SECONDARY:
$(BUILD_DIR)%.s: $(SRC_DIR)%.c
	arm-none-eabi-gcc -S $(CFLAGS) -o $@ $<

# Object file (ELF)
$(BUILD_DIR)%.o: $(BUILD_DIR)%.s
	arm-none-eabi-as $(ASFLAGS) -o $@ $<

# Link the final executable
$(EXE_ELF): $(OBJS)
	arm-none-eabi-ld $(LDFLAGS) -o $(EXE_ELF) $(OBJS)

$(EXE_BIN): $(EXE_ELF)
	arm-none-eabi-objcopy -I elf32-littlearm -O binary $(EXE_ELF) $(EXE_BIN) 

clean:
	rm -rf $(BUILD_DIR)