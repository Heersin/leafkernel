# leafkernel
A demo kernel to learn some concepts 

## Usage
### Build From source
First, clone this git:
```sh
git clone https://github.com/Heersin/leafkernel.git
```

build from source code to get kernel.bin
```sh
chmod +x build.sh
./build.sh
rm -f *.o
```

Using a ISO editor or something else to build your **.flp**/**.img** file
and load it with vbox

### Download the release file
[release links](https://github.com/Heersin/leafkernel/tree/master/releases)

## Screenshot
(with keyboard file installed)
![screenshot](https://github.com/Heersin/leafkernel/blob/master/samples/kernel_keyboard.png)

## Project Tree
```
./src
├─build.sh    --- script to compile these C files
├─gdt.c       --- GDT table
├─idt.c       --- IDT
├─include/    --- Headers
│ └─system.h
├─irq.c       --- IRQ
├─isrs.c      --- ISR
├─main.c      --- Main file
├─mydebug.c   --- Some Utils for debug
├─scrn.c      --- screen helper
├─start.asm   --- start from this asm
├─link.ld     --- ld script to set some args to load kernel
└─timer.c     --- A kernel timer

```

## Reference
[1][Bran's kernel](http://www.osdever.net/bkerndev/Docs/intro.htm) Thanks to [Brandon F.](friesenb@gmail.com) for giving me some suggestions.
[2][My Blog](http://ironfool.com/2020/07/27/leafkernel-part1/)
