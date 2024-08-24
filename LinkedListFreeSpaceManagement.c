#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 1024

// Linked list node representing a free block
typedef struct FreeBlock {
    int start;                // Starting block number
    int size;                 // Number of contiguous free blocks
    struct FreeBlock* next;
} FreeBlock;

// Function to create a new free block
FreeBlock* create_free_block(int start, int size) {
    FreeBlock* block = (FreeBlock*)malloc(sizeof(FreeBlock));
    block->start = start;
    block->size = size;
    block->next = NULL;
    return block;
}

// Function to allocate a block
int allocate_block(FreeBlock** free_list) {
    FreeBlock* current = *free_list;
    if (!current) {
        return -1;  // No free blocks available
    }

    int start_block = current->start;

    // Update the free list by removing one block
    if (current->size == 1) {
        *free_list = current->next;
        free(current);
    } else {
        current->start++;
        current->size--;
    }

    return start_block;
}

// Function to free a block
void free_block(FreeBlock** free_list, int block) {
    FreeBlock* new_block = create_free_block(block, 1);
    new_block->next = *free_list;
    *free_list = new_block;
}

int main() {
    // Initialize the free list with a large free block
    FreeBlock* free_list = create_free_block(0, BLOCK_SIZE);

    // Allocate some blocks
    int block1 = allocate_block(&free_list);
    int block2 = allocate_block(&free_list);
    printf("Allocated block %d\n", block1);
    printf("Allocated block %d\n", block2);

    // Free a block
    free_block(&free_list, block1);
    printf("Freed block %d\n", block1);

    return 0;
}
