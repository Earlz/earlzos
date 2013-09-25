
#include <string.h>
#include <kernel/gdt.h>
#include <kernel/kstdio.h>


uint64_t gdt[GDT_LIMIT];
struct gdt_ptr gp;

uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
    uint64_t d;
 
    // Create the high 32 bit segment
    d  =  limit       & 0x000F0000;         // set limit bits 19:16
    d |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    d |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    d |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    d <<= 32;
 
    // Create the low 32 bit segment
    d |= base  << 16;                       // set base bits 15:0
    d |= limit  & 0x0000FFFF;               // set limit bits 15:0
    kputs("desc: ");
    kput_hex(d);
    kputs("\n");
    return d;
}

void gdt_install()
{
    gp.limit = (sizeof(int64_t) * GDT_LIMIT) - 1;
    gp.base =  (uintptr_t)&gdt;
    gdt[0]=create_descriptor(0, 0, 0);
    gdt[1]=create_descriptor(0, 0, (GDT_CODE_PL0)); //64bit ring0 code at 0x08
    gdt[2]=create_descriptor(0, 0, (GDT_DATA_PL0)); //64bit ring0 data at 0x10
    gdt_flush();
}