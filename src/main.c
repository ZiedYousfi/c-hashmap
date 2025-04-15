#include "hashmap.h"

void print_hashmap(HashMap hm) {
  // Print hashmap details
  printf("Hashmap created:\n");
  printf("  Size: %d\n", hm.size);
  printf("  Capacity: %d\n", hm.capacity);

  // Print keys and values
  printf("Hashmap contents:\n");
  for (int i = 0; i < hm.capacity; i++) {
    printf("  Index %d: ", i);
    if (i < hm.size) {
      printf("Key: %d, Value: %d\n", hm.keys[i], ((int *)hm.values)[i]);
    } else {
      printf("Empty\n");
    }
  }
}

int main(void) {
  setbuf(stdout, NULL);
  printf("Hello from hashmap!\n");

  HashMap *hm = create_hashmap(2, 0);
  if (!hm) {
    return 1;
  }

  print_hashmap(*hm);

  int test_1 = 19;
  int *p_test_1 = &test_1;

  add_value(p_test_1, hm, sizeof(p_test_1));

  print_hashmap(*hm);

  free(hm);
  return 0;
}
