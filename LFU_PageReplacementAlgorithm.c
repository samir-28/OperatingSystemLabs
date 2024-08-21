#include <stdio.h>

struct Page {
    int value;     // Page value
    int frequency; // Frequency of usage
    int last_used; // Last used time for LFU tie-breaking
};

int main() {
    int capacity, n, page_faults = 0, page_hits = 0, time = 0;
    
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);  // Number of frames available (capacity of memory)

    printf("Enter the number of page requests: ");
    scanf("%d", &n);  // Number of pages (sequence length)

    struct Page frames[capacity];   // Frames to hold the pages and their frequency
    int pages[n];                   // Array for page requests

    // Initialize frames (set page value to -1 and frequency to 0)
    for (int i = 0; i < capacity; i++) {
        frames[i].value = -1;
        frames[i].frequency = 0;
        frames[i].last_used = 0;
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
        time++;         // Update the time for LFU tie-breaking

        // Check if the page is already in one of the frames (page hit)
        for (int j = 0; j < capacity; j++) {
            if (frames[j].value == page) {
                found = 1;
                frames[j].frequency++;   // Increment frequency on hit
                frames[j].last_used = time;
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
            page_faults++;

            // Find the frame to replace using LFU logic
            int min_freq = frames[0].frequency, replace_idx = 0;
            for (int j = 1; j < capacity; j++) {
                // Replace the least frequently used page or in case of tie, the least recently used page
                if (frames[j].frequency < min_freq ||
                   (frames[j].frequency == min_freq && frames[j].last_used < frames[replace_idx].last_used)) {
                    min_freq = frames[j].frequency;
                    replace_idx = j;
                }
            }

            // Replace the page in the chosen frame
            frames[replace_idx].value = page;
            frames[replace_idx].frequency = 1;  // Initialize frequency to 1
            frames[replace_idx].last_used = time;  // Update the last used time
        }

        // Display the current state of the frames with uniform spacing
        for (int j = 0; j < capacity; j++) {
            if (frames[j].value == -1)
                printf("  -  ");
            else
                printf("%3d  ", frames[j].value);
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
