[bits 32]

MAGIC 			EQU   0x1BADB002
PAGE_ALIGN 		EQU   0x00000001
MEM_INFO 		EQU   0x00000002
GRAPHIC_MODE 	EQU   0x00000004
FLAGS			EQU   (PAGE_ALIGN | MEM_INFO | GRAPHIC_MODE)
CHECKSUM 		EQU  -(MAGIC + FLAGS)

GRAPHIC_MODE_WIDTH	 EQU  800
GRAPHIC_MODE_HEIGHT	 EQU  600
GRAPHIC_MODE_BPP	 EQU  32

section .multiboot
dd MAGIC
dd FLAGS
dd CHECKSUM

dd 0
dd 0
dd 0
dd 0
dd 0

dd 0
dd GRAPHIC_MODE_WIDTH
dd GRAPHIC_MODE_HEIGHT
dd GRAPHIC_MODE_BPP
   
section .text
extern _kernel
global _loader
global _double_framebuffer_buffer

_loader:
    mov esp,kernel_stack
    push ebx
    call _kernel
	cli
	
_stop:
    cli
    hlt
    jmp _stop

section .bss
	_double_framebuffer_buffer:
		align 4
		resb GRAPHIC_MODE_WIDTH*GRAPHIC_MODE_HEIGHT*(GRAPHIC_MODE_BPP/4)
	kernel_stack:
		resb 4*1024 ; 4 KiB

