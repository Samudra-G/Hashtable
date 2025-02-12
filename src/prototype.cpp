#include <iostream>

#define TABLE_SIZE 11
class Node{
    public:
        int key;
        int value;
        Node* next;

        Node(int k, int v) : key(k), value(v), next(nullptr){} 

};

class LinkedList{
    private:
        Node* head;
    
    public:
        LinkedList() : head(nullptr){}
        ~LinkedList() {
            //Destructor will delete all current nodes
            Node* current = head;
            while(current){
                Node* newNode = current->next;
                delete current;
                current = newNode;
            }
        }
        //helper functions
        Node* getHead(){
            return head;
        }
        void removeHead(){
            Node* tempNode = head;
            head = head->next;
            delete tempNode;
        }
        void removeafterHead(Node* prevNode){
            Node* tempNode = prevNode->next;
            prevNode->next = prevNode->next->next;
            tempNode->next = nullptr; //ensures deleted node cannot be accessed again
            delete tempNode;
        }

        //Implement the method
        void insert(int key, int value){
            Node* newNode = new Node(key, value);

            if(!newNode){ // ensures the head doesn't point to nullptr
                std::cout << "Memory allocation failed." << std::endl;
            }
            newNode->next = head;
            head = newNode;
        }
        void remove(int searchKey){

            if(!head){
                std::cout << "Table is empty." << std::endl;
                return ;
            }
            if(head->key == searchKey){
                removeHead();
                return ;
            }

            Node* temp = head;

            while(temp && temp->next){
                if(temp->next->key == searchKey){
                    removeafterHead(temp);
                    return;
                }
                else
                    temp = temp->next;
            }
            std::cout << "Key not found." << std::endl;
        }
        bool search(int searchKey){
            if(!head)
                return false;
            
            Node* temp = head;
            while(temp){
                if(temp->key == searchKey){
                    return true;
                }
                else    
                    temp = temp->next;
            }

            return false;
        }
};

class HashTable{
    private:
        LinkedList** table;
        int size; // size of the table
        int count;// counts no.of key: value pairs
        //Later used for load factor = size/count

    public: 
        //Initialize a hash table with nullptr
        HashTable(): size(TABLE_SIZE), count(0) {
            table = new LinkedList*[size];
            for(int i{0}; i < size; i++){
                table[i] = nullptr;
            }
        }
        ~HashTable() {
            for (int i = 0; i < size; i++) {
                delete table[i]; // Free each linked list
            }
            delete[] table;
        }

        // Hash function
        int hashFunction(int key){
            int hashValue = key % size;

            return hashValue;
        }
        // Rehash
        void rehash(LinkedList* newTable[], int newSize){
            //loop through prev table
            for(int i{0}; i < size; i++){
                if(table[i] != nullptr){ //check if the index is not empty
                    Node* temp = table[i]->getHead(); //fetch the head 
                    while(temp){
                        int newIndex = (temp->key) % newSize; //recalculate hash
                        if(newTable[newIndex] == nullptr)
                            newTable[newIndex] = new LinkedList(); //create new LL if empty

                        newTable[newIndex]-> insert(temp->key, temp->value); //repopulate new table
                        temp = temp->next;
                    }
                }
            }
        }
        // Resize
        void resize(){
            int newSize = size * 2;
            LinkedList** newTable = new LinkedList*[newSize];

            for(int i{0}; i < newSize; i++){
                newTable[i] = nullptr;
            }

            rehash(newTable, newSize);

            for(int i{0}; i < size; i++){
                delete table[i];
            }
            delete[] table;
            table = newTable;
            size = newSize;
        }
        // Insert method
        void insert(int key, int value){
            //Calculate load factor
            double loadFactor = static_cast<double>(count)/size;

            if(loadFactor > 0.75){
                resize();
            }
            int index = hashFunction(key);
            if(table[index] == nullptr)//check if the index is empty
                table[index] = new LinkedList();
            
            if(table[index]-> search(key))
                table[index]->remove(key); //check to overwrite duplicates
            
            table[index]-> insert(key,value);
            count++;

        }
        // Search method
        bool search(int key){
            int index = hashFunction(key);
            if(table[index] == nullptr)//check if it is a valid index
                return false;
            
            return table[index]-> search(key);//return the result of linkedlist search 
        }
        // Remove method
        void remove(int key){
            int index = hashFunction(key);
            if(table[index] == nullptr)
                return;
            
            if(table[index]-> search(key)){
                table[index]-> remove(key);
                count--;
            }
        }
};

int main(int argc, char *argv[]){
    //driver code
    HashTable ht;
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