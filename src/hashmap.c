#include "hashmap.h"

HashMap *create_hashmap(int capacity, int size) {
  HashMap *hm = malloc(sizeof(HashMap));
  if (!hm) {
    return NULL;
  }

  hm->capacity = capacity;
  if (size <= hm->capacity) {
    hm->size = size;
    hm->values = malloc(sizeof(int) * hm->size);
    hm->keys = malloc(sizeof(int) * hm->size);
  } else {
    fprintf(stderr, "Error: size exceeds capacity\n");
    free(hm);
    return NULL;
  }

  return hm;
}
