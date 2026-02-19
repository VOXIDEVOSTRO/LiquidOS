Compiler := gcc
AR := ar

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
-IIncludes

FinalTemp := ../.Build
LocalTemp := .Build

ModuleName := LIB_Dependencies.a
InstallPath := $(LocalTemp)

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
	$(AR) rcs $@ $(Os)

clean:
	@rm -rf $(LocalTemp)
	@rm -f $(InstallPath)/$(ModuleName)
