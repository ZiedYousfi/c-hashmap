#include "hashmap.h"

int main(void) {
    setbuf(stdout, NULL);
    printf("Hello from hashmap!\n");

    HashMap *hm = create_hashmap(2, 1);
    if (!hm) {return 1;}

    // Print hashmap details
    printf("Hashmap created:\n");
    printf("  Size: %d\n", hm->size);
    printf("  Capacity: %d\n", hm->capacity);

    // Print keys and values
    printf("Hashmap contents:\n");
    for (int i = 0; i < hm->capacity; i++) {
        printf("  Index %d: ", i);
        if (i < hm->size) {
            printf("Key: %d, Value: %d\n", hm->keys[i], hm->values[i]);
        } else {
            printf("Empty\n");
        }
    }

    free(hm);
    return 0;
}
