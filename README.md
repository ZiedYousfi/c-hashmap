# C HashMap Implementation

A generic, type-flexible hash map implementation in C that supports integers, strings, floats, and generic data types.

## Features

- Support for multiple data types:
  - Integers (`HASH_TYPE_INT`)
  - Strings (`HASH_TYPE_STRING`)
  - Floating-point numbers (`HASH_TYPE_FLOAT`)
  - Generic types (`HASH_TYPE_GENERIC`)
- Dynamic resizing when capacity is reached
- Simple API for creation, insertion, retrieval, and cleanup
- Memory-efficient implementation

## Installation

Clone the repository and build the project:

```bash
git clone github.com/ZiedYousfi/c-hashmap
cd c-hashmap
make
```

## Usage Examples

### Basic Usage

```c
#include "hashmap.h"

int main() {
    // Create a hashmap that stores integers
    HashMap *hm = create_hashmap(10, 1, HASH_TYPE_INT);

    // Add values
    int value = 42;
    add_value_to_hashmap(&value, hm);

    // Retrieve values
    int retrieved;
    int hash_value = hash_function(&value, sizeof(int), HASH_TYPE_INT);
    if (get_value_of_hashmap(hash_value, *hm, &retrieved) == 0) {
        printf("Retrieved: %d\n", retrieved);
    }

    // Clean up
    free_hashmap(hm);

    return 0;
}
```

### String Example

```c
// Create a hashmap for strings
HashMap *str_map = create_hashmap(5, 1, HASH_TYPE_STRING);

// Add a string
char *str = "hello";
add_value_to_hashmap(&str, str_map);

// Retrieve the string
char *result;
int hash = hash_function(&str, sizeof(char*), HASH_TYPE_STRING);
if (get_value_of_hashmap(hash, *str_map, &result) == 0) {
    printf("Retrieved: %s\n", result);
}

free_hashmap(str_map);
```

## API Reference

### Data Structures

#### HashMap

```c
typedef struct HashMap {
  int size;          // Number of elements in the hash map
  int capacity;      // Total capacity of the hash map
  int *keys;         // Array to store keys (hash values)
  void *values;      // Array to store values
  size_t values_size;// Size of each value in bytes
  int type;          // Type of data stored
} HashMap;
```

### Functions

#### Creating/Destroying a HashMap

```c
// Create a new hashmap
HashMap *create_hashmap(int capacity, int size, int type);

// Free the hashmap
int free_hashmap(HashMap *hm);
```

#### Working with Values

```c
// Add a value to the hashmap
int add_value_to_hashmap(const void *data, HashMap *hashmap);

// Retrieve a value from the hashmap
int get_value_of_hashmap(int key, HashMap hashmap, void *value);
```

#### Hashing

```c
// Generate a hash value for data
int hash_function(const void *data, size_t size, int type);

// Convert a hash to an index for a specific hashmap
int hash_to_key_for_specific_hash_map(int hash, HashMap hashmap);
```

## Build and Testing

The project includes a Makefile for easy building and a GitHub workflow for CI:

- `make`: Builds the project
- `make clean`: Removes build artifacts
- `./bar.sh`: Builds and runs the project

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENCE.md) file for details.
