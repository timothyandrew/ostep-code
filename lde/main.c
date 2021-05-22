#include <x86intrin.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
  int file = open("/tmp/foo.txt", O_RDONLY);
  char buf[64];
  int iterations = 10000;
  double hz = 4199000000;

  unsigned long long start = __rdtsc();
  for(int i = 0; i < iterations; i++) read(file, NULL, 0);
  unsigned long long end = __rdtsc();
 
  double foo = (end - start) * 1000 * 1000 / iterations / hz;
  printf("System call overhead: %fμs\n", foo);
}