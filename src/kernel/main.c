
#include <kernel/gdt.h>
#include <kernel/kstdio.h>
#include <string.h>
#include <kernel/gdt.h>

 
void main (void) 
{
    kcls();
    kputs("EarlzOS -- Hey, I'm a 64-bit operating system!\n");
    kputs("Installing GDT...");
    gdt_install();
    kputs("done\n");
    
    kputs("Nothing left to do :(");
    while(1); //spin until the heat death of the universe
}    