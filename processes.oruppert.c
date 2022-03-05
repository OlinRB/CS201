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


void handler1(int signum) {
    if (signum == SIGUSR1) {
        printf("\nGot SIGUSR1, PID: %d\n", getpid());
        //done = 1;

        //printf("this is handler1(): got a signal %d\n", signum);
    }
    if (signum == SIGUSR2) {
        printf("\nGot SIGUSR2, PID: %d\n", getpid());
        //printf("this is handler2(): got a signal %d\n", signum);
        done = 0;
    }

}

int main() {
    // Memory
    int memid;
    int key = IPC_PRIVATE;
    char *ptr;
    char buffer[BUFFER_SIZE];
    int memidLoop;
    int keyLoop = IPC_PRIVATE;
    char *ptrLoop;
    char bufferLoop[BUFFER_SIZE];
    char wordList[3][BUFFER_SIZE] = {"from", "jason", "done"};

    strcpy(buffer, "hello");
    // Signals
    int pid;
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = handler1;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    done = 1;
    memid = shmget(key, BUFFER_SIZE, IPC_EXCL | 0666);
    if (memid < 0) {
        printf("shmget() failed\n");
        return(8);
    }
    pid = fork();
    for (int i = 0; i < 4; ++i){
        if (pid > 0) {
            printf("Inside Parent\n");
            while (!done) {
                // Wait until reading is done
            }
            printf("I am the parent, pid: %d\n", getpid());
            ptr = (char *) shmat(memid, 0, 0);
            if (ptr == NULL) {
                printf("shmat() failed\n");
                return (8);
            }
            printf("Parent is writing '%s' to the shared memory\n", buffer);
            strcpy(buffer, (const char *) (wordList + i));
            strcpy(ptr, buffer);
            wait(NULL);
            kill(getpid(), SIGUSR1);
        } else {
            printf("Inside Child\n");
            while (!done) {
                // Wait until writing is done
            }
            ptr = (char *) shmat(memid, 0, 0);
            //ptrLoop = (char *) shmat(memidLoop, 0, 0);
            printf("I am the child, and I read this from the shared memory: '%s'\n", ptr);
            shmdt(ptr);
            kill(getpid(), SIGUSR1);
            kill(getpid(), SIGUSR2);
        }
    }

    printf("done!\n");
    return 0;
}

