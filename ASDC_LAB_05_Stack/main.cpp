#include <iostream>

template<typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
struct Stack {
    Node<T>* top;

    Stack() : top(nullptr) {}

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(const T& value) {
        Node<T>* new_node = new Node<T>(value);
        new_node->next = top;
        top = new_node;
    }

    T* getLastElement() {
        if (!isEmpty()) {
            return &top->data;
        }
        else {
            return nullptr;
        }
    }

    void pop() {
        if (!isEmpty()) {
            Node<T>* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

int main() {
    Stack<int> stack;

    std::cout << "Is stack empty? " << std::boolalpha << stack.isEmpty() << std::endl;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << "Top element: " << *(stack.getLastElement()) << std::endl;

    stack.pop();

    std::cout << "Top element after pop: " << *(stack.getLastElement()) << std::endl;

    return 0;
}
