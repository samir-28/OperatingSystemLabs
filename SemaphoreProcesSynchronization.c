#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// Define union semun for semctl
union semun {
    int val;                  // Value for SETVAL
    struct semid_ds *buf;     // Buffer for IPC_STAT, IPC_SET
    unsigned short *array;    // Array for GETALL, SETALL
    struct seminfo *__buf;    // Buffer for IPC_INFO (Linux-specific)
};

// Semaphore initialization function
int init_semaphore(key_t key) {
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid < 0) {
        perror("semget");
        exit(1);
    }

    union semun semopts;
    semopts.val = 1;  // Initial semaphore value is 1
    if (semctl(semid, 0, SETVAL, semopts) < 0) {
        perror("semctl");
        exit(1);
    }

    return semid;
}

// Wait (P) operation
void semaphore_wait(int semid) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;  // Decrement the semaphore value by 1
    sb.sem_flg = 0;

    if (semop(semid, &sb, 1) < 0) {
        perror("semop wait");
        exit(1);
    }
}

// Signal (V) operation
void semaphore_signal(int semid) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = 1;  // Increment the semaphore value by 1
    sb.sem_flg = 0;

    if (semop(semid, &sb, 1) < 0) {
        perror("semop signal");
        exit(1);
    }
}

int main() {
    key_t key = ftok("semfile", 65);  // Generate a unique key for semaphore
    int semid = init_semaphore(key);

    pid_t pid;
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            semaphore_wait(semid);
            
            // Critical section
            printf("Process %d is in the critical section\n", getpid());
            sleep(1);
            printf("Process %d is leaving the critical section\n", getpid());
            
            semaphore_signal(semid);
            exit(0);
        }
    }

    // Wait for all child processes to complete
    for (int i = 0; i < 5; i++) {
        wait(NULL);
    }

    // Clean up semaphore
    if (semctl(semid, 0, IPC_RMID) < 0) {
        perror("semctl remove");
        exit(1);
    }

    return 0;
}
