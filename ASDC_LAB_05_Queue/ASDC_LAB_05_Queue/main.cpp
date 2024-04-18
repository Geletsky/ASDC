#include <iostream>

template<typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
struct Queue {
    Node<T>* front_ptr;
    Node<T>* rear_ptr;

    Queue() : front_ptr(nullptr), rear_ptr(nullptr) {}

    bool isEmpty() const {
        return front_ptr == nullptr;
    }

    void enqueue(const T& value) {
        Node<T>* new_node = new Node<T>(value);
        if (isEmpty()) {
            front_ptr = rear_ptr = new_node;
        }
        else {
            rear_ptr->next = new_node;
            rear_ptr = new_node;
        }
    }

    T* front() {
        if (!isEmpty()) {
            return &front_ptr->data;
        }
        else {
            return nullptr;
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            Node<T>* temp = front_ptr;
            front_ptr = front_ptr->next;
            delete temp;
            if (front_ptr == nullptr) {
                rear_ptr = nullptr;
            }
        }
    }
};

int main() {
    Queue<int> queue;

    std::cout << "Is queue empty? " << std::boolalpha << queue.isEmpty() << std::endl;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    std::cout << "Front element: " << *(queue.front()) << std::endl;

    queue.dequeue();

    std::cout << "Front element after dequeue: " << *(queue.front()) << std::endl;

    return 0;
}
