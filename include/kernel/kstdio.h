#ifndef KSTDIO_H
#define KSTDIO_H


int kputs(char* s);
int kputc(char c);

int kputs_xy(char* s, int x, int y);

#include <kernel/x86.h>
#define PANIC(x) kd_set_color(0xCF); \
        kd_puts_xy(">>KERNEL PANIC>>""x",0,24); \
        stopints(); \
        hlt(); 

#endif