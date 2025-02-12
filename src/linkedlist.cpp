#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current) {
        Node* newNode = current->next;
        delete current;
        current = newNode;
    }
}

Node* LinkedList::getHead() {
    return head;
}

void LinkedList::removeHead() {
    Node* tempNode = head;
    head = head->next;
    delete tempNode;
}

void LinkedList::removeAfterHead(Node* prevNode) {
    Node* tempNode = prevNode->next;
    prevNode->next = prevNode->next->next;
    tempNode->next = nullptr;
    delete tempNode;
}

void LinkedList::insert(int key, int value) {
    Node* newNode = new Node(key, value);
    if (!newNode) {
        std::cout << "Memory allocation failed." << std::endl;
        return;
    }
    newNode->next = head;
    head = newNode;

    Node* temp = head;
    while (temp) {
        temp = temp->next;
    }
}

void LinkedList::remove(int searchKey) {
    if (!head) {
        std::cout << "Table is empty." << std::endl;
        return;
    }
    if (head->key == searchKey) {
        removeHead(); 
        return;
    }

    Node* temp = head;
    while (temp && temp->next) {
        if (temp->next->key == searchKey) {
            removeAfterHead(temp);
            return;
        }
        temp = temp->next;
    }
    std::cout << "Key not found." << std::endl;
}

bool LinkedList::search(int searchKey) {
    Node* temp = head;
    while (temp) {
        if (temp->key == searchKey) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
