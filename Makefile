NAME := kfs-1.iso

# Compilers
CC :=	gcc
ASM :=	nasm
#

# Flags
CFLAGS :=	-fno-builtin -fno-rtti -fno-stack-protector -nostdlib -nodefaultlibs
ASMFLAGS :=
#

# Sources
C_SRCS :=	src/main.c\

ASM_SRCS :=	src/boot.asm\
#

# Config
LINKER := cfg/linker.ld
GRUB_CFG := cfg/grub.cfg
#

BUILD_DIR := build

# Objects
OBJ_DIR :=	$(BUILD_DIR)/obj
C_OBJS :=	$(C_SRCS:%.c=$(OBJ_DIR)/%.o)
ASM_OBJS :=	$(ASM_SRCS:%.asm=$(OBJ_DIR)/%.o)
#

all: $(NAME)

# Should link all objects and create the .iso
$(NAME): $(C_OBJS) $(ASM_OBJS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo Compiling $@

$(OBJ_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	@echo Compiling $@

re: fclean compile

fclean: clean
	@echo Removed $(NAME)
	@rm -rf $(NAME)

clean:
	@echo Removed $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)

.PHONY: all clean fclean re compile
