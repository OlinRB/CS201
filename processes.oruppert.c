// jdh CS201 S22

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define BUFFER_SIZE 32


void handle_sigusr1(int sig) {
    printf("Handler called....");
    printf("Got signal %d", sig);
}


int main(int argc, char *argv[]) {
    int pid;
    int memid;
    int key = IPC_PRIVATE;
    char *ptr;
    char buffer[BUFFER_SIZE];

    strcpy(buffer, "hello from me");

    memid = shmget(key, BUFFER_SIZE, IPC_EXCL | 0666);
    if (memid < 0) {
        printf("shmget() failed\n");
        return(8);
    }

    pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
        return(8);
    }

    if (pid > 0) {
        // this is the parent
        struct sigaction sa = {0};
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);



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
        pid = getpid();
        printf("I am the child, and my pid is %d\n", pid);
        ptr = (char *) shmat(memid, 0, 0);
        if (ptr == NULL) {
            printf("shmat() in child failed\n");
            return(8);
        }
        printf("I am the child, and I read this from the shared memory: '%s'\n", ptr);
        shmdt(ptr);
        kill(pid, SIGUSR1);
    }

    shmdt(ptr);
    shmctl(memid, IPC_RMID, NULL);

    return 0;
}
