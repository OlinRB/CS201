// jdh 1-31-22
// CS 201 S22
//
// compile this and run it; then, in a second terminal window,
// do this command: "kill -SIGUSR1 <pid>" with the pid that this
// program prints out when it start

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int done;

void handler1(int signum) {
    if (signum == SIGUSR1)
        printf("\nGot SIGUSR1\n");
    if (signum == SIGUSR2)
        printf("\nGot SIGUSR2\n");
    printf("this is handler1(): got a signal %d\n", signum);
    done = 1;
}

int main() {
    int pid;
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = handler1;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    done = 0;
    pid = fork();
    if (pid > 0) {
        printf("I am the parent, pid: %d\n", getpid());
        kill(getpid(), SIGUSR1);
    } else {
        printf("I am the child, pid: %d\n", getpid());
        kill(getpid(), SIGUSR2);
    }
    while ( ! done );

    printf("done!\n");
    return 0;
}

