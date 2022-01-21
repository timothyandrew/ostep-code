#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int pid = fork();

  if (pid < 0) {
    fprintf(stderr, "fork failed, exiting!\n");
    exit(1);
  } else if (pid == 0) {
    fprintf(stderr, "child alive: %d\n", getpid());
    sleep(3);
    exit(15);
  } else {
    int code;
    pid_t child = wait(&code);
    fprintf(stderr, "child: %d, code: %d\n", child, WEXITSTATUS(code));
  }

  return 0;
}