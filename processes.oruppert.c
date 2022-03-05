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
#include <sys/wait.h>
#include <sys/shm.h>
#define BUFFER_SIZE 32
int done;
int going;
int finished;

void handler1(int signum) {
    if (signum == SIGUSR1) {
        //printf("\nGot SIGUSR1, PID: %d\n", getpid());
        done = 1;
    }
    if (signum == SIGUSR2) {
        //printf("\nGot SIGUSR2, PID: %d\n", getpid());
        finished = 1;
    }

}

int main() {
    // Constants
    going = 1;
    int result;
    int pid;

    struct sigaction action;

    // Memory
    int memid;
    int key = IPC_PRIVATE;
    char *ptr;
    char buffer[BUFFER_SIZE];
    char wordList[4][BUFFER_SIZE] = {"hello","from", "jason", "done"};

    strcpy(buffer, (const char *) wordList);

    memid = shmget(key, BUFFER_SIZE, IPC_EXCL | 0666);
    if (memid < 0) {
        printf("shmget() failed\n");
        return(8);
    }
    memset(&action, 0, sizeof(struct sigaction));
    pid = fork();
    int i = 3;
    if (pid > 0) {
        action.sa_handler = handler1;
        sigaction(SIGUSR1, &action, NULL);
        printf("Inside parent, pid: %d\n", getpid());
        while (going) {
            while (!done);
            ptr = (char *) shmat(memid, 0, 0);
            if (ptr == NULL) {
                printf("shmat() failed\n");
                return (8);
            }
            printf("Parent is writing '%s' to the shared memory\n", buffer);
            strcpy(buffer, (const char *) (wordList + i));
            strcpy(ptr, buffer);
            if (strcmp("done", ptr) == 0)
                going = 0;
        }
        wait(NULL);
    } else {
        pid = getpid();
        action.sa_handler = handler1;
        printf("I am the child and my PID is %d\n", pid);
        sigaction(SIGUSR2, &action, NULL);
        kill(getppid(), SIGUSR1)
        while (going) {
            ptr = (char *) shmat(memid,0,0);
            if (ptr == NULL) {
                printf("shmat() failed\n");
                return (8);
            }
            printf("I am the child and I am reading this from shared memory: %s\n", ptr);
            finished = 0;
            if (strcmp("done", ptr) == 0) {
                printf("Exiting");
                going = 0;
                return 0;
            } else {
                kill(getppid(), SIGUSR1));
                shmdt(ptr);
            }

        }

    }

    shmdt(ptr);
    shmctl(memid, IPC_RMID, NULL);
}

