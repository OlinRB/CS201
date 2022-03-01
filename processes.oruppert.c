//
// Created by olinr on 2/27/2022.
//


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <signal.h>

#define BUFFER_SIZE 32

//• the parent creates a shared memory segment
//• the parent forks a child process
//• the child process attaches to the shared memory
//• the parent process writes a word to shared memory
//• the child process reads the word and prints it out
//• the parent process writes a word to shared memory
//• the child process reads the word and prints it out
//• etc.

int done;
int parentWait, childWait;

void handler1(int signum) {
    printf("Handler called....\n");
    if (signum == SIGUSR1) {
        printf("From SIGUSR1: got a signal %d\n", signum);
//        parentWait = 0;
//        childWait = 1;
// Make explicit to fork
    }
    else {
        printf("From SIGUSR2: got signal %d\n", signum);
        parentWait = 1;
        childWait = 0;

    }

    done = 1;
}


int main() {
    int pid;
    struct sigaction action;
    // Vars for shared mem
    int memid;
    int key = IPC_PRIVATE;
    char *ptr;
    char buffer[BUFFER_SIZE];
    done = 0;

    // Create shared mem
    memid = shmget(key, BUFFER_SIZE, IPC_EXCL | 0666);
    if (memid < 0) {
        printf("shmget() failed\n");
        return(8);
    }
    // Create fork
    pid = fork();
    // put in code for parent and child
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = handler1;
    if (pid < 0) {
        printf("fork failed\n");
        return(8);
    }
    strcpy(buffer, "done");
    if (pid > 0) {
        // this is the parent
        printf("I am the parent, and my pid is %d\n", getpid());
        sigaction(SIGUSR1, &action, NULL);
        ptr = (char *) shmat(memid, 0, 0);
        if (ptr == NULL) {
            printf("shmat() failed\n");
            return (8);
        }
        wait(NULL);

    } else {
        ptr = (char *) shmat(memid, 0, 0);
        printf("I am the child, and my pid is %d\n", getpid());
        sigaction(SIGUSR2, &action, NULL);
        shmdt(ptr);
    }

    // While loop for actions
    for (int i = 0; i < 3; ++i) {
        if (pid > 0) {
            // Parent actions
            printf("Parent is writing '%s' to the shared memory\n", buffer);
            strcpy(ptr, buffer);
            signal(SIGUSR1, &handler1);
            wait(NULL);
        } else {
            ptr = (char *) shmat(memid, 0, 0);
            if (ptr == NULL) {
                printf("shmat() in child failed\n");
                return (8);
            }
            printf("I am the child, and I read this from the shared memory: '%s'\n", ptr);

            shmdt(ptr);
            signal(SIGUSR2, &handler1);
            kill(getpid(), SIGUSR1);
        }
    }

    return 0;
}

