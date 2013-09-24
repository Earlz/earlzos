
#include <kernel/gdt.h>
#include <kernel/kstdio.h>
#include <string.h>

 
void main (void) 
{
    kcls();
    kputs("EarlzOS -- Hey, I'm a 64-bit operating system!\n");
    kputs("meh... I'm done\n");
    kputs("Test number: ");
    kput_hex(0x123456789ABCDEF);
    
    while(1); //spin until the heat death of the universe
}    