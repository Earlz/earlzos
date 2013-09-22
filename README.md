# EarlzOS

EarlzOS -- A toy operating system designed to run only in virtual x86-64 environments. Tested only on Virtual Box

# Dependencies

List of dependencies

* [Gujin](http://wiki.osdev.org/Gujin) -- bootloader (capable of ELF64 from FAT32!) 
* nasm -- The primary assembler I use (yasm appears to have bugs with ELF64)
* 64bit and 32bit freestanding GCC compilers
* BSD make (specifically NetBSD.. may eventually change to GNU)
* Assumes a unix-y environement


Got started from here: http://wiki.osdev.org/64-bit_Higher_Half_Kernel_with_GRUB_2
