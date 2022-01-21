#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int pid = fork();
  int pipefd[2];
  if (pipe(pipefd) != 0) {
    fprintf(stderr, "failed to create pipe\n");
  }

  if (pid < 0) {
    fprintf(stderr, "fork failed, exiting!\n");
    exit(1);
  } else if (pid == 0) {
    pid = fork();
    if (pid < 0) {
      fprintf(stderr, "fork failed, exiting!\n");
      exit(1);
    } else if (pid == 0) {
      // Child 2
      close(STDIN_FILENO);
      close(pipefd[1]);
      dup(pipefd[0]);
      execlp("wc", "wc", "-l", (char *)0);
    } else {
      // Child 1
      close(STDOUT_FILENO);
      close(pipefd[0]);
      dup(pipefd[1]);
      execlp("cat", "cat", "/usr/share/dict/web2", (char *)0);
    }
  } else {
    wait(NULL);
    fprintf(stderr, "All done!\n");
  }

  return 0;
}