#ifndef KSTDIO_H
#define KSTDIO_H
#include <stdint.h>

void kputs(char* s);
void kputc(char c);

void kputs_xy(char* s, int x, int y);
void kput_hex(uint64_t num);
void kscroll();
void kcls();

#include <kernel/x86.h>
#define PANIC(x) kd_set_color(0xCF); \
        kd_puts_xy(">>KERNEL PANIC>>""x",0,24); \
        stopints(); \
        hlt(); 

#endif