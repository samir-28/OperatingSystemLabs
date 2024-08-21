#include <stdio.h>

int main() {
    int capacity, n, page_faults = 0, page_hits = 0;
    
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);  // Number of frames available (capacity of memory)

    printf("Enter the number of page requests: ");
    scanf("%d", &n);  // Number of pages (sequence length)

    int frames[capacity];   // Frames to hold the pages
    int pages[n];           // Array for page requests
    int time[n];            // To track the time each page was used (used for LRU)
    int current_time = 0;   // Keeps track of the time to implement LRU
    int filled = 0;         // Number of pages in frames currently filled

    // Initialize all frames and times to -1 (indicating they are empty)
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
        int lru_index = 0;  // To store the index of the Least Recently Used page

        // Display the current page request
        printf("Page %2d: ", page);

        // Check if the page is already in one of the frames (page hit)
        for (int j = 0; j < filled; j++) {
            if (frames[j] == page) {
                found = 1;
                time[j] = current_time;  // Update the time for the page (most recently used)
                break;
            }
        }

        // If page is found, it's a hit
        if (found) {
            page_hits++;
        } else {
            // If page is not found, it's a fault
            if (filled < capacity) {
                // If there is still space in the frames
                frames[filled] = page;
                time[filled] = current_time;
                filled++;
            } else {
                // Find the Least Recently Used (LRU) page
                int lru_time = time[0];
                lru_index = 0;
                for (int j = 1; j < capacity; j++) {
                    if (time[j] < lru_time) {
                        lru_time = time[j];
                        lru_index = j;
                    }
                }
                // Replace the LRU page
                frames[lru_index] = page;
                time[lru_index] = current_time;
            }
            page_faults++;
        }

        // Increment the time counter
        current_time++;

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
