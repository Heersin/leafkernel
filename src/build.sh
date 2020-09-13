#!/bin/bash
echo "[-]Following command will compling your kernel loader"
echo "[1]nasm -f aout -o start.o start.asm"
echo "[-]The original chose 'nasm -f aout ....' but I chose [1]"
nasm -f elf32 -o start.o start.asm

echo "[*] Remeber create a directory to store c header files"
echo "[*] The following space is reserved for gcc command"
gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I ./include -c -o main.o main.c
gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I ./include -c -o scrn.o scrn.c
gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I ./include -c -o gdt.o gdt.c
gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I ./include -c -o mydebug.o mydebug.c
gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I ./include -c -o idt.o idt.c
gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I ./include -c -o isrs.o isrs.c
gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I ./include -c -o irq.o irq.c
gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I ./include -c -o timer.o timer.c
echo "[*] reserved space done"


echo "[-]The Following will link kernel"
echo "[2] ld -T link.ld -o kernel.bin start.o -m elf_i386"
ld -m elf_i386 -T link.ld -o kernel.bin start.o main.o scrn.o gdt.o mydebug.o idt.o isrs.o irq.o timer.o
echo "[*] All Done"
