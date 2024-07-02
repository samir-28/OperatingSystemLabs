#include <stdio.h>

struct Process
{
    int id, arrival, burst, completion, waiting, turnaround;
};

void sortByArrival(struct Process proc[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (proc[j].arrival > proc[j + 1].arrival)
            {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
}

void calculateTimes(struct Process proc[], int n)
{
    proc[0].completion = proc[0].arrival + proc[0].burst;
    for (int i = 1; i < n; i++)
    {
        proc[i].completion = proc[i].arrival > proc[i - 1].completion ? proc[i].arrival + proc[i].burst : proc[i - 1].completion + proc[i].burst;
    }

    for (int i = 0; i < n; i++)
    {
        proc[i].turnaround = proc[i].completion - proc[i].arrival;
        proc[i].waiting = proc[i].turnaround - proc[i].burst;
    }
}

void printResults(struct Process proc[], int n) 
{
    int totalWaiting = 0, totalTurnaround = 0;
    printf("\nProcess\t  Arrival Time\t  Burst Time\tCompletion Time\t  Waiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        totalWaiting += proc[i].waiting;
        totalTurnaround += proc[i].turnaround;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival, proc[i].burst, proc[i].completion, proc[i].waiting, proc[i].turnaround);
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
        printf("Enter arrival time and burst time for process %d: ", proc[i].id);
        scanf("%d %d", &proc[i].arrival, &proc[i].burst);
    }

    sortByArrival(proc, n);
    calculateTimes(proc, n);
    printResults(proc, n);

    return 0;
}
