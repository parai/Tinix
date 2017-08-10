# Tinix

* Tinix on ubunut 14.04

This is a series of course that teach you how to step by step writing an Operation System, Here I give the usefull comand line that how to build,run and debug on ubuntu machine, also some updates of the build scripts as the original does't works now as too old.

## chapter1 build and debug cmdline

* sudo apt-get install nasm

```sh
  cd chapter1/x # x is either a or b
  nasm -o boot.bin boot.asm

  # generated a bootable floppy image
  dd if=/dev/zero of=TINIX.IMG bs=512 count=2880
  sudo mkfs.vfat TINIX.IMG
  dd conv=notrunc if=boot.bin of=TINIX.IMG bs=512 count=1

  # use qemu to run
  qemu-system-i386 -fda TINIX.IMG -boot a -m 64M

  # if want to debug
  qemu-system-i386 -fda TINIX.IMG -boot a -m 64M -s -S &
  echo "target remote:1234" > ~/.gdbinit
  echo "layout asm" >> ~/.gdbinit
  echo "b *0x7c00" >> ~/.gdbinit
  echo "c" >> ~/.gdbinit
  gdb
  # then input si to step asm code
```

## chapter 3 build and debug cmdline

* sudo apt-get install dosemu # this doesn't works

* install qemu [freeDos](http://joelinoff.com/blog/?p=431) # this also not works

```sh
  mkdir ~/freedos
  cd ~/freedos
  wget http://www.freedos.org/freedos/files/download/fd11src.iso
  dd if=/dev/zero of=fdos11.img bs=1M count=1023
  qemu-system-i386 -cdrom fd11src.iso fdos11.img -boot d
  # and then in the pop up window, select install it step by step according to page [freeDos](http://joelinoff.com/blog/?p=431)
```

* install [MS-DOS](https://winworldpc.com/product/ms-dos/622) # this works, for chapter3/a, a RED "P" charactor will be displayed.

```sh
  mkdir ~/msdos
  cd ~/msdos
  # cpoy the the download "MS-DOS 6.22 VHD.vhd"  here as msdos.vhd
```
* debug 

```sh
  nasm -o pmtest.com pmtest*.asm # * means 1/2/3/4/5/6... according to each chapter
  # cp pmtest.com  ~/.dosemu/drive_c/
  # dosemu
  mkdir -p tmp
  dd if=/dev/zero of=TINIX.IMG bs=512 count=2880
  sudo mkfs.vfat TINIX.IMG
  sudo mount -t vfat TINIX.IMG tmp
  sudo cp pmtest.com tmp
  sudo umount tmp
  # qemu-system-i386  -hdc ~/freedos/fdos11.img -boot c -fda TINIX.IMG
  qemu-system-i386 -hdc ~/msdos/msdos.vhd -boot c -fda TINIX.IMG
  # then in the pop up window input A:\pmtest.com
  C:\> cls
  C:\> A:\pmtest.com
```

## chapter 4 build and debug cmdline

* for chapter4 a, the same chapter1

* for chapter4 b&c

```sh
  nasm -o boot.bin boot.asm
  nasm -o loader.bin loader.asm
  # generated a bootable floppy image
  dd if=/dev/zero of=TINIX.IMG bs=512 count=2880
  sudo mkfs.vfat TINIX.IMG
  dd conv=notrunc if=boot.bin of=TINIX.IMG bs=512 count=1
  mkdir -p tmp
  sudo mount -t vfat TINIX.IMG tmp
  sudo cp loader.bin tmp
  sudo umount tmp

  # use qemu to run
  qemu-system-i386 -fda TINIX.IMG -boot a -m 64M

```

## chapter 5 build and debug cmdline

* for a

```sh
  nasm -f elf hello.asm -o hello.o
  ld -melf_i386 -s hello.o -o hello.exe
  ./hello.exe
```

* for b

```sh
  nasm -f elf foo.asm -o foo.o
  gcc -m32 -fno-stack-protector -fno-builtin -c bar.c -o bar.o
  ld -melf_i386 -s foo.o bar.o -o foobar.exe
  ./foobar.exe
```

* for c & d & e

```sh
  nasm -o boot.bin boot.asm
  nasm -o loader.bin loader.asm
  nasm -f elf kernel.asm -o kernel.o
  ld -melf_i386 -s -Ttext 0x30400 kernel.o -o kernel.bin
  # generated a bootable floppy image
  dd if=/dev/zero of=TINIX.IMG bs=512 count=2880
  sudo mkfs.vfat TINIX.IMG
  dd conv=notrunc if=boot.bin of=TINIX.IMG bs=512 count=1
  mkdir -p tmp
  sudo mount -t vfat TINIX.IMG tmp
  sudo cp loader.bin kernel.bin tmp
  sudo umount tmp

  # use qemu to run
  qemu-system-i386 -fda TINIX.IMG -boot a -m 64M
```

* for g

```sh
  nasm -o boot.bin boot.asm
  nasm -o loader.bin loader.asm
  nasm -f elf kernel.asm -o kernel.o
  nasm -f elf klib.asm -o klib.o
  nasm -f elf string.asm -o string.o
  gcc -m32 -fno-stack-protector -fno-builtin -c start.c -o start.o
  ld -melf_i386 -s -Ttext 0x30400 kernel.o klib.o string.o start.o -o kernel.bin
  # generated a bootable floppy image
  dd if=/dev/zero of=TINIX.IMG bs=512 count=2880
  sudo mkfs.vfat TINIX.IMG
  dd conv=notrunc if=boot.bin of=TINIX.IMG bs=512 count=1
  mkdir -p tmp
  sudo mount -t vfat TINIX.IMG tmp
  sudo cp loader.bin kernel.bin tmp
  sudo umount tmp

  # use qemu to run
  qemu-system-i386 -fda TINIX.IMG -boot a -m 64M
```

* for h & i

```sh
make all
sudo mkdir -p /mnt/floppy
sudo make buildimg
sudo make run
```
