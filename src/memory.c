#include <types.h>
#include <multiboot.h>

typedef struct MemoryChunk
{
	void * start;
	u32 size;
	bool allocated;
	struct MemoryChunk * next;
}__attribute__((packed)) MemoryChunk;

#define CHUNKS_SIZE 4096

MemoryChunk * memory_chunk_begin;

void memory_init(multiboot_info_t * mboot_ptr)
{
	bool create = true;
	MemoryChunk * memory_chunk = memory_chunk_begin;

	for(multiboot_memory_map_t * mmap = (multiboot_memory_map_t *) mboot_ptr->mmap_addr;
		 (u64) mmap < mboot_ptr->mmap_addr + mboot_ptr->mmap_length;
		 mmap = (multiboot_memory_map_t *) ((u64) mmap + mmap->size + sizeof (mmap->size)))
    {
    	if(mmap->type != MULTIBOOT_MEMORY_AVAILABLE)
            continue;
          
         u32 * start = mmap->addr;
         u32 * end = start + mmap->len;
         
         //?
         if(mmap->addr == 0) continue;
         
         if(create)
         {         	
         	memory_chunk = (MemoryChunk*)start;
         	memory_chunk->start = start + sizeof(MemoryChunk);
         	memory_chunk->size = CHUNKS_SIZE;
			memory_chunk->allocated = false;
         	
         	create = false;
         	start += CHUNKS_SIZE;
        }
        while(start != end)
        {
			memory_chunk->next = (MemoryChunk*)start;
         	memory_chunk->next->start = (void*)(start + sizeof(MemoryChunk));
         	memory_chunk->next->allocated = false;
         	memory_chunk->next->next = NULL;
         	
         	if((start+CHUNKS_SIZE) < end)
         		memory_chunk->next->size = CHUNKS_SIZE;
         	else
         		memory_chunk->next->size = (end - start) / CHUNKS_SIZE;

			memory_chunk = memory_chunk->next;
			start += CHUNKS_SIZE;
         }
    }
}
void * memory_allocate(u32 size)
{
	if(size == 0) return NULL;
	
	MemoryChunk * memory_chunks = memory_chunk_begin;
	while(memory_chunks != NULL)
	{
		if(!memory_chunks->allocated && memory_chunks->size < size)
		{
			memory_chunks->allocated = true;
			return memory_chunks->start;
		}
		memory_chunks = memory_chunks->next;
	}
}
void memory_deallocate(void * ptr)
{
	if(ptr == NULL) return;
	
	MemoryChunk * memory_chunks = memory_chunk_begin;
	while(memory_chunks != NULL)
	{		
		if(memory_chunks->start == ptr)
		{
			memory_chunks->allocated = false;
		}
		memory_chunks = memory_chunks->next;
	}
}
