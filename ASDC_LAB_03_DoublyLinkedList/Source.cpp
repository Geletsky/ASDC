#include <iostream>

template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template<typename T>
struct LinkedList {
    Node<T>* head;
    Node<T>* tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    Node<T>* insertAfter(Node<T>* node, const T& value) {
        Node<T>* new_node = new Node<T>(value);
        if (node == nullptr) {
            if (head == nullptr) {
                head = tail = new_node;
            }
            else {
                new_node->next = head;
                head->prev = new_node;
                head = new_node;
            }
        }
        else {
            new_node->prev = node;
            new_node->next = node->next;
            if (node->next == nullptr) {
                tail = new_node;
            }
            else {
                node->next->prev = new_node;
            }
            node->next = new_node;
        }
        return new_node;
    }

    Node<T>* insertBefore(Node<T>* node, const T& value) {
        Node<T>* new_node = new Node<T>(value);
        if (node == nullptr) {
            if (tail == nullptr) {
                head = tail = new_node;
            }
            else {
                new_node->prev = tail;
                tail->next = new_node;
                tail = new_node;
            }
        }
        else {
            new_node->next = node;
            new_node->prev = node->prev;
            if (node->prev == nullptr) {
                head = new_node;
            }
            else {
                node->prev->next = new_node;
            }
            node->prev = new_node;
        }
        return new_node;
    }

    Node<T>* find(int value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void remove(Node<T>* node) {
        if (node == nullptr) return;

        if (node->prev != nullptr) {
            node->prev->next = node->next;
        }
        else {
            head = node->next;
        }

        if (node->next != nullptr) {
            node->next->prev = node->prev;
        }
        else {
            tail = node->prev;
        }

        delete node;
    }

    void assertNoCycles() {
        if (head == nullptr || tail == nullptr) {
            std::cout << "Empty list or invalid state.\n";
            return;
        }

        Node<T>* slow_ptr = head;
        Node<T>* fast_ptr = head;

        while (fast_ptr != nullptr && fast_ptr->next != nullptr) {
            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next->next;

            if (slow_ptr == fast_ptr) {
                std::cout << "Cycle detected in the list.\n";
                return;
            }
        }

        std::cout << "No cycles detected in the list.\n";
    }
};

int main() {
    LinkedList<int> list;

    Node<int>* node1 = list.insertAfter(nullptr, 1);
    Node<int>* node2 = list.insertAfter(node1, 2);
    Node<int>* node3 = list.insertBefore(node2, 3);
    Node<int>* node4 = list.insertAfter(node3, 4);

    list.assertNoCycles();

    list.remove(node3);
    list.remove(node1);

    list.assertNoCycles();

    return 0;
}
