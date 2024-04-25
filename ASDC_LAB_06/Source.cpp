#include <iostream>
#include <string>

struct Data {
    int key;
    std::string value;
};

struct Node {
    std::string key;
    Data data;
    Node* next;
};

using HashFunc = size_t(*)(const std::string&);

struct HashTable {
    Node** buckets;
    HashFunc hashFunc;
    int capacity;
};

size_t simpleHashFunc(const std::string& key) {
    if (key.empty()) return 0;
    return key[0] - 'a';
}

HashTable createHashTable(int capacity, HashFunc func) {
    HashTable table;
    table.buckets = new Node * [capacity]();
    table.hashFunc = func;
    table.capacity = capacity;
    return table;
}

void addOrUpdate(HashTable& table, const std::string& key, const Data& data) {
    size_t index = table.hashFunc(key) % table.capacity;
    Node* newNode = new Node{ key, data, nullptr };
    if (table.buckets[index] == nullptr) {
        table.buckets[index] = newNode;
    }
    else {
        Node* current = table.buckets[index];
        while (current->next != nullptr && current->key != key) {
            current = current->next;
        }
        if (current->key == key) {
            current->data = data;
            delete newNode;
        }
        else {
            current->next = newNode;
        }
    }
}

Data* find(HashTable& table, const std::string& key) {
    size_t index = table.hashFunc(key) % table.capacity;
    Node* current = table.buckets[index];
    while (current != nullptr) {
        if (current->key == key) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

void remove(HashTable& table, const std::string& key) {
    size_t index = table.hashFunc(key) % table.capacity;
    Node* current = table.buckets[index];
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                table.buckets[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void freeHashTable(HashTable& table) {
    for (int i = 0; i < table.capacity; ++i) {
        Node* current = table.buckets[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table.buckets;
}

int main() {
    HashTable table = createHashTable(15, simpleHashFunc);

    addOrUpdate(table, "apple", { 1, "Red fruit" });
    addOrUpdate(table, "banana", { 2, "Yellow fruit" });
    addOrUpdate(table, "carrot", { 3, "Orange vegetable" });
    addOrUpdate(table, "tomato", { 4, "Red vegetable" });
    addOrUpdate(table, "cucumber", { 5, "Green vegetable" });

    Data* data = find(table, "banana");
    if (data) {
        std::cout << "Data found: Key = " << data->key << ", Value = " << data->value << std::endl;
    }
    else {
        std::cout << "Data not found." << std::endl;
    }

    remove(table, "carrot");

    data = find(table, "carrot");
    if (data) {
        std::cout << "Data found: Key = " << data->key << ", Value = " << data->value << std::endl;
    }
    else {
        std::cout << "Data not found." << std::endl;
    }

    freeHashTable(table);
}
