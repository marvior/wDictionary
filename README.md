# WDictionary is a Polymorphic Generic Dictionary in C

A lightweight, polymorphic dictionary (hash map) implementation written in pure C (C11). This library supports nesting dictionaries inside other dictionaries and maps keys to different data types seamlessly using compile-time type dispatching.

** Features

* **Polymorphic Inserter:** Uses C11 `_Generic` macros to automatically choose the correct insertion function based on the input type (`char*` or `Dict*`).
* **Nested Structures:** Supports dictionary-in-dictionary nesting, allowing you to build complex JSON-like hierarchical structures in C.
* **Collision Resolution:** Implements a hash map with separate chaining (linked lists) using the public-domain **FNV-1a** 64-bit hashing algorithm.
* **Safe Memory Management:** Features automated deep recursive cleanup via `free_dict()` to free all slots, keys, strings, and dynamically nested dictionaries without memory leaks.

---

## ⚠️ Disclaimer / Production Environment Notice

This project was developed strictly for **educational and learning purposes** to explore data structures and polymorphism in C. 

**DO NOT USE THIS CODE IN PRODUCTION ENVIRONMENTS.**

This implementation has not been audited for security vulnerabilities, concurrency (thread safety), or production-scale workloads (such as Hash Collision DoS attacks). Use it in real-world applications entirely at your own risk.

---

## Project Structure

* `wdictionary.h`: Library header containing types, structures, and the `insert` generic macro.
* `wdictionary.c`: Core dictionary implementation (insertion, lookup, memory management).
* `hash_fnv1a_64.h` / `.c`: The 64-bit FNV-1a hashing function implementation.
* `main.c`: Example entry point showcasing creation, insertion of strings and nested dictionaries, and safe deletion.

## List function 

### `Dict * create_dictionary(int capacity);`
* **Purpose:** Allocates and initializes a new empty dictionary.
* **Input:** An integer specifying the hash table size (e.g., `10`).
* **Returns:** A pointer to the ready-to-use dictionary (`Dict *`).

### `insert(dict, key, value)`
* **Prototype/Macro:** `#define insert(dict, key, value) 
* **Purpose:** Inserts a key-value pair into the dictionary. If the key already exists, it automatically updates the value.
* **Smart Feature:** It automatically detects the data type at compile-time. It seamlessly supports **strings** (`char*` / `const char*`), **integers** (`int`), and **other dictionaries** (`Dict *`) to create nested configurations.
* **For example:**
  ```c
  Dict * mydict = create_dictionary(CAPACITY);
  Dict * mydict2 = create_dictionary(CAPACITY);
  insert(mydict2,"ciao","mondo");
  insert(mydict, "hello", mydict2);
  insert(mydict, "hi", 10);
  insert(mydict, "re", "Baby1");

### `void * get_value(Dict * dict, const char * key);`
* **Purpose:** Retrieves the value previously saved with that key.
* **Returns:** A generic pointer (`void *`). You just need to cast it when reading (e.g., `(char *)` for text or `(int *)` for numbers). Returns `NULL` if the key does not exist.

### `ListKeys * get_keys(Dict * dict);`
* **Purpose:** Extracts the complete list of all the keys currently stored inside the dictionary.
* **Returns:** A linked list of strings (`ListKeys *`) that you can easily iterate through using a `while` loop with `list->next`.

### `void free_dict(Dict * dict);`
* **Purpose:** **The most critical function.** It performs a deep, recursive memory cleanup. It automatically frees the dictionary, all keys, texts, numbers, and dynamically destroys any nested sub-dictionary, leaving zero memory leaks.


## Quick Start (Compilation)

To compile the project with GCC/CC, pass all source files to the compiler:

cc main.c wdictionary.c hash_fnv1a_64.c -o dictionary_demo
./dictionary_demo
