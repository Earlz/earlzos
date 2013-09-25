#<Copyright Header>
#Copyright (c) 2007 - 2013 Jordan "Earlz/hckr83" Earls  <http://earlz.net>
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions
#are met:
#
#1. Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
#2. Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
#3. The name of the author may not be used to endorse or promote products
#   derived from this software without specific prior written permission.
#   
#THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
#INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
#AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
#THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
#ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#</Copyright Header>


ASM=yasm
ASMFLAGS=-felf64

CFLAGS= -m64 \
	-mcmodel=kernel \
	-mno-red-zone \
	-nostdlib \
	-nostartfiles \
	-nodefaultlibs \
	-I ./include \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-sse3 \
	-mno-3dnow \
	-ffreestanding \
	-I ./compiled-newlib/x86_64-elf/include \
	-Wall



LDFLAGS:= -nostartfiles -nodefaultlibs -nostdlib -nodefaultlibs \
	-z max-page-size=0x1000 -s -static 


HDRS=

C_SRCS=src/kernel/main.c src/kernel/kstdio.c src/kernel/gdt.c
 
C_OBJS=$(C_SRCS:src/%.c=objs/%.o)

ASM_SRCS=src/kernel/assemblyglue.asm src/kernel/boot.asm
ASM_OBJS=$(ASM_SRCS:src/%.asm=objs/%.o)

OUTFILE=bin/kernel.elf

DONEKERNEL=bin/earlzos.kgz

BINDIR:=bin

#BOOTDEV=/dev/sdd

default: ${DONEKERNEL}

rebuild: clean install-boot install

install-boot:
	gujin ${BOOTDEV}

install: ${DONEKERNEL}
	rm -rf mnt
	mkdir mnt
	mount ${BOOTDEV} ./mnt
	cp ${DONEKERNEL} ./mnt/
	sync
	umount ${BOOTDEV}

#user_:
#	cd user/ && make

#We always remake the ramdisk because it's nearly impossible to know if
#the file it links with are out of date or not
#ramdisk: user_
#	${ASM} ${ASMFLAGS} src/tfs.asm -o objs/tfs.o

${ASM_OBJS}: ${*:objs/%=src/%}.asm
	${ASM} ${ASMFLAGS} ${*:objs/%=src/%}.asm -o $*.o

${C_OBJS}: ${HDRS} ${*:objs/%=src/%}.c
	${CC} ${CFLAGS} -c ${*:objs/%=src/%}.c -o $*.o

${OUTFILE}: ${ASM_OBJS} ${C_OBJS} src/linker.ld
	${CC} ${LDFLAGS} -T src/linker.ld -o ${OUTFILE} ${ASM_OBJS} $(C_OBJS) ./compiled-newlib/x86_64-elf/lib/libc.a ./compiled-newlib/x86_64-elf/lib/libnosys.a

${DONEKERNEL}: ${OUTFILE}
	gzip -9 ${OUTFILE} -c > ${DONEKERNEL}

clean:
	rm -f ${C_OBJS} ${ASM_OBJS} ${OUTFILE} ${DONEKERNEL}

force-clean: clean
	rm -f *.o */*.o */*/*.o */*/*/*.o */*/*/*/*.o */*/*/*/*/*.o */*/*/*/*/*/*.o



