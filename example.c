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
void sighup();
void sigint();
void sigquit();

// driver code
int main() {
    int pid;

    /* get child process */
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    // Print out PIDs
    if (getpid() > 0) {
        // I am the parent
        printf("I am the parent, and my pid is %d", getpid());
    } else {
        printf("I am the child, and my pid is %d", getpid());
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

