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
int loop;

void handler1(int signum) {
    printf("this is handler1(): got a signal %d\n", signum);
    done = 1;
    loop = 1;
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
    loop = 0;

    // Create shared mem
    memid = shmget(key, BUFFER_SIZE, IPC_EXCL | 0666);
    if (memid < 0) {
        printf("shmget() failed\n");
        return(8);
    }

    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = handler1;
    sigaction(SIGUSR1, &action, NULL);


    // Create fork
    pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
        return(8);
    }
    strcpy(buffer, "Hello world");
    if (pid > 0) {
        // this is the parent
        printf("I am the parent, and my pid is %d\n", getpid());

        ptr = (char *) shmat(memid, 0, 0);
        if (ptr == NULL) {
            printf("shmat() failed\n");
            return (8);
        }

        printf("Parent is writing '%s' to the shared memory\n", buffer);
        strcpy(ptr, buffer);
        wait(NULL);

    } else {
        ptr = (char *) shmat(memid, 0, 0);
        printf("I am the child, and my pid is %d\n", getpid());

        printf("I am the child, and I read this from the shared memory: '%s'\n", ptr);

        shmdt(ptr);
        // Kill process
    }


    return 0;
}

