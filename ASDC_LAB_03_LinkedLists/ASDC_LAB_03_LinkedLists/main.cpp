#include <iostream>
#include <cassert>

template<typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
struct LinkedList {
    Node<T>* first;
    Node<T>* last;
    size_t size;

    LinkedList() : first(nullptr), last(nullptr), size(0) {}

    Node<T>* insertAfter(Node<T>* node, const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!node) {
            newNode->next = first;
            first = newNode;
            if (!last) last = newNode;
        }
        else {
            newNode->next = node->next;
            node->next = newNode;
            if (node == last) last = newNode;
        }
        size++;
        return newNode;
    }

    struct FindNodeResult {
        Node<T>* current;
        Node<T>* previous;
    };

    FindNodeResult find(const T& value) {
        FindNodeResult result;
        result.current = first;
        result.previous = nullptr;
        while (result.current && result.current->data != value) {
            result.previous = result.current;
            result.current = result.current->next;
        }
        return result;
    }

    void removeAfter(Node<T>* node) {
        if (!node) {
            if (!first) return; 
            Node<T>* temp = first;
            first = first->next;
            delete temp;
            if (!first) last = nullptr;
        }
        else {
            if (!node->next) return;
            Node<T>* temp = node->next;
            node->next = temp->next;
            delete temp;
            if (!node->next) last = node;
        }
        size--;
    }

    void assertNoCycles() {
        size_t count = 0;
        Node<T>* current = first;
        while (current) {
            count++;
            if (count > size) {
                std::cerr << "Error: Cycle detected in the linked list!" << std::endl;
                assert(false);
            }
            current = current->next;
        }
    }

    ~LinkedList() {
        while (first) {
            Node<T>* temp = first;
            first = first->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList<int> list;
    list.insertAfter(nullptr, 1);
    list.insertAfter(nullptr, 2);
    list.insertAfter(nullptr, 3);

    LinkedList<int>::FindNodeResult result = list.find(2);
    if (result.current) {
        std::cout << "Found: " << result.current->data << std::endl;
        list.removeAfter(result.previous);
    }

    list.assertNoCycles();

    return 0;
}
