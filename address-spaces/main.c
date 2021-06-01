#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main (int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: address-spaces <mb>\n");
    exit(1);
  }

  int mb = atoi(argv[1]);
  if (mb <= 0) {
    fprintf(stderr, "count needs to be > 0\n");
    exit(1);
  }


  long count = (1024 * 1024 / sizeof(int)) * mb;
  fprintf(stderr, "Going to allocate %lu bytes (pid: %d)\n", count * sizeof(int), getpid());

  int limit = 999999;
  int *mem = (int *)malloc(sizeof(int) * count);

  for(;;) {
    for (int i = 0; i < count; i++) {
      mem[i] = (mem[i] + 1) % limit;
    }
  }
  
  fprintf(stdout, "Done\n");
}
