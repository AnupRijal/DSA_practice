#include <iostream>

using namespace std;

// Node class for the doubly linked list
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

// Doubly linked list class
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // Insertion at the beginning of the doubly linked list
    void insert(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        cout << value << " inserted into the list." << endl;
    }

    // Deletion of a node from the doubly linked list
    void remove(int value) {
        Node* current = head;

        while (current != nullptr && current->data != value) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << value << " not found in the list." << endl;
            return;
        }

        if (current == head) {
            head = current->next;
        } else {
            current->prev->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
        }

        delete current;
        cout << value << " removed from the list." << endl;
    }

    // Display the doubly linked list in forward direction
    void displayForward() {
        Node* current = head;
        cout << "Doubly Linked List (Forward): ";
        while (current != nullptr) {
            cout << current->data << " <-> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

    // Display the doubly linked list in reverse direction
    void displayReverse() {
        Node* current = tail;
        cout << "Doubly Linked List (Reverse): ";
        while (current != nullptr) {
            cout << current->data << " <-> ";
            current = current->prev;
        }
        cout << "nullptr" << endl;
    }

    // Destructor to free memory
    ~DoublyLinkedList() {
        Node* current = head;
        Node* nextNode;

        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
    }
};

int main() {
    DoublyLinkedList list;

    list.insert(5);
    list.insert(10);
    list.insert(15);
    list.displayForward();
    list.displayReverse();

    list.remove(10);
    list.displayForward();

    return 0;
}
