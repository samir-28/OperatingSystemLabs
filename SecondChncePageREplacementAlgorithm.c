#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Function to find an element in the queue
// Returns the index if found, -1 otherwise
int findPage(int *q, int size, int x) {
    for (int i = 0; i < size; i++) {
        if (q[i] == x)
            return i;
    }
    return -1;
}

// Function to implement the Second Chance Page Replacement Algorithm
void Second_Chance_Replacement(int *t, int n, int capacity) {
    int *q = (int *)malloc(capacity * sizeof(int));  // Queue implementation using array
    bool *bitref = (bool *)malloc(capacity * sizeof(bool));  // Reference bits
    int qSize = 0;  // Current size of queue

    // Variables to track hits and faults
    int hits = 0, faults = 0;

    int ptr = 0;  // Pointer to track the position in the queue

    // Initialize the reference bits array
    for (int i = 0; i < capacity; i++) {
        bitref[i] = false;
    }

    for (int i = 0; i < n; i++) {
        int pageIndex = findPage(q, qSize, t[i]);

        // If the page is already in memory (hit)
        if (pageIndex != -1) {
            hits++;
            bitref[pageIndex] = true;  // Set reference bit to 1 (second chance)
        } 
        // If it's a fault (page not found in memory)
        else {
            faults++;

            // If there's still room in the queue
            if (qSize < capacity) {
                q[qSize] = t[i];  // Insert page into memory
                bitref[qSize] = false;  // Initially set reference bit to 0
                qSize++;
            } 
            // If the queue is full, apply the Second Chance algorithm
            else {
                while (true) {
                    // Check the reference bit of the page at the current pointer position
                    if (bitref[ptr] == false) {
                        // If reference bit is 0, replace the page
                        q[ptr] = t[i];
                        break;
                    } else {
                        // If reference bit is 1, reset it and move to the next page
                        bitref[ptr] = false;
                        ptr = (ptr + 1) % capacity;  // Circular increment
                    }
                }

                // Move pointer to the next position after replacement
                ptr = (ptr + 1) % capacity;
            }
        }
    }

    printf("Hits: %d\nFaults: %d\n", hits, faults);

    // Free dynamically allocated memory
    free(q);
    free(bitref);
}

// Driver code
int main() {
    int t[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3 , 2, 3};
    int n = sizeof(t) / sizeof(t[0]);
    int capacity = 3;
    Second_Chance_Replacement(t, n, capacity);

    return 0;
}
