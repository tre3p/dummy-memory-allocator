#include <stdio.h>
#include "../allocator.h"

int main() {
  int* first_ptr = (int*) mem_alloc(sizeof(int));
  int* second_ptr = (int*) mem_alloc(sizeof(int));

  *first_ptr = 15;
  *second_ptr = 9999;

  printf("First: %d\n", *first_ptr);
  printf("Second: %d\n", *second_ptr);

  mem_dealloc(first_ptr);
  mem_dealloc(second_ptr);
}