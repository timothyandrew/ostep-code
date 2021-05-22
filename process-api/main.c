#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  int rc = fork();
  int x = 42;

  if (rc < 0) {
    fprintf(stderr, "Failed to fork!\n");
    exit(1);
  } else if (rc == 0) {
    // Child
    sleep(2);
    x = x + 5;
    fprintf(stderr, "Hi from child (%d)!\n", x);
  } else {
    // Parent
    wait(NULL);
    x = x + 7;
    fprintf(stderr, "Parent exiting (%d)!\n", x);
  }
}