#include "../src/hashtable.h"
#include <iostream>
#include <chrono>

// Function to test insertion speed
void testPerformance(HashTable &ht, int numkeys){
    auto start = std::chrono::high_resolution_clock::now();

    for(int i{0}; i < numkeys; i++){
        ht.insert(i, i*10);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken to insert " << numkeys << " elements: " 
              << duration.count() << " seconds\n";
}
bool hasCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            std::cout << "⚠️ Cycle detected in linked list!\n";
            return true;
        }
    }
    return false;
}

// Function to count collisions
int countCollisions(HashTable& ht){
    int collisionCount {0};
    LinkedList** table = ht.getTable();

    for (int i{0}; i < ht.getSize(); i++) { 
        if (table[i] != nullptr) {
            Node* head = table[i]->getHead(); 
            if (head != nullptr) {
                if (hasCycle(head)) {
                    std::cout << "Cycle detected at index " << i << "!\n";
                    exit(1);
                }

                int chainLength {0};
                Node* temp = head;

                while (temp) {
                    chainLength++;
                    temp = temp->next;
                }

                if (chainLength > 1) {
                    collisionCount += (chainLength - 1);
                }
            }
        }
    }

    std::cout << "Total number of collisions: " << collisionCount << std::endl;
    std::cout << "Table size: " << ht.getSize() << std::endl;

    return collisionCount;
}

int main(){
    HashTable ht;
    testPerformance(ht, 10000);
    countCollisions(ht);
    return 0;
}
