CC := gcc
RM := rm
C_FLAGS := -g -Wall -Wextra
#LINKFLAGS :=

.PHONY: $(TARGET)
.PHONY: clean

VPATH := ./SRC/ ./OBJ/ ./HEAD/

SRC_PATH := ./SRC/
OBJ_PATH := ./OBJ/
INC_PATH := -I ./HEAD

#Exe Name
TARGET := VCM

#Files to Compile
OBJ1 := main.o gpu.o cpu.o mem.o shell.o assembler.o gui.o

OBJ := $(patsubst %,$(OBJ_PATH)%,$(OBJ1))

#build .o files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo [CC] $<
	@$(CC) $(C_FLAGS) -o $@ -c $< $(INC_PATH) -F/Library/Frameworks -framework SDL2

#build binary
$(TARGET): $(OBJ)
	@echo [INFO] CREATING EXECUTABLE [$(TARGET)]
	@$(CC) -o $@ $^ $(LINKFLAGS)

#clean
clean:
	@echo "[CLEANING]"
	@$(RM) -rfv $(OBJ_PATH)*
	@$(RM) -rfv $(TARGET)


