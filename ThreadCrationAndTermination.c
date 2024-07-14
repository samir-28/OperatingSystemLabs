 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Function that will be run by the child thread
void* child_thread_function(void* arg) {
    printf("This is the child thread. Thread ID: %lu\n", pthread_self());
    usleep(300000);  // Wait for 0.3 seconds
    printf("Child thread exiting. Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t child_thread;

    // Create the child thread
    if (pthread_create(&child_thread, NULL, child_thread_function, NULL) != 0) {
        perror("ERROR: Failed to create child thread");
        return 1;
    }

    // This is the parent thread
    printf("This is the parent thread. Thread ID: %lu\n", pthread_self());

    // Wait for the child thread to finish
    if (pthread_join(child_thread, NULL) != 0) {
        perror("ERROR: Failed to join child thread");
        return 1;
    }

    printf("Parent thread exiting. Thread ID: %lu\n", pthread_self());
    return 0;
}

