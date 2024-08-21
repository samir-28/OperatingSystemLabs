#include <stdio.h>

int main() {
    int capacity, n, page_faults = 0, page_hits = 0, front = 0;
    
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);  // Number of frames available (capacity of memory)

    printf("Enter the number of page requests: ");
    scanf("%d", &n);  // Number of pages (sequence length)

    int frames[capacity];   // Frames to hold the pages
    int pages[n];           // Array for page requests
    int filled = 0;         // Number of pages in frames currently filled

    // Initialize all frames to -1 (indicating they are empty)
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    // Input the page sequence
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Iterate over each page in the reference string
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;  // Flag to check if page is already in frame

        // Check if the page is already in one of the frames (page hit)
        for (int j = 0; j < filled; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // Display the current page request
        printf("Page %2d: ", page);

        // If page is found, it's a hit
        if (found) {
            page_hits++;
        } else {
            // If page is not found, it's a fault
            if (filled < capacity) {
                // If there is still space in the frames
                frames[filled++] = page;
            } else {
                // Replace the oldest page (FIFO)
                frames[front] = page;
                front = (front + 1) % capacity;  // Move to next position in FIFO
            }
            page_faults++;
        }

        // Display the current state of the frames with uniform spacing
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1)
                printf("  -  ");
            else
                printf("%3d  ", frames[j]);
        }

        // Indicate hit or fault
        if (found) {
            printf("[ H ]\n");
        } else {
            printf("[ F ]\n");
        }
    }

    // Output the total number of page faults and hits
    printf("\nTotal Page Faults: %d\n", page_faults);
    printf("Total Page Hits: %d\n", page_hits);

    return 0;
}
