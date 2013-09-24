




void kput_hex(uint32_t dat){
        char *hex_digits="0123456789ABCDEF";
     unsigned int i=7; //7
     unsigned char tmp[2]={'\0',0};
     //waitkey();
     while(((dat&(0xF<<(i*4)))>>(i*4))==0){
         if(i==0){break;}
         i--;
     }
     for(i=i;i>0;i--){
          tmp[0]=hex_digits[(dat&(0xF<<(i*4)))>>(i*4)];
         // waitkey();
          kputs(tmp);
          //wait(2000);
          if(i==0){break;}
     }
     tmp[0]=hex_digits[(dat&(0xF))];
     kputs(tmp);
}
