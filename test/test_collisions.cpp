#include "../src/hashtable.h"
#include <iostream>

int countCollisions(HashTable& ht){
    int collisionCount {0};
    LinkedList** table = ht.getTable();

    for (int i{0}; i < ht.getSize(); i++) { // Use dynamic size
        if (table[i] != nullptr) {
            Node* head = table[i]->getHead(); 
            if (head != nullptr) {
                int chainLength {0};
                Node* temp = head;

                std::cout << "Index " << i << "-> ";
                while (temp) {
                    std::cout << "(" << temp->key << ", " << temp->value << ") -> ";
                    chainLength++;
                    temp = temp->next;
                }
                std::cout << "nullptr" << std::endl;

                if (chainLength > 1)
                    collisionCount += (chainLength - 1); // Count extra nodes
            }
        }
    }
    
    return collisionCount;
}

int main() {
    HashTable ht;

    std::cout << "\n=== Inserting Elements ===\n";

    // Insert elements that will collide based on TABLE_SIZE = 11
    //Case 1: Basic
    int keys[] = {1, 12, 23, 5, 16};
    int values[] = {100, 200, 300, 500, 600};

    for (int i = 0; i < 5; i++) {
        ht.insert(keys[i], values[i]);
        std::cout << "Inserted (" << keys[i] << ", " << values[i] << ") at index " << (keys[i] % TABLE_SIZE) << "\n";
    }


    // Case 2: Force collision by inserting values mapping to same index
    std::cout << "\n=== Force Collisions ===\n";
    ht.insert(6, 700);  // 6 % TABLE_SIZE might collide
    ht.insert(17, 800); // 17 % TABLE_SIZE might collide
    ht.insert(28, 900); // Another intentional collision

    // Case 3: Insert a duplicate key (should update value, not add new node)
    std::cout << "\n=== Duplicate Key Test ===\n";
    ht.insert(1, 999); // Key 1 already exists, should update value

    // Case 4: Insert large numbers (check modulo behavior)
    std::cout << "\n=== Large Numbers Test ===\n";
    ht.insert(1001, 1111);
    ht.insert(2012, 2222);
    ht.insert(3023, 3333);

    // Count collisions and print result
    int collisions = countCollisions(ht);
    std::cout << "\nTotal number of collisions: " << collisions << std::endl;


    return 0;
}