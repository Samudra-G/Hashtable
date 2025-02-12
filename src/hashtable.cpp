#include "HashTable.h"
#include <iostream>

HashTable::HashTable() : size(TABLE_SIZE), count(0) {
    table = new LinkedList*[size];
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < size; i++) {
        delete table[i];
    }
    delete[] table;
}

int HashTable::hashFunction(int key) {
    double fraction = (key * A) - floor(key * A);
    return floor(size * fraction);
}

void HashTable::rehash(LinkedList* newTable[], int newSize) {
    for (int i = 0; i < size; i++) {
        if (table[i] != nullptr) {
            Node* temp = table[i]->getHead();
            while (temp) {
                int newIndex = temp->key % newSize;
                if (newTable[newIndex] == nullptr)
                    newTable[newIndex] = new LinkedList();

                newTable[newIndex]->insert(temp->key, temp->value);
                temp = temp->next;
            }
        }
    }
}

void HashTable::resize() {
    int newSize = size * 2;
    LinkedList** newTable = new LinkedList*[newSize];

    for (int i = 0; i < newSize; i++) {
        newTable[i] = nullptr;
    }

    rehash(newTable, newSize);

    for (int i = 0; i < size; i++) {
        delete table[i];
    } 
    delete[] table;
    table = newTable;
    size = newSize;
}

void HashTable::insert(int key, int value) {
    double loadFactor = static_cast<double>(count) / size;

    if (loadFactor > 0.75) {
        resize();
    }

    int index = hashFunction(key);
    if (table[index] == nullptr)
        table[index] = new LinkedList();

    if (table[index]->search(key))
        table[index]->remove(key);
    else
        count++;

    table[index]->insert(key, value);
    
    //Debug output
    Node* temp = table[index]->getHead();
    while (temp) {
        temp = temp->next;
    }
    
}

bool HashTable::search(int key) {
    int index = hashFunction(key);
    if (table[index] == nullptr)
        return false;

    return table[index]->search(key);
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    if (table[index] == nullptr)
        return;

    if (table[index]->search(key)) {
        table[index]->remove(key);
        count--;
    }
}
//Getter functions
int HashTable::getSize() {
    return size;
}
LinkedList** HashTable::getTable() {
    return table;
}
int HashTable::getHash(int key) {
    return hashFunction(key);
}