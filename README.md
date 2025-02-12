# Hash Table Implementation in C++

## **Overview**
This project implements a **Hash Table** in C++ with **separate chaining** for collision handling. It features **dynamic resizing and rehashing** based on the load factor and supports performance testing. The hash function utilizes **multiplicative hashing**, ensuring even distribution.

## **Features**
- **Dynamic Resizing & Rehashing**: Automatically increases the table size when the load factor is exceeded.
- **Multiplicative Hashing**: Ensures better key distribution, reducing collisions.
- **Separate Chaining**: Uses linked lists to handle collisions efficiently.
- **Performance Benchmarking**: Measures time taken for insertion and tracks collisions.
- **Statistical Distribution Analysis**: Computes mean and standard deviation of elements per bucket.

## **Implementation Details**

### **Hash Function (Multiplicative Hashing)**
```cpp
size_t hashFunction(int key, size_t tableSize) {
    const double A = 0.6180339887; // Fractional part of the golden ratio
    return (size_t)(tableSize * (key * A - (int)(key * A))) % tableSize;
}
```

### **Collision Handling**
- **Separate Chaining with Linked Lists**
- Each bucket stores a linked list of key-value pairs.

### **Dynamic Resizing & Rehashing**
- The table resizes when the **load factor exceeds 0.75**.
- New size is **doubled**, and all elements are **rehashed**.

## **Performance Testing**
### **Test Code for Performance Analysis**
```cpp
void testPerformance(HashTable &ht, int numKeys) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numKeys; i++) {
        ht.insert(i, i * 10);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to insert " << numKeys << " elements: " << duration.count() << " seconds\n";
}
```

### **Test Code for Collision Counting**
```cpp
int countCollisions(HashTable& ht) {
    int collisionCount {0};
    LinkedList** table = ht.getTable();
    for (int i {0}; i < ht.getSize(); i++) {
        if (table[i] != nullptr) {
            Node* head = table[i]->getHead();
            int chainLength {0};
            while (head) {
                chainLength++;
                head = head->next;
            }
            if (chainLength > 1) collisionCount += (chainLength - 1);
        }
    }
    return collisionCount;
}
```

## **Benchmark Results**
```
Time taken to insert 10,000 elements: 0.015619 seconds
Total number of collisions: 581
Table size after resizing: 22,528
Mean elements per bucket: 0.0638853
Standard deviation: 0.252755
```

### **Observations:**
- The **multiplicative hash function** significantly reduces clustering.
- The **dynamic resizing mechanism** ensures performance efficiency.
- The **collision rate remains low**, demonstrating effective hashing.

## **Future Improvements**
- Implementing **Open Addressing** as an alternative to Separate Chaining.
- Exploring **alternative hash functions** (e.g., MurmurHash, FNV-1a).
- Adding **thread safety** for concurrent operations.

## **Conclusion**
This hash table implementation is **efficient, scalable, and optimized for minimal collisions**. The performance tests validate its robustness, making it suitable for high-performance applications.

