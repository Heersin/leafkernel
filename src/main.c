#include "system.h"
#define NULL (void *)0
/* You will need to code these up yourself!  */
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
    /* Add code here to copy 'count' bytes of data from 'src' to
 *     *  'dest', finally return 'dest' */
	const unsigned char *src_ptr;
	unsigned char *dst_ptr;
	src_ptr = src;
	dst_ptr = dest;

	int i;
	for(i = 0; i < count; ++i)
		dst_ptr[i] = src_ptr[i];
	return dst_ptr;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
    /* Add code here to set 'count' bytes in 'dest' to 'val'.
 *     *  Again, return 'dest' */
	int i;
	for(i = 0; i < count; ++i)
		dest[i] = val;
	return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    /* Same as above, but this time, we're working with a 16-bit
 *     *  'val' and dest pointer. Your code can be an exact copy of
 *         *  the above, provided that your local variables if any, are
 *             *  unsigned short */
	unsigned short *dst_ptr;
	int i;
	dst_ptr = dest;
	for(i = 0; i < count; ++i)
		dst_ptr[i] = val;
	return dst_ptr;
}

int strlen(const char *str)
{
    /* This loops through character array 'str', returning how
 *     *  many characters it needs to check before it finds a 0.
 *         *  In simple words, it returns the length in bytes of a string */
	int len;
	char *string;
	string = str;
	len = 0;
	while(*string != '\0')
	{
		++string;
		++len;
	}
	return len;
}

/* We will use this later on for reading from the I/O ports to get data
 * *  from devices such as the keyboard. We are using what is called
 * *  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
 * *  will be used in the next tutorial for changing the textmode cursor
 * *  position. Again, we use some inline assembly for the stuff that simply
 * *  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

/* This is a very simple main() function. All it does is sit in an
 * *  infinite loop. This will be like our 'idle' loop */
int main()
{
    /* You would add commands after here */
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	__asm__ __volatile__("sti");
	timer_install();
	init_video();

	puts("A little Kernel, Hello world !\n");
	print_log("It's v0.5, with GDT installed and Some Output Function, --2019/10/17");
	print_success("Happy Day");
	print_info("Information Like this");
	print_error("Error Like This");
	print_debug("Used for debug");
	print_log("It's v0.6, IDT and ISRs installed, tested by 'putch(5/0)'--2019/10/19");
	print_log("It's v0.7, IRQ with Timer set up -- 2019/11/03");
	// putch(5/0);


    /* ...and leave this loop in. There is an endless loop in
 *     *  'start.asm' also, if you accidentally delete this next line */
    	for (;;);
	return 0;
}
