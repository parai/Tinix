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
  # then in the pop up window input pmtest.com
  C:\> cls
  C:\> A:\pmtest.com
```
