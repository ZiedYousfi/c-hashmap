#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>

typedef struct HashMap {
  int size;      // Number of elements in the hash map
  int capacity;  // Total capacity of the hash map
  int *keys;     // Array to store keys
  int *values;   // Array to store values
} HashMap;

HashMap *create_hashmap(int capacity);

#endif /* HASHMAP_H */
