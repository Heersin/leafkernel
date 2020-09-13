#ifndef __SYSTEM_H
#define __SYSTEM_H

/* MAIN.C */
extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);


/* SCRN.C */
#define MAX_WIDTH 80
#define MAX_LINES 25
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define LIGHT_BROWN 14
#define WHITE 15
extern void cls();
extern void putch(unsigned char c);
extern void puts(unsigned char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();
// Mine Function
extern void setToLineHead();
extern void clrLine();

/* Based on scroll-- mydebug */
extern void print_log(unsigned char *log);
extern void print_info(unsigned char *info);
extern void print_success(unsigned char *info);
extern void print_debug(unsigned char *info);
extern void print_error(unsigned char *error);

// and a function for fun
extern void refreshLine(unsigned char *info);

/* GDT */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();


/* IDT */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* ISRs */
extern void isrs_install();
// Defines what the stack looks like after an ISR was running
struct regs
{
	unsigned int gs, fs, es, ds;	// push them at last
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; //pusha
	unsigned int int_no, err_code; // push byte
	unsigned int eip, cs, eflags, useresp, ss; // pushed by processor auto
};

/* PIC -- IRQs */
extern void irq_install();
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);

/* Timer */
extern void timer_install();
extern void timer_wait(int ticks);
#endif
