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
    // Vars for shared mem
    int memid;
    int key = IPC_PRIVATE;
    char *ptr;
    char buffer[BUFFER_SIZE];
    done = 0;

    strcpy(buffer, "testing 12345");
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

    if (pid > 0) {
        // this is the parent
        printf("I am the parent, and my pid is %d\n", getpid());

        ptr = (char *) shmat(memid, 0, 0);
        if (ptr == NULL) {
            printf("shmat() failed\n");
            return(8);
        }

        printf("Parent is writing '%s' to the shared memory\n", buffer);
        strcpy(ptr, buffer);
        wait(NULL);

    } else {
        // this is the child
        printf("PID before new getPID: %d\n", pid);
        pid = getpid();
        printf("I am the child, and my pid is %d\n", pid);
        ptr = (char *) shmat(memid, 0, 0);
        if (ptr == NULL) {
            printf("shmat() in child failed\n");
            return (8);
        }

        printf("Child will do busywork for a little while\n");
        double d;
        for (int i = 0; i < 5000; ++i) {
            for (int j = 0; j < 5000; ++j) {
                d = d + (double) i / (double) j;
            }
        }
        d = d + 45;

        printf("I am the child, and I read this from the shared memory: '%s'\n", ptr);

        shmdt(ptr);
    }

//    printf("now wait for something to happen\n");
//    while ( ! done );

    printf("done!\n");
    return 0;
}

