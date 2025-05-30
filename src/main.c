/*
 * main.c
 *
 * Main file for the hash map implementation in C.
 */

#include "hashmap.h"

/**
 * Print a value from the hash map based on its type.
 * @param hm    The hash map.
 * @param i     The index of the value to print.
 */
void print_value(HashMap hm, int i){

  printf("Value: ");

  switch (hm.type)
  {
  case HASH_TYPE_INT:
    printf("%d", ((int *)hm.values)[i]);
    break;

  case HASH_TYPE_STRING:
    printf("%s", ((char **)hm.values)[i]);
    break;
  case HASH_TYPE_FLOAT:
    printf("%f", ((float *)hm.values)[i]);
    break;
  case HASH_TYPE_GENERIC:
    printf("%p", ((void **)hm.values)[i]);
    break;

  default:
    break;
  }
}

void print_hashmap(HashMap hm) {
  // Print hashmap details
  printf("Hashmap created:\n");
  printf("  Size: %d\n", hm.size);
  printf("  Capacity: %d\n", hm.capacity);

  // Print keys and values
  printf("Hashmap contents:\n");
  for (int i = 0; i < hm.size; i++) {
    printf("  Index %d: ", i);
    if (i < hm.size) {
      printf("Key: %d, ", hm.keys[i]);
      print_value(hm, i);
      printf("\n");
    } else {
      printf("Empty\n");
    }
  }
}

int main(void) {
  setbuf(stdout, NULL);
  printf("Hello from hashmap!\n");

  HashMap *hm = create_hashmap(2, 2, HASH_TYPE_INT);
  if (!hm) {
    fprintf(stderr, "Error: failed to create hashmap\n");
    return 1;
  }

  print_hashmap(*hm);

  for (int i = 0; i < 10; i++) {
    int value = i * 10;
    int *p_value = &value;
    if (add_value_to_hashmap(p_value, hm) != 0){
      fprintf(stderr, "Error: failed to add value %d to hashmap\n", value);
      if (free_hashmap(hm) != 0) {
        fprintf(stderr, "Error: failed to free hashmap\n");
        return 3;
      }
      return 2;
    }
    print_hashmap(*hm);
  }

  if (free_hashmap(hm) != 0) {
    fprintf(stderr, "Error: failed to free hashmap\n");
    return 3;
  }
  return 0;
}
