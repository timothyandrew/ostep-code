#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Vector {
    int *vec;
    int capacity;
};

struct Vector create_vector(int size) {
  struct Vector v = {
    (int *) malloc(sizeof(int) * size),
    size
  };

  return v;
}

void set_value_at(struct Vector *v, int index, int value) {
  if (index >= v->capacity) {
    int *result = realloc(v->vec, sizeof(int) * index * 2);

    if (result == 0) {
      fprintf(stderr, "Realloc failed\n");
      exit(1);
    }

    v->vec = result;
    v->capacity = index * 2;
  }

  v->vec[index] = value;
}

int get_value_at(struct Vector v, int index) {
  if (index >= v.capacity) {
    fprintf(stderr, "Out of bounds - capacity: %d, requested: %d\n", v.capacity, index);
    exit(1);
  }

  return v.vec[index];
}


int main (int argc, char *argv[]) {
  struct Vector vec = create_vector(20);

  int index = 200;

  fprintf(stderr, "capacity: %d\n", vec.capacity);
  set_value_at(&vec, index, 8008);
  fprintf(stderr, "capacity: %d\n", vec.capacity);

  fprintf(stdout, "value: %d\n", get_value_at(vec, index));
}