#include <stdio.h>

struct Process
{
    int id, arrival, burst, completion, waiting, turnaround;
    float responseRatio;
};

void sortByArrival(struct Process proc[], int n)
{
    // Sorting processes by arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (proc[j].arrival > proc[j + 1].arrival)
            {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void calculateResponseRatio(struct Process proc[], int n, int currentTime)
{
    for (int i = 0; i < n; i++)
    {
        if (proc[i].arrival <= currentTime && proc[i].completion == 0) // Process has arrived and not completed
        {
            proc[i].waiting = currentTime - proc[i].arrival;
            proc[i].responseRatio = (float)(proc[i].waiting + proc[i].burst) / proc[i].burst;
        }
        else
        {
            proc[i].responseRatio = -1; // Not eligible for selection
        }
    }
}

int selectProcess(struct Process proc[], int n)
{
    int selectedIndex = -1;
    float highestResponseRatio = -1.0;
    for (int i = 0; i < n; i++)
    {
        if (proc[i].responseRatio > highestResponseRatio)
        {
            highestResponseRatio = proc[i].responseRatio;
            selectedIndex = i;
        }
    }
    return selectedIndex;
}

void calculateTimes(struct Process proc[], int n, int readyQueue[])
{
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        calculateResponseRatio(proc, n, currentTime);
        int selectedIndex = selectProcess(proc, n);
        if (selectedIndex != -1)
        {
            readyQueue[i] = proc[selectedIndex].id;
            currentTime += proc[selectedIndex].burst;
            proc[selectedIndex].completion = currentTime;
            proc[selectedIndex].turnaround = proc[selectedIndex].completion - proc[selectedIndex].arrival;
            proc[selectedIndex].waiting = proc[selectedIndex].turnaround - proc[selectedIndex].burst;
        }
    }
}

void printReadyQueue(int readyQueue[], int n)
{
    printf("Ready Queue Order: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", readyQueue[i]);
    }
    printf("\n");
}

void printResults(struct Process proc[], int n)
{
    int totalWaiting = 0, totalTurnaround = 0;
    printf("\nProcess\t  Arrival Time\t  Burst Time\tCompletion Time\t  Waiting Time\t  Turnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        totalWaiting += proc[i].waiting;
        totalTurnaround += proc[i].turnaround;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival, proc[i].burst,
         proc[i].completion, proc[i].waiting, proc[i].turnaround);
    }
    printf("\nAverage waiting time = %.2f", (float)totalWaiting / n);
    printf("\nAverage turnaround time = %.2f\n", (float)totalTurnaround / n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    int readyQueue[n]; // Array to keep track of the ready queue order
    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", proc[i].id);
        scanf("%d %d", &proc[i].arrival, &proc[i].burst);
        proc[i].completion = 0; // Initially not completed
        proc[i].waiting = 0; // Initially no waiting time
        proc[i].turnaround = 0; // Initially no turnaround time
        proc[i].responseRatio = 0; // Initially no response ratio
    }

    sortByArrival(proc, n); // Sort processes by arrival time initially

    calculateTimes(proc, n, readyQueue); // Calculate completion, waiting, and turnaround times using HRRN
    printResults(proc, n); // Print scheduling results
    printReadyQueue(readyQueue, n); // Print the final ready queue order

    return 0;
}
