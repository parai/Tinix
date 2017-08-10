
######################
# Makefile for Tinix #
######################


# Entry point of Tinix
# It must be as same as 'KernelEntryPointPhyAddr' in load.inc!!!
ENTRYPOINT	= 0x30400

# Offset of entry point in kernel file
# It depends on ENTRYPOINT
ENTRYOFFSET	=   0x400


# Programs, flags, etc.
ASM		= nasm
DASM		= ndisasm
CC		= gcc -m32 -fno-stack-protector
LD		= ld -melf_i386
ASMBFLAGS	= -I boot/include
ASMKFLAGS	= -I include -f elf
CFLAGS		= -I include -c -fno-builtin
LDFLAGS		= -s -Ttext $(ENTRYPOINT)
DASMFLAGS	= -u -o $(ENTRYPOINT) -e $(ENTRYOFFSET)

# This Program
TINIXBOOT	= boot/boot.bin boot/loader.bin
TINIXKERNEL	= kernel.bin
OBJS		= kernel/kernel.o kernel/start.o lib/klib.o lib/string.o
DASMOUTPUT	= kernel.bin.asm

# All Phony Targets
.PHONY : everything final image clean realclean disasm all buildimg

# Default starting position
everything : $(TINIXBOOT) $(TINIXKERNEL)

all : realclean everything

final : all clean

image : final buildimg

clean :
	rm -f $(OBJS)

realclean :
	rm -f $(OBJS) $(TINIXBOOT) $(TINIXKERNEL)

disasm :
	$(DASM) $(DASMFLAGS) $(TINIXKERNEL) > $(DASMOUTPUT)

TINIX.IMG:
	dd if=/dev/zero of=$@ bs=512 count=2880
	mkfs.vfat $@

run:
	qemu-system-i386 -fda TINIX.IMG -boot a -m 64M

# Write "boot.bin" & "loader.bin" into floppy image "TINIX.IMG"
# We assume that "TINIX.IMG" exists in current folder
buildimg : TINIX.IMG
	dd conv=notrunc if=boot/boot.bin of=TINIX.IMG bs=512 count=1
	mount TINIX.IMG /mnt/floppy -o loop
	cp -f boot/loader.bin /mnt/floppy/
	cp -f kernel.bin /mnt/floppy
	umount /mnt/floppy

boot/boot.bin : boot/boot.asm boot/include/load.inc boot/include/fat12hdr.inc
	(cd boot; $(ASM) $(ASMBFLAGS) -o $(notdir $@) $(notdir $<))

boot/loader.bin : boot/loader.asm boot/include/load.inc boot/include/fat12hdr.inc boot/include/pm.inc
	(cd boot; $(ASM) $(ASMBFLAGS) -o $(notdir $@) $(notdir $<))

$(TINIXKERNEL) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(TINIXKERNEL) $(OBJS)

kernel/kernel.o : kernel/kernel.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

kernel/start.o : kernel/start.c ./include/type.h ./include/const.h ./include/protect.h
	$(CC) $(CFLAGS) -o $@ $<

lib/klib.o : lib/klib.asm
	(cd lib; $(ASM) $(ASMKFLAGS) -o $(notdir $@) $(notdir $<))

lib/string.o : lib/string.asm
	(cd lib; $(ASM) $(ASMKFLAGS) -o $(notdir $@) $(notdir $<))
