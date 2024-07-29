#include <stdio.h>

void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int lastAllocatedBlock = 0;

    // Initialize all allocations to -1 (indicating no allocation yet)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Loop through each process to find the next block that fits
    for (int i = 0; i < n; i++) {
        int startIdx = lastAllocatedBlock;
        int allocated = 0;

        for (int j = startIdx; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i]; // Reduce available memory in this block
                lastAllocatedBlock = (j + 1) % m;
                allocated = 1;
                break;
            }
        }

        // If not allocated, search from the beginning again
        if (!allocated) {
            for (int j = 0; j < startIdx; j++) {
                if (blockSize[j] >= processSize[i]) {
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    lastAllocatedBlock = (j + 1) % m;
                    break;
                }
            }
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

    nextFit(blockSize, m, processSize, n);

    return 0;
}
 