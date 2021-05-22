#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    fprintf(stderr, "Failed to create pipe: %s\n", strerror(errno));
    exit(1);
  }

  int c1 = fork();

  if (c1 < 0) {
    fprintf(stderr, "Failed to fork first child!\n");
    exit(1);
  } 

  if (c1 == 0) {
    close(pipefd[0]);

    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
      fprintf(stderr, "Failed to duplicate fd: %s\n", strerror(errno));
      exit(1);
    }

    char *args[] = { "cat", "/etc/passwd", NULL };
    execvp(args[0], args);
  } else {
    int c2 = fork();

    if (c2 < 0) {
      fprintf(stderr, "Failed to fork second child!\n");
      exit(1);
    } 

    if (c2 == 0) {
      close(pipefd[1]);

      if (dup2(pipefd[0], STDIN_FILENO) == -1) {
        fprintf(stderr, "Failed to duplicate fd: %s\n", strerror(errno));
        exit(1);
      }

      char *args[] = { "grep", "tim", NULL };
      execvp(args[0], args);
    } else {
      close(pipefd[0]);
      close(pipefd[1]);
      waitpid(c1, NULL, 0);
      waitpid(c2, NULL, 0);

      fprintf(stderr, "Parent exiting\n");
    }
  }
}