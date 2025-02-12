#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

class LinkedList {
private:
    Node* head; 

public:
    LinkedList();
    ~LinkedList();

    Node* getHead();
    void removeHead();
    void removeAfterHead(Node* prevNode);
    void insert(int key, int value);
    void remove(int searchKey);
    bool search(int searchKey);
};

#endif