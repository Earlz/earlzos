
#include <kernel/gdt.h>
#include <kernel/kstdio.h>

 const char msg1[] = "Hello long-mode text world! please reboot ..."; 
 
 void main (void) 
 { 
        /* We are flat non-paged memory and interrupt disabled */ 
        volatile unsigned short *video_array = (volatile unsigned short *)0xB8000; 
        unsigned cpt1; 
  memcpy(0, 0, 0);
        video_array += 10 * 80; /* few empty lines */ 
        /* We want blue background color and lightgray foreground, so 0x1700: */ 
        if(sizeof(int*)==8)
        {
          for (cpt1 = 0; cpt1 < sizeof(msg1) - 1; cpt1++) 
                  video_array[cpt1] = 0x1700 + msg1[cpt1]; 
        }
        while (1) 
                continue; 
  while(1);
}