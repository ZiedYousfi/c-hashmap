#include "hashmap.h"

HashMap *create_hashmap(int capacity) {
  HashMap *hm = malloc(sizeof(HashMap));
  if (!hm) {
    return NULL;
  }

  return hm;
}
