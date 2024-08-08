#include <stdio.h>
#include <stdbool.h>

int n, m; // n = number of processes, m = number of resource types
int available[10], max[10][10], allocation[10][10], need[10][10];

void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe() {
    int work[10], finish[10] = {0};
    int safeSequence[10], index = 0;

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == m) { // If all resources for this process can be allocated
                    for (int y = 0; y < m; y++) {
                        work[y] += allocation[i][y];
                    }
                    safeSequence[index++] = i;
                    finish[i] = 1;
                }
            }
        }
    }

    // Check if all processes are finished
    for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
            printf("The system is in an unsafe state!\n");
            return false;
        }
    }

    // If the system is safe
    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    printf("Enter the available resources: \n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resource matrix (Max): \n");
    for (int i = 0; i < n; i++) {
        printf("For process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation resource matrix (Allocation): \n");
    for (int i = 0; i < n; i++) {
        printf("For process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    calculateNeed();
    isSafe();

    return 0;
}
