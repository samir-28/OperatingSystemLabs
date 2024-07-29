#include <stdio.h>

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    // Initialize all allocations to -1 (indicating no allocation yet)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Loop through each process to find the worst block that fits
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[worstIdx] < blockSize[j]) {
                    worstIdx = j;
                }
            }
        }

        // If we found a block for the process
        if (worstIdx != -1) {
            allocation[i] = worstIdx; // Allocate block to process
            blockSize[worstIdx] -= processSize[i]; // Reduce available memory in this block
        }
    }

    // Print the results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Need to wait\n");
    }
}

int main() {
    int m, n;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter the sizes of the memory blocks in order: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter the sizes of the processes in order: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    worstFit(blockSize, m, processSize, n);

    return 0;
}
