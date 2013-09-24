/*
<Copyright Header>
Copyright (c) 2007 - 2013 Jordan "Earlz/hckr83" Earls  <http://www.earlz.net>
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

This file is part of the AlloyOS project
</Copyright Header>
*/

/**x86 inline assembly functions. Note that not all of these may work. -- mixed Ring 3 and Ring 0**/


#ifndef X86_H
#define X86_H

#include <stdint.h>

static inline uint8_t inportb(uint16_t port) {
        uint8_t ret;

        asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
        return ret;
}
static inline void outportb(uint16_t port,uint8_t value) {
        asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
}


static inline uint32_t inportd(uint16_t port) {
        uint32_t ret;

        asm volatile ("in %%dx,%%eax":"=a" (ret):"d" (port));
        return ret;
}
static inline void outportd(uint16_t port,uint32_t value) {
        asm volatile ("out %%eax,%%dx": :"d" (port), "a" (value));
}

/* Stop Interrupts */
static inline void stopints() {
        asm ("cli");
}
static inline void startints() {
        asm("sti");
}

extern uint32_t _x86_tmpi; //these are because symbols are not recorded for the stack
extern uint16_t _x86_tmps;
extern uint8_t _x86_tmpc;
extern void *_x86_tmpp;




//control regs
static inline unsigned int GetCR0(){
        __asm(".intel_syntax noprefix\n"
                        "push eax\n"
                        "mov eax,cr0\n"
                        "mov [_x86_tmpi],eax\n"
                        "pop eax\n"
                        ".att_syntax\n");
        return _x86_tmpi;
}
static inline unsigned int GetCR1(){
        __asm(".intel_syntax noprefix\n"
                        "push eax\n"
                        "mov eax,cr1\n"
                        "mov [_x86_tmpi],eax\n"
                        "pop eax\n"
                        ".att_syntax\n");
        return _x86_tmpi;
}
static inline unsigned int GetCR2(){
        __asm(".intel_syntax noprefix\n"
                        "push eax\n"
                        "mov eax,cr2\n"
                        "mov [_x86_tmpi],eax\n"
                        "pop eax\n"
                        ".att_syntax\n");
        return _x86_tmpi;
}
static inline unsigned int GetCR3(){
        __asm(".intel_syntax noprefix\n"
                        "push eax\n"
                        "mov eax,cr3\n"
                        "mov [_x86_tmpi],eax\n"
                        "pop eax\n"
                        ".att_syntax\n");
        return _x86_tmpi;
}
static inline unsigned int GetCR4(){
        __asm(".intel_syntax noprefix\n"
                        "push eax\n"
                        "mov eax,cr4\n"
                        "mov [_x86_tmpi],eax\n"
                        "pop eax\n"
                        ".att_syntax\n");
        return _x86_tmpi;
}

static inline void SetCR0(unsigned int val){
        _x86_tmpi=val;
        __asm(".intel_syntax noprefix\n"
                        "push eax\n"
                        "mov eax,[_x86_tmpi]\n"
                        "mov cr0,eax\n"
                        "pop eax\n"
                        ".att_syntax\n");
}

static inline void SetCR1(unsigned int val){
        _x86_tmpi=val;
        __asm(".intel_syntax noprefix\n"
                        "push eax\n"
                        "mov eax,[_x86_tmpi]\n"
                        "mov cr1,eax\n"
                        "pop eax\n"
                        ".att_syntax\n");
}
static inline void SetCR2(unsigned int val){
        _x86_tmpi=val;
        __asm(".intel_syntax noprefix\n"
                        "push eax\n"
                        "mov eax,[_x86_tmpi]\n"
                        "mov cr2,eax\n"
                        "pop eax\n"
                        ".att_syntax\n");
}
static inline void SetCR3(unsigned int val){
        _x86_tmpi=val;
        __asm(".intel_syntax noprefix\n"
                        "push eax\n"
                        "mov eax,[_x86_tmpi]\n"
                        "mov cr3,eax\n"
                        "pop eax\n"
                        ".att_syntax\n");
}
static inline void SetCR4(unsigned int val){
        _x86_tmpi=val;
        __asm(".intel_syntax noprefix\n"
                        "push eax\n"
                        "mov eax,[_x86_tmpi]\n"
                        "mov cr4,eax\n"
                        "pop eax\n"
                        ".att_syntax\n");
}


//Lxxx commands such as lgdt

static inline void LGDT(void *ptr){
        _x86_tmpp=ptr;
        __asm(".intel_syntax noprefix\n"
                        "lgdt [_x86_tmpp]\n"
                        ".att_syntax\n");
}

static inline void LLDT(void *ptr){
        _x86_tmpp=ptr;
        __asm(".intel_syntax noprefix\n"
                        "lldt [_x86_tmpp]\n"
                        ".att_syntax\n");
}
static inline void LTR(unsigned short selector){
        _x86_tmps=selector;
        __asm(".intel_syntax noprefix\n"
                        "mov dx,_x86_tmps\n"
                        "ltr [_x86_tmps]\n"
                        ".att_syntax\n");
}
static inline void LIDT(void *ptr){
        _x86_tmpp=ptr;
        __asm(".intel_syntax noprefix\n"
                        "lidt [[_x86_tmpp]]\n"
                        ".att_syntax\n");
}


static inline unsigned int GetEFLAGS(){
        __asm(".intel_syntax noprefix\n"
                        "pushfd\n"
                        "pop [_x86_tmpi]\n"
                        ".att_syntax\n");
        return _x86_tmpi;
}




//ect commands
static inline void hlt(){
        asm volatile("hlt");
}








#endif
