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
    fprintf(stderr, "hello\n");
  } else {
    // wait(NULL);
    waitpid(pid, NULL, 0);
    fprintf(stderr, "goodbye\n");
  }

  return 0;
}