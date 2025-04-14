#include <stdio.h>
#include "hashmap.h"

int main(void) {
    printf("Hello from hashmap!\n");

    HashMap *hm = create_hashmap(2);
    if (!hm) {return 1;}


    free(hm);
    return 0;
}
