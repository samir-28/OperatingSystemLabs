#include <stdio.h>
#include <stdbool.h>

#define BLOCKS 16  // Number of blocks

// Initialize bitmap with all blocks free (0)
unsigned char bitmap[BLOCKS / 8] = {0};

// Function to set the bit at index in the bitmap
void set_bit(int index) {
    bitmap[index / 8] |= (1 << (index % 8));
}

// Function to clear the bit at index in the bitmap
void clear_bit(int index) {
    bitmap[index / 8] &= ~(1 << (index % 8));
}

// Function to check if the bit at index is set
bool is_bit_set(int index) {
    return bitmap[index / 8] & (1 << (index % 8));
}

// Function to allocate a block
int allocate_block() {
    for (int i = 0; i < BLOCKS; i++) {
        if (!is_bit_set(i)) {
            set_bit(i);
            return i;  // Return the index of the allocated block
        }
    }
    return -1;  // No free blocks available
}

// Function to free a block
void free_block(int index) {
    if (index >= 0 && index < BLOCKS) {
        clear_bit(index);
    }
}

int main() {
    // Allocate some blocks
    int block1 = allocate_block();
    int block2 = allocate_block();
    printf("Allocated block %d\n", block1);
    printf("Allocated block %d\n", block2);

    // Free a block
    free_block(block1);
    printf("Freed block %d\n", block1);

    return 0;
}
