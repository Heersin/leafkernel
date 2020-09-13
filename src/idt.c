#include <system.h>

/* define IDT entry */
/* ---------FLAGS---------
 * 7 --6---5----------0
 *   P  DPL   Always 01110(14)
 *
 */
struct idt_entry
{
	unsigned short base_lo;
	unsigned short sel;		// kernel segment goes here
	unsigned char always0;
	unsigned char flags;		// set using the 
	unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. Although we will only use the
 * *  first 32 entries in this tutorial, the rest exists as a bit
 * *  of a trap. If any undefined IDT entry is hit, it normally
 * *  will cause an "Unhandled Interrupt" exception. Any descriptor
 * *  for which the 'presence' bit is cleared (0) will generate an
 * *  "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* An Extern func */
extern void idt_load();


void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,unsigned char flags)
{
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].sel = sel;
	idt[num].always0 = 0x0;
	idt[num].flags = flags;
	idt[num].base_hi = ((base>>16) & 0xFFFF);
} 

/* Install the IDT */
void idt_install()
{
	/* Sets up the special IDT pointer */
	idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
	idtp.base = &idt;


	/* CLear out the entire IDT, init to 0 */
	memset(&idt,0, sizeof(struct idt_entry) * 256);

	/* ----------- ISRs Issue ---------------*/
	
	/* ----------- ISRs Done ----------------*/
	
	/* Points the proc's internal reg to the new IDT*/
	idt_load();
}
