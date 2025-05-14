/*
 * hashmap.h
 *
 * Header file for a generic hash map implementation in C.
 *
*/

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TYPE_INT 1
#define HASH_TYPE_STRING 2
#define HASH_TYPE_FLOAT 3
#define HASH_TYPE_GENERIC 4
#define INT_MAX 2147483647

typedef struct HashMap {
  int size;      // Number of elements in the hash map
  int capacity;  // Total capacity of the hash map
  int *keys;     // Array to store keys
  void *values;  // Array to store values
  size_t values_size;
  int type;
} HashMap;

int hash_function(const void *data, size_t size, int type);
HashMap *create_hashmap(int capacity, int size, int type);
int hash_to_key_for_specific_hash_map(int hash, HashMap hashmap);
int add_value_to_hashmap(const void *data, HashMap *hashmap);
int get_value_of_hashmap(int key, HashMap hashmap, void *value);
int free_hashmap(HashMap *hm);

#endif /* HASHMAP_H */
