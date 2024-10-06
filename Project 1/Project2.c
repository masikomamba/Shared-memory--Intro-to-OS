#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SHM_KEY 0x1234 // Shared memory key


int main() {
    int shmid;
    int* total = 0;


    // Create shared memory segment
    shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0777);
    if (shmid == -1) {
        perror("shared memory");
        return 1;
    }

    // Attach shared memory segment to parent process
    total = (int*)shmat(shmid, NULL, 0);
    if (total == (int*)-1) {
        perror("Shared memory attach");
        return 1;
    }

    // Fork processes
    

   /*pid_t pid =  fork();
   
   if (pid == 0){
   fork();
   //fork();
        for(int i = 0; i < 4; i++){
                int increments[] = { 100000, 200000, 300000, 500000 };
                int increment_value = increments[i];
                int process_number = i;
                for (int i = 0; i < increment_value; ++i) {
                    (*total)++;
                    }
                i++;
                printf("From Process %d: counter = %d.\n", process_number+1, *total);
                // Child process exits after finishing its task
                    
        }
   return 1;
   }*/
 //fork processes
  for (int i = 0; i < 4; i++) {
        pid_t pid = fork(); // create four child processes
        if (pid == 0) { // let child process execute the following code
            int increments[] = { 100000, 200000, 300000, 500000 };
            int increment_value = increments[i];
            int process_number = i;
            for (int i = 0; i < increment_value; ++i) {
                (*total)++;
                }
            i++;
            printf("From Process %d: counter = %d.\n", process_number +1, *total);
            return 1;  // Child process exits after finishing its task
        }
    }

    // Detach and remove shared memory
    if (shmdt(total) == -1) {
        perror("shmdt");
        return 1;
    }
 //remove shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        return 1;
    }

    pid_t childProcess_pid = 0;
  // Parent process waits for all children to finish
     for (int i = 0; i < 4; i++) {
        childProcess_pid = wait(NULL);
    }
    
    printf("\n");
 //parent process prints everytime a child process finishes execution
    for(int i = 0; i<4; i++){
        printf("Child with ID: %d has just exited.\n", childProcess_pid+i);
    }

    printf("\n");
    printf("End of Simulation\n");

    return 0;
}
