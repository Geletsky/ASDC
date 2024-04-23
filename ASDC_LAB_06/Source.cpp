#include <assert.h>
#include <string>
#include <iostream> 
#include <string_view>

struct Struct {
    std::string name;
    int age;

    void printInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

struct BucketNode {
    std::string key;
    Struct data;
    BucketNode* next;
};

using HashFunc = size_t(*)(std::string_view key);

struct AssociativeArray {
    BucketNode** buckets;
    HashFunc hashFunc;
    int capacity;
    int countOfBucketNodes;
};

struct AddOrGetElemResult {
    Struct* data;
    bool added;
};

size_t calculateKeyIndex(AssociativeArray* arr, std::string_view key) {
    size_t hash = arr->hashFunc(key);
    size_t index = hash % arr->capacity;
    return index;
}

AddOrGetElemResult modifyOrFetchElem(AssociativeArray* arr, std::string_view key) {
    size_t index = calculateKeyIndex(arr, key);
    BucketNode** curNode = &arr->buckets[index];
    while (true) {
        if ((*curNode) == nullptr) {
            BucketNode* node = new BucketNode;
            node->key = key;
            node->next = nullptr;
            *curNode = node;
            arr->countOfBucketNodes++;

            return { &node->data, true };
        }
        else if ((*curNode)->key == key) {
            Struct* dataAddress = &(*curNode)->data;
            arr->countOfBucketNodes++;
            return { dataAddress,false };
        }
        else curNode = &(*curNode)->next;
    }
}

Struct* findElem(AssociativeArray* arr, std::string_view key) {
    size_t index = calculateKeyIndex(arr, key);
    BucketNode* curNode = arr->buckets[index];
    while (curNode != nullptr) {
        if (curNode->key == key) return &curNode->data;
        curNode = curNode->next;
    }
    return nullptr;
}

size_t simpleHashFunc(std::string_view key) {
    if (key.empty()) return 0;
    uint8_t firstLetter = key[0];
    uint8_t positionInAlphabet = firstLetter - static_cast<uint8_t>('a');
    return static_cast<size_t>(positionInAlphabet);
}

AssociativeArray establishHashTable(int capacity, HashFunc func) {
    AssociativeArray arr;
    arr.buckets = new BucketNode * [capacity];
    for (int i = 0; i < capacity; i++) arr.buckets[i] = nullptr;
    arr.hashFunc = func;
    arr.capacity = capacity;
    arr.countOfBucketNodes = 0;
    return arr;
}

bool eradicateNodeByKey(AssociativeArray* arr, std::string_view key) {
    size_t index = calculateKeyIndex(arr, key);
    BucketNode** tempNodeForRemoval = &arr->buckets[index];
    while (*tempNodeForRemoval != nullptr) {
        if ((*tempNodeForRemoval)->key == key) {
            BucketNode* temp = *tempNodeForRemoval;
            *tempNodeForRemoval = (*tempNodeForRemoval)->next;
            delete temp;
            return true;
        }
        tempNodeForRemoval = &(*tempNodeForRemoval)->next;
    }
    return false;
}

void freeAssociativeArray(AssociativeArray* arr) {
    assert(arr);
    if (arr->countOfBucketNodes == 0 || arr->buckets == nullptr) return;
    for (int i = 0; i < arr->capacity; ++i) {
        BucketNode* curNode = arr->buckets[i];
        while (curNode != nullptr) {
            BucketNode* nodeToDelete = curNode;
            curNode = curNode->next;
            delete nodeToDelete;
        }
    }
    delete[] arr->buckets;
    arr->buckets = nullptr;
}

int main() {
    AssociativeArray arr = establishHashTable(15, simpleHashFunc);
    {
        AddOrGetElemResult result = modifyOrFetchElem(&arr, "alex");
        assert(result.added == true);
        result.data->name = "Alex Johnson";
        result.data->age = 28;
    }
    {
        AddOrGetElemResult result = modifyOrFetchElem(&arr, "sophia");
        assert(result.added == true);
        result.data->name = "Sophia Brown";
        result.data->age = 32;
    }
    {
        AddOrGetElemResult result = modifyOrFetchElem(&arr, "michael");
        assert(result.added == true);
        result.data->name = "Michael Davis";
        result.data->age = 37;
    }
    {
        AddOrGetElemResult result = modifyOrFetchElem(&arr, "emma");
        assert(result.added == true);
        result.data->name = "Emma Garcia";
        result.data->age = 41;
    }
    {
        AddOrGetElemResult result = modifyOrFetchElem(&arr, "william");
        assert(result.added == true);
        result.data->name = "William Martinez";
        result.data->age = 46;
    }
    {
        Struct* data = findElem(&arr, "alex");
        assert(data != nullptr);
        data->printInfo();
        eradicateNodeByKey(&arr, "emma");
    }
    freeAssociativeArray(&arr);
    return 0;
}
