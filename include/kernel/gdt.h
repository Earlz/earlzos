/*
<Copyright Header>
Copyright (c) 2007 - 2013 Jordan "Earlz/hckr83" Earls  <http://earlz.net>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.
   
THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

</Copyright Header>
*/

/**Contains all the kernel GDT functions**/

#ifndef GDT_H
#define GDT_H
#include <stdint.h>

struct gdt_entry
{
        unsigned short limit_low;
        unsigned short base_low;
        unsigned char base_middle;
        unsigned char access;
        unsigned char granularity; //has limit in tss
        unsigned char base_high;
} __attribute__((packed));



struct gdt_entry_bits
{
        unsigned int limit_low:16;
        unsigned int base_low : 24;
     //attribute byte split into bitfields
        unsigned int accessed :1;
        unsigned int read_write :1; //readable for code, writable for data
        unsigned int conforming_expand_down :1; //conforming for code, expand down for data
        unsigned int code :1; //1 for code, 0 for data
        unsigned int always_1 :1; //should be 1 for everything but TSS and LDT
        unsigned int DPL :2; //priveledge level
        unsigned int present :1;
     //and now into granularity
        unsigned int limit_high :4;
        unsigned int available :1;
        unsigned int longmode :1; //64bit segment
        unsigned int big :1; //32bit opcodes for code, dword stack for data
        unsigned int gran :1; //1 to use 4k page addressing, 0 for byte addressing
        unsigned int base_high :8;
} __attribute__((packed));

/**
g->limit_low=limit&0xFFFF; //isolate bottom 16 bits
g->base_low=base&0xFFFFFF; //isolate bottom 24 bits
g->accessed=1; //This indicates it's a TSS and not a LDT. This is a changed meaning
g->read_write=0; //This indicates if the TSS is busy or not. 0 for not busy
g->conforming_expand_down=0; //always 0 for TSS
g->code=1; //For TSS this is 1 for 32bit usage, or 0 for 16bit.
g->always_1=0; //indicate it is a TSS
g->DPL=3; //same meaning
g->present=1; //same meaning
g->limit_high=(limit&0xF0000)>>16; //isolate top nibble
g->available=0;
g->always_0=0; //same thing
g->big=0; //should leave zero according to manuals. No effect
g->gran=0; //so that our computed GDT limit is in bytes, not pages
g->base_high=(base&0xFF000000)>>24; //isolate top byte.
**/


// A struct describing a Task State Segment.
struct tss_entry_struct
{
   uint32_t prev_tss;   // The previous TSS - if we used hardware task switching this would form a linked list.
   uint32_t esp0;       // The stack pointer to load when we change to kernel mode.
   uint32_t ss0;        // The stack segment to load when we change to kernel mode.
   uint32_t esp1;       // Unused...
   uint32_t ss1;
   uint32_t esp2;
   uint32_t ss2;
   uint32_t cr3;
   uint32_t eip;
   uint32_t eflags;
   uint32_t eax;
   uint32_t ecx;
   uint32_t edx;
   uint32_t ebx;
   uint32_t esp;
   uint32_t ebp;
   uint32_t esi;
   uint32_t edi;
   uint32_t es;         // The value to load into ES when we change to kernel mode.
   uint32_t cs;         // The value to load into CS when we change to kernel mode.
   uint32_t ss;         // The value to load into SS when we change to kernel mode.
   uint32_t ds;         // The value to load into DS when we change to kernel mode.
   uint32_t fs;         // The value to load into FS when we change to kernel mode.
   uint32_t gs;         // The value to load into GS when we change to kernel mode.
   uint32_t ldt;        // Unused...
   uint16_t trap;
   uint16_t iomap_base;
} __attribute__((packed));

typedef struct tss_entry_struct tss_entry_t;
extern tss_entry_t tss_entry;


/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr {
        unsigned short limit;
        unsigned int base;
} __attribute__((packed));

/* Our GDT, with 3 entries, and finally our special GDT pointer */

#define GDT_LIMIT 10


extern struct gdt_entry gdt[GDT_LIMIT];
extern struct gdt_ptr gp;
extern void gdt_flush(); //asm function

void GdtInstall();
uint16_t GdtSetGate(uint32_t num,uint32_t base,uint32_t limit,uint8_t access,uint8_t gran);
void write_tss(uint32_t num, uint16_t ss0, uint32_t esp0);
void tss_flush();
void set_kernel_stack(uint32_t stack);

#endif

