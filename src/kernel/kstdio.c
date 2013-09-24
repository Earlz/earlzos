
#include <string.h>
#include <kernel/kstdio.h>

volatile uint8_t *vram=(uint8_t *)0xB8000;
volatile uint8_t *vpage;
volatile uint8_t kd_color=0x0F;
volatile uint8_t backup_color;

volatile int console_x=0,console_y=0;


void k_put_cursor(int x,int y)
{
   // The screen is 80 characters wide...
   uint16_t cursorLocation = y * 80 + x;
   outportb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outportb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outportb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outportb(0x3D5, cursorLocation);      // Send the low cursor byte.
} 
void kcursor(){
        k_put_cursor(console_x,console_y);
}


void kputc_xy(char c,int x,int y){
        vram[(x+(y*80))*2]=c;
        vram[(x+(y*80))*2+1]=kd_color;
        k_put_cursor(x+1,y);
        
}

void kputs_xy(char *str,int x,int y){
        uint8_t i=0;
        while(str[i]!=0){
                kputc_xy(str[i],x+i,y);
                i++;
        }
}

void kputs(char *str){
        uint8_t i=0;
        while(str[i]!=0){
                
                if(console_y>=25){
                        kscroll();
                        console_y=24;
                        kcursor();
                }
                if(str[i]=='\n'){
                        console_x=0;
                        console_y++;
                }else{
                        kputc_xy(str[i],console_x,console_y);
                        console_x++;
                }
                if(console_y>=25){
                        kscroll();
                        console_y=24;
                        kcursor();
                }
                i++;
        }
        kcursor();
}

void kputc(char c){
        kputc_xy(c,console_x,console_y);
}


void kcls(){
        uint32_t i;
        for(i=0;i<=((80*25*2));i+=2){
                vram[i]=0;
                vram[i+1]=kd_color; //set color
        }
}

void kscroll(){
        
        memcpy((void*)vram,(const void*)vram+(80*2),80*2*24);
        uint32_t i;
        for(i=0;i<=((80*2));i+=2){
                vram[i+(80*24*2)]=0;
                vram[i+1+(80*24*2)]=kd_color; //set color
        }
        
}

//from http://www.jb.man.ac.uk/~slowe/cpp/itoa.html

/**
 * Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C"
 * with slight modification to optimize for specific architecture:
 */
//assumes that buffer is 32 bytes. returns pointer for use with kputs     
char* kitoa(uint64_t val, char* buf, int base){
    memset(buf, 0, 32);
    int i = 30;
    for(; val && i ; --i, val /= base)
            buf[i] = "0123456789abcdef"[val % base];
    
    return &buf[i+1];
}
        

void kput_hex(uint64_t dat){
    char tmp[32];
    kputs(kitoa(dat, tmp, 16));
}
