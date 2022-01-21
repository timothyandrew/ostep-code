#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
  Write a program that calls fork(). Before calling fork(), 
  have the main process access a variable (e.g., x) and set
  its value to something (e.g., 100). What value is the variable
  in the child process? What happens to the variable when both
  the child and parent change the value of x?
*/

int main() {
  int x = 0;

  int pid = fork();

  if (pid < 0) {
    fprintf(stderr, "fork failed, exiting!\n");
    exit(1);
  } else if (pid == 0) {
    x = 15;
    fprintf(stderr, "child! %d\n", x);
  } else {
    wait(NULL);
    // Always zero, because memory isn't shared
    fprintf(stderr, "parent! %d\n", x);
  }

  return 0;
}