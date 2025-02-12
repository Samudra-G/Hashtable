#include "../src/hashtable.h"
#include <iostream>
#include <unordered_map>
#include <cmath>

void testDistribution(HashTable &ht, int numKeys){
    std::unordered_map<int, int> bucketCounts; //counts the recurring elements in original table
    int tableSize = ht.getSize();

    for(int i{0}; i < numKeys; i++){
        int index = ht.getHash(i);
        bucketCounts[index]++;
    }

    double mean = numKeys / (double)tableSize;

    double variance = 0.0;

    for(auto pair: bucketCounts){
        variance += pow(pair.second - mean, 2)/tableSize;
    }
    double stdDeviation = sqrt(variance);

    for(auto pair: bucketCounts){
        std::cout << "Bucket: " << pair.first << " has elements: " << pair.second << std::endl;
    }
    std::cout << "Mean elements per bucket: " << variance << std::endl;
    std::cout << "Standard deviation: " << stdDeviation << std::endl;
}

int main() {
    HashTable ht;
    for (int i = 0; i < 1000; i++) {
        ht.insert(i, i * 10);
    }

    testDistribution(ht, 1000);
    return 0;
}