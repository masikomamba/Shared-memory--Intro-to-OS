# Shared-memory--Intro-to-OS

##Shared memory

### overview

This program shows how shared memory is used to allow multiple processes to perform operations on a shared variable. The shared memory is created by the parent process, child processes are created using the fork function and they increment the shared variable. The parent process waits for all children to finish executing and then detaches from the shared memory and prints the results. 

###Requirements

* This program must be run on a Linux system
* Libraries: POSIX shared memory

## Compilation instructions

* Install C compiler if it is not already installed on your device
      - use the following command:
        sudo apt install gcc
* On the terminal, navaigate to the folder containing your code by using the **cd** commnad to move between directories
* Compile the program using gcc
      - gcc -o ExecutableFileName CodeFileName.c

## Execution Instructions

* Run the executable using the terminal using the following command:
    - ./ExecutableFileName
* The program should print process IDs and results.
  - example output:
    ![image](https://github.com/user-attachments/assets/3ace0909-f28c-480f-8455-42014c5064f2)

## Program explanation

### Shared memory creation:
* We begin by creating the shared memory using **shmget()** function and attach it using **shmat()**. Ths memory is reated by all child processes.

### Child process creation
* The parent creates the required number of child processes. The child processes are created using the **fork()** function. 
### Child Process execution
* Child process executes the remaining functions. The child processes increment using the array of incrementing values. Each child increments once with a specific value in the increment values array. After the process, each child will print its output as the total value after incrementing. 

### Parent process
* The parent waits for the children to finish executing before continuing using the **wait()** function. The parent process records the process IDs of the children while waiting and prints them once done.

### Shared memory cleanup
* Once all the processes have finished executing, the shared memory is detached and removed using the **shmdt()** function and **shmctl** function to clean up the resources used.
