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
  int file = open("/tmp/foo.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

  if (file == -1) {
    fprintf(stderr, "Failed to open file: %s\n", strerror(errno));
    exit(1);
  }

  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "Failed to fork!\n");
    exit(1);
  } else if (rc == 0) {
    // Child
    sleep(2);
    fprintf(stderr, "Hi from child\n");

    char contents[] = "this is inside the parent!\n";
    int result = write(file, contents, strlen(contents));

    if (result == -1) {
      fprintf(stderr, "Failed to write to file: %s\n", strerror(errno));
      exit(1);
    }

    close(file);

  } else {
    // Parent

    char contents[] = "this is inside the file!\n";
    int result = write(file, contents, strlen(contents));

    if (result == -1) {
      fprintf(stderr, "Failed to write to file: %s\n", strerror(errno));
      exit(1);
    }

    wait(NULL);
    close(file);

    fprintf(stderr, "Parent exiting\n");
  }
}