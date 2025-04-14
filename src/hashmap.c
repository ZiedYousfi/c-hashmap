#include "hashmap.h"

/**
 * Fonction de hachage générique qui prend n'importe quel type de données
 * et retourne une valeur de hachage entière
 *
 * @param data      Pointeur vers les données à hacher
 * @param size      Taille en octets des données
 * @param type      Type de données (utiliser les constantes définies dans l'en-tête)
 * @return          Valeur de hachage générée
 */
int hash_function(const void* data, size_t size, int type) {
    if (!data) return 0;

    unsigned int hash = 5381; // Constante de base (nombre premier)

    // Pour les types communs, nous utilisons des méthodes de hachage optimisées
    switch (type) {
        case HASH_TYPE_INT:
            return *((int*)data) % INT_MAX;

        case HASH_TYPE_STRING: {
            const char* str = (const char*)data;
            // Algorithme de hachage djb2
            while (*str) {
                hash = ((hash << 5) + hash) + *str++; // hash * 33 + c
            }
            return (int)(hash % INT_MAX);
        }

        case HASH_TYPE_FLOAT: {
            // Convertit le float en représentation binaire pour le hachage
            float f = *((float*)data);
            return hash_function(&f, sizeof(float), HASH_TYPE_GENERIC);
        }

        case HASH_TYPE_GENERIC:
        default: {
            // Pour les types génériques, nous hachons les octets bruts
            const unsigned char* bytes = (const unsigned char*)data;
            for (size_t i = 0; i < size; i++) {
                hash = ((hash << 5) + hash) + bytes[i];
            }
            return (int)(hash % INT_MAX);
        }
    }
}

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

