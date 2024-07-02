#include <stdio.h>

struct Process
{
    int id, arrival, burst, remaining, completion, waiting, turnaround;
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

void calculateTimes(struct Process proc[], int n, int order[], int *order_count)
{
    int completed = 0, time = 0, min_remaining, shortest;
    int is_completed[n];
    for (int i = 0; i < n; i++)
    {
        proc[i].remaining = proc[i].burst;
        is_completed[i] = 0;
    }

    while (completed != n)
    {
        min_remaining = 9999;
        shortest = -1;

        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrival <= time && is_completed[i] == 0 && proc[i].remaining < min_remaining)
            {
                min_remaining = proc[i].remaining;
                shortest = i;
            }
        }

        if (shortest == -1)
        {
            time++;
        }
        else
        {
            if (*order_count == 0 || order[*order_count - 1] != shortest)
            {
                order[*order_count] = shortest;
                (*order_count)++;
            }

            proc[shortest].remaining--;
            time++;

            if (proc[shortest].remaining == 0)
            {
                proc[shortest].completion = time;
                proc[shortest].turnaround = proc[shortest].completion - proc[shortest].arrival;
                proc[shortest].waiting = proc[shortest].turnaround - proc[shortest].burst;
                is_completed[shortest] = 1;
                completed++;
            }
        }
    }
}

void printResults(struct Process proc[], int n, int order[], int order_count)
{
    int totalWaiting = 0, totalTurnaround = 0;
    printf("\nProcess\t  Arrival Time\t  Burst Time\tCompletion Time\t  Waiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        int idx = order[i];
        totalWaiting += proc[idx].waiting;
        totalTurnaround += proc[idx].turnaround;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[idx].id, proc[idx].arrival, proc[idx].burst,
         proc[idx].completion, proc[idx].waiting, proc[idx].turnaround);
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
    int order[n]; // Array to store the order of process execution
    int order_count = 0;

    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", proc[i].id);
        scanf("%d %d", &proc[i].arrival, &proc[i].burst);
    }

    sortByArrival(proc, n);
    calculateTimes(proc, n, order, &order_count);
    printResults(proc, n, order, order_count);

    return 0;
}
