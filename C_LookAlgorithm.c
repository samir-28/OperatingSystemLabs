#include <stdio.h>
#include <stdlib.h>

void C_LOOK_Top_Bottom(int requests[], int n, int head)
{
    int total_head_movement = 0;
    int sorted_requests[n]; // Array to store sorted requests
    int i, j;

    // Copy the requests
    for (i = 0; i < n; i++)
        sorted_requests[i] = requests[i];

    // Sort the request array
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (sorted_requests[i] > sorted_requests[j])
            {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }
        }
    }

    // Display the initial head position
    printf("Initial Head Position: %d\n", head);
    printf("Disk Head Movement Sequence (Top-Bottom C-LOOK Approach):\n");

    // Find the position of the head in the sorted array
    int start_index = 0;
    for (i = 0; i < n; i++)
    {
        if (sorted_requests[i] >= head)
        {
            start_index = i;
            break;
        }
    }

    // Move Upwards (Top-Down)
    for (i = start_index; i < n; i++)
    {
        printf("%d -> %d\n", head, sorted_requests[i]);
        total_head_movement += abs(sorted_requests[i] - head);
        head = sorted_requests[i];
    }

    // Jump directly to the lowest unserviced request
    if (start_index > 0)
    {
        printf("%d -> %d (Jump)\n", head, sorted_requests[0]);
        total_head_movement += abs(head - sorted_requests[0]);
        head = sorted_requests[0];

        // Move Upwards again from the lowest request
        for (i = 0; i < start_index; i++)
        {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }
    }

    // Display the total head movement
    printf("Total Distance Covered in Tracks (Top-Bottom C-LOOK): %d\n", total_head_movement);
}

void C_LOOK_Bottom_Top(int requests[], int n, int head)
{
    int total_head_movement = 0;
    int sorted_requests[n]; // Array to store sorted requests
    int i, j;

    // Copy the requests
    for (i = 0; i < n; i++)
        sorted_requests[i] = requests[i];

    // Sort the request array
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (sorted_requests[i] > sorted_requests[j])
            {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }
        }
    }

    // Display the initial head position
    printf("\nInitial Head Position: %d\n", head);
    printf("Disk Head Movement Sequence (Bottom-Top C-LOOK Approach):\n");

    // Find the position of the head in the sorted array
    int start_index = 0;
    for (i = 0; i < n; i++)
    {
        if (sorted_requests[i] >= head)
        {
            start_index = i;
            break;
        }
    }

    // Move Downwards (Bottom-Up)
    for (i = start_index - 1; i >= 0; i--)
    {
        printf("%d -> %d\n", head, sorted_requests[i]);
        total_head_movement += abs(sorted_requests[i] - head);
        head = sorted_requests[i];
    }

    // Jump directly to the highest unserviced request
    if (start_index < n)
    {
        printf("%d -> %d (Jump)\n", head, sorted_requests[n - 1]);
        total_head_movement += abs(head - sorted_requests[n - 1]);
        head = sorted_requests[n - 1];

        // Move Downwards again from the highest request
        for (i = n - 2; i >= start_index; i--)
        {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }
    }

    // Display the total head movement
    printf("Total Distance Covered in Tracks (Bottom-Top C-LOOK): %d\n", total_head_movement);
}

int main()
{
    // Self-initialized values for disk requests and head position
    int requests[] = {95, 180, 34, 119, 11, 123, 62, 64}; // Disk request queue
    int n = sizeof(requests) / sizeof(requests[0]);       // Number of disk requests
    int head = 50;

    // Run C-LOOK Disk Scheduling Algorithm (Top-Bottom approach)
    C_LOOK_Top_Bottom(requests, n, head);

    // Run C-LOOK Disk Scheduling Algorithm (Bottom-Top approach)
    C_LOOK_Bottom_Top(requests, n, head);

    return 0;
}
