#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    // Initialize all allocations to -1 (indicating no allocation yet)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Loop through each process and find the first block that fits
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j; // Allocate block j to process i
                blockSize[j] -= processSize[i]; // Reduce available memory in this block
                break;
            }
        }
    }

    // Print the results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t  %d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("  %d\n", allocation[i] + 1);
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

    firstFit(blockSize, m, processSize, n);

    return 0;
}
