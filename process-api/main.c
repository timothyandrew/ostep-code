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
  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "Failed to fork!\n");
    exit(1);
  } else if (rc == 0) {
    // Child
    sleep(1);
    fprintf(stderr, "Hi from child\n");

    char *args[] = { "env", NULL };
    char *env[] = { "PATH=/tmp", NULL };
    int result = execvpe(args[0], args, env);

    if (result == -1) {
      fprintf(stderr, "Failed to execute: %s\n", strerror(errno));
      exit(1);
    }
  } else {
    // Parent
    wait(NULL);
    fprintf(stderr, "Parent exiting\n");
  }
}