#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define MAX_EAT_TIMES 3

sem_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t mutex;

void *philosopher(void *num)
{
    int id = *(int *)num;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    int eat_count = 0;

    while (eat_count < MAX_EAT_TIMES)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1); // Thinking

        // Pick up forks
        pthread_mutex_lock(&mutex);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        pthread_mutex_unlock(&mutex);

        // Eating
        printf("Philosopher %d is eating\n", id);
        eat_count++;
        sleep(1);

        // Put down forks
        sem_post(&forks[left]);
        sem_post(&forks[right]);
    }

    printf("Philosopher %d has finished eating %d times and leaves the table.\n", 
    id, eat_count);
    return NULL;
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}
