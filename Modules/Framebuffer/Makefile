Compiler := gcc

Cflg := \
-std=c11 \
-ffreestanding \
-fno-stack-protector \
-fno-stack-check \
-fno-lto \
-fno-pie \
-fno-builtin \
-fno-omit-frame-pointer \
-mno-red-zone \
-mno-mmx \
-mno-sse \
-mno-sse2 \
-mno-sse3 \
-mno-ssse3 \
-mno-sse4.1 \
-mno-sse4.2 \
-mno-sse4 \
-mno-avx \
-mno-avx2 \
-mno-80387 \
-m64 \
-march=x86-64 \
-mcmodel=kernel \
-mcmodel=large \
-Wall \
-Wextra \
-Werror \
-Wno-unused-parameter \
-Wno-unused-variable \
-O2 \
-g \
-I../../Core/Headers \
-I../Includes \
-I../Libraries/Includes

FinalTemp := ../.Build
LocalTemp := .Build

ModuleName := Framebuffer.ko
InstallPath := $(LocalTemp)

EXTERNAL_LIB ?= ../Libraries/.Build/DEF_Library.a

Cs := $(shell find . -type f -name "*.c")
Os := $(patsubst ./%.c,$(LocalTemp)/%.o,$(Cs))

.PHONY: \
	all \
	clean

all: $(InstallPath)/$(ModuleName)

$(LocalTemp)/%.o: %.c
	@mkdir -p $(dir $@)
	$(Compiler) $(Cflg) -c $< -o $@

$(InstallPath)/$(ModuleName): $(Os)
	@mkdir -p $(InstallPath)
	$(Compiler) -nostdlib -r -o $@ $(Os) $(EXTERNAL_LIB)

clean:
	@rm -rf $(LocalTemp)
	@rm -f $(InstallPath)/$(ModuleName)
