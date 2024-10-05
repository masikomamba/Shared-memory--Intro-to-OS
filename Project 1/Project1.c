#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SHM_KEY 12345 // Shared memory key

// Function that increments the shared variable "total"
void increment_total(int* total, int increment_value, int process_num) {
    for (int i = 0; i < increment_value; ++i) {
        (*total)++;
    }
    printf("From Process %d: counter = %d.\n", process_num, *total);
}

int main() {
    int shmid;
    int* total;
    pid_t pid;
    int increments[] = { 100000, 200000, 300000, 500000 };
    int i;

    // Create shared memory segment
    shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory segment to parent process
    total = (int*)shmat(shmid, NULL, 0);
    if (total == (int*)-1) {
        perror("shmat");
        exit(1);
    }

    // Initialize the shared variable
    *total = 0;

    // Fork processes
    for (i = 0; i < 4; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        else if (pid == 0) {
            // Child process
            increment_total(total, increments[i], i + 1);
            exit(0);  // Child process exits after finishing its task
        }
    }

    // Parent process waits for all children to finish
    for (i = 0; i < 4; i++) {
        pid_t child_pid = wait(NULL);
        printf("Child with ID: %d has just exited.\n", child_pid);
    }

    // Detach and remove shared memory
    if (shmdt(total) == -1) {
        perror("shmdt");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    printf("End of Program\n");

    return 0;
}
