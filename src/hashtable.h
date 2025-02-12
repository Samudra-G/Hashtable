#ifndef HASHTABLE_H
#define HASHTABLE_H

static constexpr double A = 0.6180339887; // Golden ratio fraction

#include "LinkedList.h"
#include <cmath>

#define TABLE_SIZE 11

class HashTable {
private:
    LinkedList** table;
    int size;
    int count;

    int hashFunction(int key);
    void rehash(LinkedList* newTable[], int newSize);
    void resize();

public:
    HashTable();
    ~HashTable();

    void insert(int key, int value);
    bool search(int key);
    void remove(int key);
    int getSize();
    LinkedList** getTable();
    int getHash(int key);
};

#endif