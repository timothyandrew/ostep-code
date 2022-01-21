#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
  exec

  l: program arguments as function arguments
  v: program arguments as string array
  e: pass env vars
  p: use PATH to find the program
*/

int main() {
  int pid = fork();

  if (pid < 0) {
    fprintf(stderr, "fork failed, exiting!\n");
    exit(1);
  } else if (pid == 0) {
    fprintf(stderr, "hello\n");
    int ret = execlp("bash", "bash", (char *)0);
    fprintf(stderr, "exec ret: %d\n", ret);
  } else {
    waitpid(pid, NULL, 0);
    fprintf(stderr, "goodbye\n");
  }

  return 0;
}