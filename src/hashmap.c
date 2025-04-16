#include "hashmap.h"

/**
 * Fonction de hachage générique qui prend n'importe quel type de données
 * et retourne une valeur de hachage entière
 *
 * @param data      Pointeur vers les données à hacher
 * @param size      Taille en octets des données
 * @param type      Type de données (utiliser les constantes définies dans
 * l'en-tête)
 * @return          Valeur de hachage générée
 */
int hash_function(const void *data, size_t size, int type) {
  if (!data) return 0;

  unsigned int hash = 5381;  // Constante de base (nombre premier)

  // Pour les types communs, nous utilisons des méthodes de hachage optimisées
  switch (type) {
    case HASH_TYPE_INT:
      return *((int *)data) % INT_MAX;

    case HASH_TYPE_STRING: {
      const char *str = (const char *)data;
      // Algorithme de hachage djb2
      while (*str) {
        hash = ((hash << 5) + hash) + *str++;  // hash * 33 + c
      }
      return (int)(hash % INT_MAX);
    }

    case HASH_TYPE_FLOAT: {
      // Convertit le float en représentation binaire pour le hachage
      float f = *((float *)data);
      return hash_function(&f, sizeof(float), HASH_TYPE_GENERIC);
    }

    case HASH_TYPE_GENERIC:
    default: {
      // Pour les types génériques, nous hachons les octets bruts
      const unsigned char *bytes = (const unsigned char *)data;
      for (size_t i = 0; i < size; i++) {
        hash = ((hash << 5) + hash) + bytes[i];
      }
      return (int)(hash % INT_MAX);
    }
  }
}

int hash_to_key_for_specific_hash_map(int hash, HashMap hashmap) {
  return hash % hashmap.size;
}

int add_value_to_hashmap(const void *data, HashMap *hashmap,
                         size_t value_size) {
  if ((hashmap->size + 1) > hashmap->capacity) {
    int new_capacity = hashmap->capacity * 2;
    int *new_keys = realloc(hashmap->keys, sizeof(int) * new_capacity);
    void *new_values = realloc(hashmap->values, value_size * new_capacity);

    if (!new_keys || !new_values) {
      if (new_keys) free(new_keys);
      if (new_values) free(new_values);
      return 1;
    }

    hashmap->keys = new_keys;
    hashmap->values = new_values;
    hashmap->capacity = new_capacity;
  }

  int data_hash = hash_function(data, value_size, HASH_TYPE_GENERIC);

  hashmap->keys[hashmap->size] = data_hash;
  memcpy((char *)hashmap->values + (hashmap->size * value_size), data,
         value_size);
  hashmap->size += 1;
  return 0;
}

int get_value_of_hashmap(int key, HashMap hashmap, void *value,
                         size_t value_size) {
  for (int i = 0; i < hashmap.size; i++) {
    if (hashmap.keys[i] == key) {
      memcpy(value, (char *)hashmap.values + (i * value_size), value_size);
      return 0;
    }
  }
  return 1;
}

// Hashmap memory mangement
HashMap *create_hashmap(int capacity, int size) {
  HashMap *hm = malloc(sizeof(HashMap));
  if (!hm) {
    return NULL;
  }

  hm->capacity = capacity;

  hm->size = size;

  if (hm->size == 0) {
    if (hm->capacity >= 1) {
      hm->size = 1;
      fprintf(stderr, "Warning: size shouldn't be 0\n");
    } else {
      fprintf(stderr, "Error: capacity must be greater than 0\n");
      free(hm);
      return NULL;
    }
  }

  if (size <= hm->capacity) {
    hm->values = malloc(sizeof(int) * hm->size);
    if (!hm->values) {
      free(hm);
      return NULL;
    }
    hm->keys = malloc(sizeof(int) * hm->size);
    if (!hm->keys) {
      free(hm->values);
      free(hm);
      return NULL;
    }
  } else {
    fprintf(stderr, "Error: size exceeds capacity\n");
    free(hm);
    return NULL;
  }

  return hm;
}

int free_hashmap(HashMap *hm) {
  if (hm->values != NULL) {
    free(hm->values);
    printf("Freeing values\n");
    hm->values = NULL;
  }

  if (hm->keys != NULL) {
    free(hm->keys);
    printf("Freeing keys\n");
    hm->keys = NULL;
  }
  free(hm);
  hm = NULL;
  printf("Freeing hashmap\n");
  return 0;
}
