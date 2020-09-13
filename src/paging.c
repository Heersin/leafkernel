#include <system.h>

// 4096 aligned, depend on your hardware
unsigned long *page_dir;
unsigned long *cur_page_table;

extern unsigned long read_cr0();
extern void write_cr0(unsigned long );
extern unsigned long read_cr3();
extern void write_cr3(unsigned long );


void paging_install()
{
    page_dir = (unsigned long *) 0x40000;
    cur_page_table = (unsigned long *) 0x41000;

    unsigned long phy_addr;
    unsigned int i;

    // Init page dir, the low 3 bit always 0, so we can use them as flag bit.
    // Supervisor level, rw, present (0b011)
    page_dir[0] = cur_page_table;
    page_dir[0] = page_dir[0] | 3;

    // Init other page, not present (0b010)
    for (i = 1; i < 1024; ++i)
        page_dir[i] = 0 | 2;

    // start physicall address
    // we can map virtual address to other phy addr by changing this
    phy_addr = 0;

    // map the first 4MB of mem
    for (i = 0; i < 1024; ++i)
    {
        // first table set present 
        // 0x3 = 0b011 -- supervisor / RW / Present
        // 4kb = 4096
        cur_page_table[i] = phy_addr | 3;
        phy_addr = phy_addr + 4096;
    }


    // set up paging
    // remeber the CR0 and CR3 mechnism!!!
    // paging bit is the 1st bit of cr0
    write_cr3((unsigned long)page_dir);
    write_cr0(read_cr0() | 0x80000000);

}