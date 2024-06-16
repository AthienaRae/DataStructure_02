Write a C program to create a hash table and perform collision resolution using the following techniques.
(i)	Open addressing
(ii)	Closed Addressing
(iii)	Rehashing 

Algorithm:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

struct HashEntry {
    int key;
    int data;
};

struct HashTable {
    struct HashEntry **table;
    int size;
};

struct HashTable *createHashTable(int size) {
    struct HashTable *hashTable = (struct HashTable *)malloc(sizeof(struct HashTable));
    if (hashTable == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    hashTable->size = size;
    hashTable->table = (struct HashEntry **)malloc(size * sizeof(struct HashEntry *));
    if (hashTable->table == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

int hashCode(struct HashTable *hashTable, int key) {
    return key % hashTable->size;
}

void insertOpenAddressing(struct HashTable *hashTable, int key, int data) {
    int index = hashCode(hashTable, key);
    while (hashTable->table[index] != NULL) {
        index = (index + 1) % hashTable->size;
    }
    struct HashEntry *entry = (struct HashEntry *)malloc(sizeof(struct HashEntry));
    entry->key = key;
    entry->data = data;
    hashTable->table[index] = entry;
}

void insertClosedAddressing(struct HashTable *hashTable, int key, int data) {
    int index = hashCode(hashTable, key);
    if (hashTable->table[index] == NULL) {
        struct HashEntry *entry = (struct HashEntry *)malloc(sizeof(struct HashEntry));
        entry->key = key;
        entry->data = data;
        hashTable->table[index] = entry;
    } else {
        while (hashTable->table[index] != NULL) {
            index = (index + 1) % hashTable->size;
        }
        struct HashEntry *entry = (struct HashEntry *)malloc(sizeof(struct HashEntry));
        entry->key = key;
        entry->data = data;
        hashTable->table[index] = entry;
    }
}

void insertRehashing(struct HashTable *hashTable, int key, int data) {
    int index = hashCode(hashTable, key);
    if (hashTable->table[index] == NULL) {
        struct HashEntry *entry = (struct HashEntry *)malloc(sizeof(struct HashEntry));
        entry->key = key;
        entry->data = data;
        hashTable->table[index] = entry;
    } else {
        int newIndex = (index + 1) % hashTable->size;
        while (newIndex != index) {
            if (hashTable->table[newIndex] == NULL) {
                struct HashEntry *entry = (struct HashEntry *)malloc(sizeof(struct HashEntry));
                entry->key = key;
                entry->data = data;
                hashTable->table[newIndex] = entry;
                return;
            }
            newIndex = (newIndex + 1) % hashTable->size;
        }
        printf("Hash table is full. Rehashing required!\n");
    }
}

void displayHashTable(struct HashTable *hashTable) {
    printf("Hash Table:\n");
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i] != NULL) {
            printf("Index %d: Key=%d, Data=%d\n", i, hashTable->table[i]->key, hashTable->table[i]->data);
        } else {
            printf("Index %d: NULL\n", i);
        }
    }
}

void deleteHashTable(struct HashTable *hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i] != NULL) {
            free(hashTable->table[i]);
        }
    }
    free(hashTable->table);
    free(hashTable);
}

int main() {
    struct HashTable *hashTable = createHashTable(TABLE_SIZE);

    insertOpenAddressing(hashTable, 10, 20);
    insertClosedAddressing(hashTable, 15, 25);
    insertRehashing(hashTable, 20, 30);

    displayHashTable(hashTable);

    deleteHashTable(hashTable);

    return 0; 

