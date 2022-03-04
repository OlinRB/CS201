//
// Created by olinr on 3/3/2022.
//

// C program to implement sighup(), sigint()
// and sigquit() signal functions
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// function declaration
void handler1(int signum) {
    printf("this is handler1(): got a signal %d\n", signum);
}


// driver code
int main() {
    int pid = fork();
    struct sigaction sa = {0};
    sa.sa_handler = &handler1;
    sigaction(SIGUSR1, &sa, NULL);
    if (pid == -1)
        return 1;
    if (pid == 0)  {
        printf("This is the child process, PID: %d", getpid());
        //kill(getpid(), SIGUSR1);
    } else {
        printf("This is the parent process, PID: %d", getpid());
        wait(NULL);
    }
    return 0;
}

