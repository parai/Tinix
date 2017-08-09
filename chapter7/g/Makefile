
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
ASMBFLAGS	= -I ./boot
ASMKFLAGS	= -I include -f elf
CFLAGS		= -I include -c -fno-builtin
LDFLAGS		= -s -Ttext $(ENTRYPOINT)
DASMFLAGS	= -u -o $(ENTRYPOINT) -e $(ENTRYOFFSET)

# This Program
TINIXBOOT	= boot/boot.bin boot/loader.bin
TINIXKERNEL	= kernel.bin
OBJS		= kernel/kernel.o kernel/syscall.o kernel/start.o kernel/main.o\
			kernel/clock.o kernel/i8259.o kernel/global.o kernel/protect.o\
			kernel/proc.o kernel/keyboard.o kernel/tty.o kernel/console.o\
			kernel/printf.o kernel/vsprintf.o\
			lib/klib.o lib/klibc.o lib/string.o
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

boot/boot.bin : boot/boot.asm boot/load.inc boot/fat12hdr.inc
	(cd boot; $(ASM) $(ASMBFLAGS) -o $(notdir $@) $(notdir $<))

boot/loader.bin : boot/loader.asm boot/load.inc boot/fat12hdr.inc boot/pm.inc
	(cd boot; $(ASM) $(ASMBFLAGS) -o $(notdir $@) $(notdir $<))

$(TINIXKERNEL) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(TINIXKERNEL) $(OBJS)

kernel/kernel.o : kernel/kernel.asm include/sconst.inc
	(cd kernel; $(ASM) $(ASMKFLAGS) -o $(notdir $@) $(notdir $<))

kernel/syscall.o : kernel/syscall.asm include/sconst.inc
	(cd kernel; $(ASM) $(ASMKFLAGS) -o $(notdir $@) $(notdir $<))

kernel/start.o: kernel/start.c include/type.h include/const.h include/protect.h include/string.h include/proc.h include/proto.h \
			include/tty.h include/console.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/main.o: kernel/main.c include/type.h include/const.h include/protect.h include/string.h include/proc.h include/proto.h \
			include/tty.h include/console.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/i8259.o: kernel/i8259.c include/type.h include/const.h include/protect.h include/string.h include/proc.h \
			include/tty.h include/console.h include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/global.o: kernel/global.c include/type.h include/const.h include/protect.h include/proc.h \
			include/tty.h include/console.h include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/protect.o: kernel/protect.c include/type.h include/const.h include/protect.h include/proc.h include/proto.h \
			include/tty.h include/console.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/clock.o: kernel/clock.c include/type.h include/const.h include/protect.h include/string.h include/proc.h \
			include/tty.h include/console.h include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/proc.o: kernel/proc.c include/type.h include/const.h include/protect.h include/string.h include/proc.h include/proto.h \
			include/tty.h include/console.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/keyboard.o: kernel/keyboard.c include/type.h include/const.h include/protect.h include/string.h include/proc.h \
			include/tty.h include/console.h include/global.h include/keyboard.h include/keymap.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/tty.o: kernel/tty.c include/type.h include/const.h include/protect.h include/string.h include/proc.h \
			include/tty.h include/console.h include/global.h include/keyboard.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/console.o: kernel/console.c include/type.h include/const.h include/protect.h include/string.h include/proc.h \
			include/tty.h include/console.h include/global.h include/keyboard.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/vsprintf.o: kernel/vsprintf.c include/type.h include/const.h include/string.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/printf.o: kernel/printf.c include/type.h include/const.h
	$(CC) $(CFLAGS) -o $@ $<

lib/klibc.o: lib/klib.c include/type.h include/const.h include/protect.h include/string.h include/proc.h include/proto.h \
			include/tty.h include/console.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

lib/klib.o : lib/klib.asm include/sconst.inc
	(cd lib; $(ASM) $(ASMKFLAGS) -o $(notdir $@) $(notdir $<))

lib/string.o : lib/string.asm
	(cd lib; $(ASM) $(ASMKFLAGS) -o $(notdir $@) $(notdir $<))
