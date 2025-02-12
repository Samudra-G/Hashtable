#ifndef NODE_H
#define NODE_H

class Node{
    public:
        int key;
        int value;
        Node* next;

        Node(int k, int v) : key(k), value(v), next(nullptr){} 

};

#endif