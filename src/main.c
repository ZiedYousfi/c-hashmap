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

  for (int i = 0; i < 10; i++) {
    int value = i * 10;
    int *p_value = &value;
    add_value(p_value, hm, sizeof(int));
    print_hashmap(*hm);
  }

  free(hm);
  return 0;
}
