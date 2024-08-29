#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void SSTF(int requests[], int n, int head)
{
    int total_head_movement = 0;
    bool serviced[n];  // Array to keep track of serviced requests

    // Initialize the serviced array to false
    for (int i = 0; i < n; i++)
        serviced[i] = false;

    // Display the initial head position
    printf("Initial Head Position: %d\n", head);
    printf("Disk Head Movement Sequence:\n");

    // Service all requests using SSTF
    for (int i = 0; i < n; i++)
    {
        int shortest_seek_time = 1000000;  // Large initial value
        int next_request_index = -1;

        // Find the closest request to the current head position
        for (int j = 0; j < n; j++)
        {
            if (!serviced[j])
            {
                int seek_time = abs(requests[j] - head);
                if (seek_time < shortest_seek_time)
                {
                    shortest_seek_time = seek_time;
                    next_request_index = j;
                }
            }
        }

        // Service the closest request
        printf("%d -> %d\n", head, requests[next_request_index]);
        total_head_movement += shortest_seek_time;
        head = requests[next_request_index];
        serviced[next_request_index] = true;
    }

    // Display the total head movement
    printf("Total Distance Covered in Tracks: %d\n", total_head_movement);
}

int main()
{
    // Self-initialized values for disk requests and head position
   int requests[] = {95, 180, 34, 119, 11, 123, 62, 64}; // Disk request queue
   int n = sizeof(requests) / sizeof(requests[0]);       // Number of disk requests
   int head = 50;                                        // Initial position of the disk head
     
    // Run SSTF Disk Scheduling Algorithm
    SSTF(requests, n, head);

    return 0;
}
