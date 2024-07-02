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

void calculateTimes(struct Process proc[], int n, int order[], int *order_count, int quantum)
{
    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0; // Circular queue to hold process indices
    int isInQueue[n];
    for (int i = 0; i < n; i++)
    {
        proc[i].remaining = proc[i].burst;
        isInQueue[i] = 0;
    }

    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrival <= time && proc[i].remaining > 0 && isInQueue[i] == 0)
            {
                queue[rear % 100] = i;
                rear++;
                isInQueue[i] = 1;
            }
        }

        if (front == rear)
        {
            time++;
            continue;
        }

        int idx = queue[front % 100];
        front++;

        if (proc[idx].remaining > 0)
        {
            if (proc[idx].remaining <= quantum)
            {
                time += proc[idx].remaining;
                proc[idx].remaining = 0;
                proc[idx].completion = time;
                proc[idx].turnaround = proc[idx].completion - proc[idx].arrival;
                proc[idx].waiting = proc[idx].turnaround - proc[idx].burst;
                completed++;
            }
            else
            {
                time += quantum;
                proc[idx].remaining -= quantum;
            }

            order[*order_count] = idx;
            (*order_count)++;

            for (int i = 0; i < n; i++)
            {
                if (proc[i].arrival <= time && proc[i].remaining > 0 && isInQueue[i] == 0)
                {
                    queue[rear % 100] = i;
                    rear++;
                    isInQueue[i] = 1;
                }
            }

            if (proc[idx].remaining > 0)
            {
                queue[rear % 100] = idx;
                rear++;
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
        totalWaiting += proc[i].waiting;
        totalTurnaround += proc[i].turnaround;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival, proc[i].burst,
         
          proc[i].completion, proc[i].waiting, proc[i].turnaround);
    }

    printf("\nAverage waiting time = %.2f", (float)totalWaiting / n);
    printf("\nAverage turnaround time = %.2f\n", (float)totalTurnaround / n);

    printf("\nReady Queue Order: ");
    for (int i = 0; i < order_count; i++)
    {
        printf("%d ", proc[order[i]].id);
    }
    printf("\n");
}

int main()
{
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    struct Process proc[n];
    int order[100];  // Assuming a maximum of 100 order entries for simplicity
    int order_count = 0;

    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", proc[i].id);
        scanf("%d %d", &proc[i].arrival, &proc[i].burst);
    }

    sortByArrival(proc, n);
    calculateTimes(proc, n, order, &order_count, quantum);
    printResults(proc, n, order, order_count);

    return 0;
}
