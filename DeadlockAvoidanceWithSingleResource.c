#include <stdio.h>
#include <stdbool.h>

int n; // Number of processes
int totalResource; // Total instances of the resource
int available; // Available instances of the resource
int max[10]; // Maximum demand of each process
int allocation[10]; // Currently allocated resource instances for each process
int need[10]; // Remaining need of each process

void calculateNeed() {
    for (int i = 0; i < n; i++) {
        need[i] = max[i] - allocation[i];
    }
}

bool isSafe() {
    int work = available;
    bool finish[10] = {0};
    int safeSequence[10];
    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i] && need[i] <= work) {
                work += allocation[i];
                safeSequence[count++] = i;
                finish[i] = true;
                found = true;
            }
        }

        if (!found) {
            printf("The system is in an unsafe state!\n");
            return false;
        }
    }

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

    printf("Enter the total number of resource instances: ");
    scanf("%d", &totalResource);

    printf("Enter the maximum demand for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        scanf("%d", &max[i]);
    }

    printf("Enter the currently allocated resources for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        scanf("%d", &allocation[i]);
    }

    available = totalResource;
    for (int i = 0; i < n; i++) {
        available -= allocation[i];
    }

    calculateNeed();

    if (isSafe()) {
        printf("The system is safe and can proceed with the safe sequence.\n");
    } else {
        printf("The system is not safe.\n");
    }

    return 0;
}
