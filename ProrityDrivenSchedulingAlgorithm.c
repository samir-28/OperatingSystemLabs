#include <stdio.h>

struct Process
{
    int id, arrival, burst, priority, completion, waiting, turnaround;
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

void sortByPriority(struct Process proc[], int start, int n)
{
    // Sorting processes by priority (higher number means higher priority)
    for (int i = start; i < n - 1; i++)
    {
        for (int j = start; j < n - 1; j++)
        {
            if (proc[j].priority < proc[j + 1].priority)
            {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(struct Process proc[], int n)
{
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        if (currentTime < proc[i].arrival)
        {
            currentTime = proc[i].arrival;
        }
        proc[i].completion = currentTime + proc[i].burst;
        proc[i].turnaround = proc[i].completion - proc[i].arrival;
        proc[i].waiting = proc[i].turnaround - proc[i].burst;
        currentTime = proc[i].completion;
    }
}

void printResults(struct Process proc[], int n)
{
    int totalWaiting = 0, totalTurnaround = 0;
    printf("\nProcess\t  Arrival Time\t  Burst Time\t  Priority\tCompletion Time\t  Waiting Time\t  Turnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        totalWaiting += proc[i].waiting;
        totalTurnaround += proc[i].turnaround;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival, proc[i].burst, 
         proc[i].priority, proc[i].completion, proc[i].waiting, proc[i].turnaround);
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
    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority (higher number indicates higher priority) for process %d: ", proc[i].id);
        scanf("%d %d %d", &proc[i].arrival, &proc[i].burst, &proc[i].priority);
    }

    sortByArrival(proc, n); // Sort processes by arrival time initially

    // Move process with arrival time 0 to the front
    if (proc[0].arrival == 0)
    {
        sortByPriority(proc, 1, n); // Sort remaining processes by priority
    }
    else
    {
        sortByPriority(proc, 0, n); // Sort all processes by priority if none arrive at time 0
    }

    calculateTimes(proc, n); // Calculate completion, waiting, and turnaround times
    printResults(proc, n); // Print scheduling results

    return 0;
}
