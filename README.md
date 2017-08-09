# Tinix
Tinix on ubunut 14.04

sudo apt-get install nasm

# chapter1/a build cmdline
  cd chapter1/a
  nasm -o boot.bin boot.asm
  dd if=/dev/zero of=TINIX.IMG bs=512 count=2880
  sudo mkfs.vfat TINIX.IMG
  dd conv=notrunc if=boot.bin of=TINIX.IMG bs=512 count=1
  qemu-system-i386 -fda TINIX.IMG -boot a -m 64M

  // if want to debug
  qemu-system-i386 -fda TINIX.IMG -boot a -m 64M -s -S &
  echo "target remote:1234" > ~/.gdbinit
  echo "layout asm" >> ~/.gdbinit
  echo "b *0x7c00" >> ~/.gdbinit
  echo "c" >> ~/.gdbinit
  gdb
  // then input si to step asm code
