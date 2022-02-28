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

