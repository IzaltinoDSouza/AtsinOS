#include <types.h>
#include <multiboot.h>

void memory_init(multiboot_info_t * mboot_ptr);
void * memory_allocate(u32 size);
void memory_deallocate(void * ptr);
