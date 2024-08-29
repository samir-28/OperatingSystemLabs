#include <stdio.h>
#include <stdlib.h>

void FCFS(int requests[], int n, int head)
{
    int total_head_movement = 0;

    // Display the initial head position
    printf("Initial Head Position: %d\n", head);
    printf("Disk Head Movement Sequence:\n");

    // Service each request in the order they appear
    for (int i = 0; i < n; i++)
    {
        // Display the movement from the current head to the next request
        printf("%d -> %d\n", head, requests[i]);

        // Calculate the head movement for the current request
        int movement = abs(requests[i] - head);
        total_head_movement += movement;

        // Move the head to the current request's position
        head = requests[i];
    }

    // Display the total head movement
    printf("Total Distance Covered in Tracks: %d\n", total_head_movement);
}

int main()
{
    //Self-initialized values for disk requests and head position
    int requests[] = {95, 180, 34, 119, 11, 123, 62, 64};
    int n = sizeof(requests) / sizeof(requests[0]);      // Number of disk requests
    int head = 50;                                       // Initial position of the disk head
                                   
    // Run FCFS Disk Scheduling Algorithm
    FCFS(requests, n, head);

    return 0;
}
