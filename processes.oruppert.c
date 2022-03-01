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

void handler1(int signum) {
    printf("this is handler1(): got a signal %d\n", signum);
    done = 1;
}


int main() {
    int pid;
    struct sigaction action;

    done = 0;
    pid = getpid();

    printf("Starting; my pid is %d\n", pid);

    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = handler1;
    sigaction(SIGUSR1, &action, NULL);

    printf("now wait for something to happen\n");
    while ( ! done );

    printf("done!\n");
    return 0;
}

