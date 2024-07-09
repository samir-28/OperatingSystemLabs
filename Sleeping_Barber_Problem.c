#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CHAIRS 5

sem_t customers; // Semaphore to count customers
sem_t barberChair; // Semaphore for barber chair
sem_t barberSleep; // Semaphore for barber sleeping
sem_t barberDone; // Semaphore for barber finishing

int num_waiting = 0; // Number of customers waiting
int next_customer = 0; // Index of next customer to serve

pthread_mutex_t mutex; // Mutex to protect shared variables

void* barber_function(void* arg) {
    while (1) {
        sem_wait(&customers); // Wait for a customer to arrive
        pthread_mutex_lock(&mutex);

        num_waiting--;
        sem_post(&barberChair); // Allow customer to sit in barber chair
        printf("Barber: Starting haircut for customer %d\n", next_customer);
        next_customer = (next_customer + 1) % NUM_CHAIRS;

        pthread_mutex_unlock(&mutex);
        sleep(2); // Simulate haircut duration

        printf("Barber: Finished haircut for customer\n");
        sem_post(&barberDone); // Signal haircut is finished
    }
    return NULL;
}

void* customer_function(void* arg) {
    int id = *(int*)arg;
    pthread_mutex_lock(&mutex);

    if (num_waiting < NUM_CHAIRS) {
        num_waiting++;
        printf("Customer %d: Arrived and waiting for haircut\n", id);
        sem_post(&customers); // Signal barber that customer has arrived
        pthread_mutex_unlock(&mutex);

        sem_wait(&barberChair); // Wait for barber chair to become available
        printf("Customer %d: Getting haircut\n", id);
        sem_wait(&barberDone); // Wait for haircut to finish

        printf("Customer %d: Finished haircut and leaving\n", id);
    } else {
        printf("Customer %d: No free chairs, leaving without haircut\n", id);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t barber, customers_threads[NUM_CHAIRS];
    int customer_ids[NUM_CHAIRS];

    sem_init(&customers, 0, 0);
    sem_init(&barberChair, 0, 0);
    sem_init(&barberSleep, 0, 1);
    sem_init(&barberDone, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&barber, NULL, barber_function, NULL);

    for (int i = 0; i < NUM_CHAIRS; i++) {
        customer_ids[i] = i;
        pthread_create(&customers_threads[i], NULL, customer_function, &customer_ids[i]);
        sleep(1); // Interval between customer arrivals
    }

    pthread_join(barber, NULL);
    for (int i = 0; i < NUM_CHAIRS; i++) {
        pthread_join(customers_threads[i], NULL);
    }

    sem_destroy(&customers);
    sem_destroy(&barberChair);
    sem_destroy(&barberSleep);
    sem_destroy(&barberDone);
    pthread_mutex_destroy(&mutex);

    return 0;
}
