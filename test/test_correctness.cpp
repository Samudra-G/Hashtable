#include "../src/hashtable.h"
#include <iostream>

void testCorrectness(HashTable &ht) {
    // Insert test data
    ht.insert(1, 100);
    ht.insert(2, 200);
    ht.insert(3, 300);

    // Check if keys exist
    if (ht.search(1)) std::cout << "Test Passed: Key 1 exists\n";
    else std::cout << "Test Failed: Key 1 not found\n";

    if (ht.search(2)) std::cout << "Test Passed: Key 2 exists\n";
    else std::cout << "Test Failed: Key 2 not found\n";

    if (ht.search(3)) std::cout << "Test Passed: Key 3 exists\n";
    else std::cout << "Test Failed: Key 3 not found\n";

    // Check non-existent key
    if (!ht.search(999)) std::cout << "Test Passed: Non-existent Key correctly not found\n";
    else std::cout << "Test Failed: Non-existent Key found (incorrect)\n";
}

int main() {
    HashTable ht;
    testCorrectness(ht);
    return 0;
}
