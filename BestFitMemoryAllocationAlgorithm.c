#include <stdio.h>

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    // Initialize all allocations to -1 (indicating no allocation yet)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Loop through each process to find the best block that fits
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j]) {
                    bestIdx = j;
                }
            }
        }

        // If we found a block for the process
        if (bestIdx != -1) {
            allocation[i] = bestIdx; // Allocate block to process
            blockSize[bestIdx] -= processSize[i]; // Reduce available memory in this block
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

    bestFit(blockSize, m, processSize, n);

    return 0;
}
 