#include <iostream>
#include "hashtable.h"

int main(){
    //driver code
    HashTable ht;
    std::cout << "Table size pre-rehashing: " << TABLE_SIZE << std::endl;
    //test 1
    ht.insert(10, 100);
    ht.insert(20, 200);
    ht.insert(30, 300);
    ht.insert(40, 400);
    std::cout << ht.search(10) << "\n"; // Expected: 1 (true)
    std::cout << ht.search(20) << "\n"; // Expected: 1 (true)
    std::cout << ht.search(50) << "\n"; // Expected: 0 (false)

    //test 2
    ht.insert(10, 500);
    std::cout << ht.search(10) << "\n"; // Expected: 1 (true)

    //test 3
    ht.remove(20);
    std::cout << ht.search(20) << "\n"; // Expected: 0 (false)

    //test 4
    ht.remove(99); // Should not crash or change count
    std::cout << ht.search(99) << "\n"; // Expected: 0 (false)

    //test 5
    ht.remove(10);
    ht.remove(30);
    ht.remove(40);
    std::cout << ht.search(10) << "\n"; // Expected: 0 (false)
    std::cout << ht.search(30) << "\n"; // Expected: 0 (false)
    std::cout << ht.search(40) << "\n"; // Expected: 0 (false)

    //test 6: insert till rehashing is triggered
    for (int i = 0; i < 10; i++) {
        ht.insert(i, i * 100);
    }
    std::cout << ht.search(5) << "\n"; // Expected: 1 (true)
    std::cout << ht.search(9) << "\n"; // Expected: 1 (true)
    
    std::cout << "Table size post-rehashing: " << ht.getSize() << std::endl;
    //test 7
    HashTable emptyHT;
    std::cout << emptyHT.search(1) << "\n"; // Expected: 0 (false)

    //test 8
    emptyHT.remove(1); // Should not crash

    //test 9
    for (int i = 1; i <= 100; i++) {
        ht.insert(i, i * 10);
    }
    for (int i = 1; i <= 100; i++) {
        std::cout << ht.search(i) << " "; // Expected: All 1s (true)
    }
    std::cout << "\n";

    return 0;
}