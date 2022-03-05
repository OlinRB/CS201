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
int cnt = 0;

void handler(int signum) {
    if (signum == SIGUSR1) {
        //printf("\nGot SIGUSR1, PID: %d\n", getpid());
        done = 1;
    }
    if (signum == SIGUSR2) {
        //printf("\nGot SIGUSR2, PID: %d\n", getpid());
        finished = 1;
    }
}

//void handler1(int signum) {
//    printf("Parent got signal %d\n", signum);
//    done = 1;
//}
//
//void handler2(int signum) {
//    printf("Child got signal %d\n", signum);
//    finished = 1;
//}

int main() {
    going = 1;
    int result;
    int pid;
    struct sigaction action;
    int memid;
    int key = IPC_PRIVATE;
    char *ptr;
    char buffer[BUFFER_SIZE];
    char wordList[4][BUFFER_SIZE] = {"hello","from", "jason", "done"};

    //strcpy(buffer, (const char *) wordList);
    //strcpy(buffer, "done");

    memid = shmget(key, BUFFER_SIZE, IPC_EXCL | 0666);
    if (memid < 0) {
        printf("shmget() failed\n");
        return(8);
    }
    memset(&action, 0, sizeof(struct sigaction));
    pid = fork();
    if (pid < 0) {
        printf("Fork failed");
        return (8);
    }

    if (pid > 0) {
        action.sa_handler = handler;
        sigaction(SIGUSR1, &action, NULL);
        printf("\nI am the parent and my pid is: %d\n", getpid());
        while (going==1) {
            while (! done );
            done = 0;
            ptr = (char *) shmat(memid, 0, 0);
            if (ptr == NULL) {
                printf("shmat() failed\n");
                return (8);
            }
            strcpy(buffer, (const char *) (wordList + cnt));
            printf("Parent is writing '%s' to the shared memory\n", buffer);
            strcpy(ptr, buffer);
            ++cnt;
            kill(pid, SIGUSR2);
            if (strcmp("done", ptr) == 0)
                going = 0;
        }
        wait(NULL);
    } else {
        pid = getpid();
        action.sa_handler = handler;
        printf("I am the child and my pid is %d\n", pid);
        sigaction(SIGUSR2, &action, NULL);
        kill(getppid(), SIGUSR1);
        while (going) {
            while (!finished);
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
                kill(getppid(), SIGUSR1);
                shmdt(ptr);
            }

        }

    }

    shmdt(ptr);
    shmctl(memid, IPC_RMID, NULL);
    return 0;
}

