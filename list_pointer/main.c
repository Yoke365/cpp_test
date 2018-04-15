#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>

/**
 * INTERNAL DEFINITION, DO NOT USE DIRECTLY.
 * A memory block used in the memory block allocator.
 */
typedef union CanardPoolAllocatorBlock_u
{
    char bytes[32];
    //union CanardPoolAllocatorBlock_u* next;
} CanardPoolAllocatorBlock;

/**
 * This structure provides usage statistics of the memory pool allocator.
 * This data helps to evaluate whether the allocated memory is sufficient for the application.
 */
typedef struct
{
    uint16_t capacity_blocks;               ///< Pool capacity in number of blocks
    uint16_t current_usage_blocks;          ///< Number of blocks that are currently allocated by the library
    uint16_t peak_usage_blocks;             ///< Maximum number of blocks used since initialization
} CanardPoolAllocatorStatistics;

/**
 * INTERNAL DEFINITION, DO NOT USE DIRECTLY.
 */
typedef struct
{
    CanardPoolAllocatorBlock* free_list;
    //CanardPoolAllocatorStatistics statistics;
} CanardPoolAllocator;

uint8_t buf1[512];
CanardPoolAllocatorBlock* p_mem[20];

void initPoolAllocator(CanardPoolAllocator* allocator,
                                       CanardPoolAllocatorBlock* buf,
                                       uint16_t buf_len)
{
   	size_t current_index = 0;
   	while(current_index < buf_len) {
   		p_mem[current_index] = &buf1[current_index];
   		printf("i: %d, *current_block: 0x%x,\r\n", current_index, p_mem[current_index]);


   		current_index++;
   	}

    // size_t current_index = 0;
    // CanardPoolAllocatorBlock** current_block = &(allocator->free_list);
    // while (current_index < buf_len)
    // {   
    	
    //     *current_block = &buf[current_index];
    //     printf("i: %d, *current_block: 0x%x,\r\n", current_index, *current_block );
    //     current_block = &((*current_block)->next);

    //     printf("0x%x, 0x%x,0x%x, 0x%x\r\n", buf1[32*current_index+0], 
    //     	buf1[32*current_index+1], 
    //     	buf1[32*current_index+2], 
    //     	buf1[32*current_index+3]);
    //     current_index++;
    // }
    // *current_block = NULL;

    // allocator->statistics.capacity_blocks = buf_len;
    // allocator->statistics.current_usage_blocks = 0;
    // allocator->statistics.peak_usage_blocks = 0;
}

CanardPoolAllocator allocator;                  ///< Pool allocator




// CANARD_INTERNAL void* allocateBlock(CanardPoolAllocator* allocator)
// {
//     // // Check if there are any blocks available in the free list.
//     // if (allocator->free_list == NULL)
//     // {
//     //     return NULL;
//     // }

//     // // Take first available block and prepares next block for use.
//     // void* result = allocator->free_list;
//     // allocator->free_list = allocator->free_list->next;

//     // // Update statistics
//     // allocator->statistics.current_usage_blocks++;
//     // if (allocator->statistics.peak_usage_blocks < allocator->statistics.current_usage_blocks)
//     // {
//     //     allocator->statistics.peak_usage_blocks = allocator->statistics.current_usage_blocks;
//     // }

//     return result;
// }

// CANARD_INTERNAL void freeBlock(CanardPoolAllocator* allocator, void* p)
// {
//     // CanardPoolAllocatorBlock* block = (CanardPoolAllocatorBlock*) p;

//     // block->next = allocator->free_list;
//     // allocator->free_list = block;

//     // CANARD_ASSERT(allocator->statistics.current_usage_blocks > 0);
//     // allocator->statistics.current_usage_blocks--;
// }

void uavcan_test()
{
	printf("addr: 0x%x\r\n", buf1);

	initPoolAllocator(&allocator, buf1, 512/32);

}

int main (int argc, char **argv)
{	
	//printf("argc: %d\r\n", argc);
	uavcan_test();

	// for (uint8_t i = 0 ; i < argc; i++) {
	// 	printf("%s\r\n", argv[i]);
	// }

	// char buf[10];
	// for (uint8_t i = 0; i < 10; i++) {
	// 	buf[i] = i;
	// 	printf("%d\n", buf[i]); 
	// }

	// char *p1 = &buf[0];
	// char *p2 = &buf[1];
	// char *p3 = &buf[2];
	// char *p4 = &buf[3];

	// char *p_array[4];
	// // p_array[0] = &p1;
	// // p_array[1] = &p2;
	// // p_array[2] = &p3;
	// // p_array[3] = &p4;
    
 //    char **ptr = &p2;

 //    printf("%d\n", **ptr); 

	// // int a=12,*p,**ptr;  
 // //    ptr=&p;  
 // //    p=&a;  
 // //    **ptr=34;  
    //printf("%d %d %d\n",a,*p,**ptr); 

	return 0;
}