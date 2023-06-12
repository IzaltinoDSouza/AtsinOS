.set MAGIC,    0x1BADB002
.set PAGE_ALIGN,   0x00000001
.set MEM_INFO,     0x00000002
.set GRAPHIC_MODE, 0x00000004
.set FLAGS,	       (PAGE_ALIGN | MEM_INFO | GRAPHIC_MODE)
.set CHECKSUM,    -(MAGIC + FLAGS)
.section .multiboot

# define type to long for each data defined as above
.long MAGIC
.long FLAGS
.long CHECKSUM

.long 0
.long 0
.long 0
.long 0
.long 0

.long 0         # mode_type
.long 800       # width
.long 600		# height
.long 32		# bpp
   
.section .text
.extern _kernel
.global _loader
.global _double_framebuffer_buffer

_loader:
    mov $kernel_stack, %esp
    push %ebx
    call _kernel
	cli
	
_stop:
    cli
    hlt
    jmp _stop

.section .bss
_double_framebuffer_buffer:
	.align 4
	.skip 800*600*4
.space 4*1024 # 4 KiB
kernel_stack:

