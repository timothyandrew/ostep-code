#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
  fprintf(stderr, "Starting as %d\n", getpid());
  int *x = (int *) malloc((sizeof(int) * 1024 * 1024 * 1024) - 4096);
  free(x);
}