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
    int pid;
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = handler1;
    sigaction(SIGUSR1, &action, NULL);

    /* get child process */
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    // Print out PIDs
    if (getpid() > 0) {
        // I am the parent
        printf("I am the parent, and my pid is %d\n", getpid());
        wait(NULL);
    } else {
        printf("I am the child, and my pid is %d\n", getpid());
    }

//    for (int i = 0; i < 3; ++i) {
//        if (pid == 0) { /* child */
//
//            for (;;); /* loop for ever */
//        } else /* parent */
//        { /* pid hold id of child */
//            printf("\nPARENT: sending SIGHUP\n\n");
//            kill(pid, SIGHUP);
//
//            printf("\nPARENT: sending SIGINT\n\n");
//            kill(pid, SIGINT);
//
//            printf("\nPARENT: sending SIGQUIT\n\n");
//            kill(pid, SIGQUIT);
//        }

}

