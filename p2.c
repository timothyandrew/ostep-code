#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
  Write a program that opens a file (with the open() system call) 
  and then calls fork() to create a new process. Can both the child
  and parent access the file descriptor returned by open()? What 
  happens when they are writing to the file concurrently?
*/

int main() {
  int fd = open("/tmp/foobar.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
  int pid = fork();

  if (pid < 0) {
    fprintf(stderr, "fork failed, exiting!\n");
    exit(1);
  } else if (pid == 0) {
    char *s = "child\n";
    int written = write(fd, s, strlen(s));

    fprintf(stderr, "child! %d\n", written);
  } else {
    char *s = "parent\n";
    int written = write(fd, s, strlen(s));

    wait(NULL);
    fprintf(stderr, "parent! %d\n", written);
  }

  return 0;
}