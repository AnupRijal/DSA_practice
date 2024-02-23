/**
 * @file Doubly_Linked_list.cpp
 * @brief Declaration of the DoublyLinked class and Node struct.
 * @author Anup Rijal
 */
#ifndef DOUBLY_LINKED_H
#define DOUBLY_LINKED_H

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/**
 * @brief Node struct for the elements of the doubly linked list.
 * @tparam T The type of data stored in the node.
 */
template <typename T>
struct Node {
    Node *prev;
    T data;
    Node *next;
};

/**
 * @brief DoublyLinked class representing a doubly linked list.
 * @tparam T The type of data stored in the list.
 */
template <typename T>
class DoublyLinked {
private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    int count = 0;

    Node<T>* createNewNode(T d);
    bool deleteAfter(Node<T> *prevNode);
    void insert_After(Node<T> *prevNode, T value);

public:
    //Copy constructor and destructor 
    DoublyLinked();
    ~DoublyLinked();

    //Copy constructor 
    DoublyLinked(const DoublyLinked &);

    //List manipulation function 
    void push_front(T value);
    bool insert(int index, T value);
    void push_back(T value);
    bool pop_front(T &data);
    bool pop_back(T &data);
    bool deleteNode(int index);
    bool elementAt(int index, T &value);
    void displayList();
    int size();
    bool isEmpty();
    bool reverseList();
    void deleteItem(T value);
    vector<Node<T>*> searchItems(T value);
};

/**
 * @brief Constructor for DoublyLinked class.
 * Initializes head, tail, and count.
 * 
 * @tparam T The type of data stored in the list.
 */
template <typename T>
DoublyLinked<T>::DoublyLinked() {
    head = nullptr;
    tail = nullptr;
}

/**
 * @brief Creates a new Node with the provided data.
 * 
 * @tparam T The type of data stored in the node.
 * @param d Data for the new node.
 * @return Node<T>* A pointer to the new node.
 */
template <typename T>
Node<T>* DoublyLinked<T>::createNewNode(T d) {
    Node<T> *newNode = new Node<T>;
    if (newNode == nullptr) {
        throw std::bad_alloc();
    }
    newNode->prev = nullptr;
    newNode->data = d;
    newNode->next = nullptr;
    return newNode;
}

/**
 * @brief Deletes the node after the provided previous node.
 * 
 * @tparam T The type of data stored in the list.
 * @param prevNode The previous node.
 * @return bool True if the deletion is successful, false otherwise.
 */
template <typename T>
bool DoublyLinked<T>::deleteAfter(Node<T> *prevNode) {
    if (prevNode == nullptr)
        return false;

    Node<T> *nodeDelete = prevNode->next;
    if (nodeDelete == nullptr)
        return false;

    prevNode->next = nodeDelete->next;
    if (nodeDelete->next != nullptr)
        nodeDelete->next->prev = prevNode;

    delete nodeDelete;
    count--;
    return true;
}

/**
 * @brief Inserts a new node with the provided value after the given previous node.
 * 
 * @tparam T The type of data stored in the list.
 * @param prevNode The previous node.
 * @param value The value to be inserted.
 */
template <typename T>
void DoublyLinked<T>::insert_After(Node<T> *prevNode, T value) {
    if (prevNode == nullptr) {
        throw std::invalid_argument("Previous node is required, it cannot be NULL");
    }

    Node<T> *nextNode = prevNode->next;
    Node<T>* newNode = createNewNode(value);

    newNode->next = nextNode;
    prevNode->next = newNode;
    newNode->prev = prevNode;

    if (nextNode != nullptr)
        nextNode->prev = newNode;

    count++;
}

/**
 * @brief Destructor for DoublyLinked class.
 * Deletes all nodes in the list and sets head, tail, and count to nullptr.
 * 
 * @tparam T The type of data stored in the list.
 */
template <typename T>
DoublyLinked<T>::~DoublyLinked() {
    Node<T> *currentPtr = head;
    Node<T> *tempPtr = nullptr;
    while (currentPtr != nullptr) {
        tempPtr = currentPtr->next;
        delete currentPtr;
        currentPtr = tempPtr;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

/**
 * @brief Copy constructor for DoublyLinked class.
 * Creates a deep copy of the provided list.
 * 
 * @tparam T The type of data stored in the list.
 * @param copyy The list to be copied.
 */
template <typename T>
DoublyLinked<T>::DoublyLinked(const DoublyLinked &copyy) {
    head = nullptr;
    tail = nullptr;
    count = 0;

    Node<T> *current = copyy.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

/**
 * @brief Adds a new node with the provided value to the front of the list.
 * 
 * @tparam T The type of data stored in the list.
 * @param value The value to be added.
 */
template <typename T>
void DoublyLinked<T>::push_front(T value) {
    Node<T>* newNode = createNewNode(value);

    if (head != nullptr) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else {
        head = newNode;
        tail = newNode;
    }

    count++;
}

/**
 * @brief Inserts a new node with the provided value at the specified index.
 * 
 * @tparam T The type of data stored in the list.
 * @param index The index at which the value should be inserted.
 * @param value The value to be inserted.
 * @return bool True if insertion is successful, false otherwise.
 */
template <typename T>
bool DoublyLinked<T>::insert(int index, T value) {
    if (index < 0 || index > count)
        return false;

    if (index == 0) {
        push_front(value);
    } else if (index == count) {
        push_back(value);
    } else {
        Node<T> *current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        insert_After(current, value);
    }

    return true;
}

/**
 * @brief Adds a new node with the provided value to the end of the list.
 * 
 * @tparam T The type of data stored in the list.
 * @param value The value to be added.
 */
template <typename T>
void DoublyLinked<T>::push_back(T value) {
    Node<T>* newNode = createNewNode(value);

    if (tail != nullptr) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        head = newNode;
        tail = newNode;
    }

    count++;
}

/**
 * @brief Removes and returns the value of the first node in the list.
 * 
 * @tparam T The type of data stored in the list.
 * @param data Reference to store the retrieved data.
 * @return bool True if successful, false otherwise.
 */
template <typename T>
bool DoublyLinked<T>::pop_front(T &data) {
    if (count == 0 || head == nullptr)
        return false;

    data = head->data;
    if (head->next == nullptr) {
        delete head;
        tail = nullptr;
        head = nullptr;
        count = 0;
    } else {
        Node<T> *prevHead = head;
        head = head->next;
        head->prev = nullptr;
        delete prevHead;
        count--;
    }

    return true;
}

/**
 * @brief Removes and returns the value of the last node in the list.
 * 
 * @tparam T The type of data stored in the list.
 * @param data Reference to store the retrieved data.
 * @return bool True if successful, false otherwise.
 */
template <typename T>
bool DoublyLinked<T>::pop_back(T &data) {
    if (count == 0 || tail == nullptr)
        return false;

    data = tail->data;
    if (head->next == nullptr) {
        delete head;
        tail = nullptr;
        head = nullptr;
        count = 0;
    } else {
        Node<T> *prevTail = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete prevTail;
        count--;
    }

    return true;
}

/**
 * @brief Deletes the node at the specified index.
 * 
 * @tparam T The type of data stored in the list.
 * @param index The index of the node to be deleted.
 * @return bool True if deletion is successful, false otherwise.
 */
template <typename T>
bool DoublyLinked<T>::deleteNode(int index) {
    if (index < 0 || index >= count || head == nullptr)
        return false;

    if (index == 0 || index < count / 2) {
        Node<T>* current = head;

        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }

        return deleteAfter(current);
    } else {
        Node<T>* current = tail;

        for (int i = count - 1; i > index; --i) {
            current = current->prev;
        }

        return deleteAfter(current->prev);
    }
}

/**
 * @brief Retrieves the value at the specified index.
 * 
 * @tparam T The type of data stored in the list.
 * @param index The index of the value to be retrieved.
 * @param value Reference to store the retrieved value.
 * @return bool True if successful, false otherwise.
 */
template <typename T>
bool DoublyLinked<T>::elementAt(int index, T &value) {
    if (index >= count || index < 0)
        return false;

    Node<T> *current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    value = current->data;
    return true;
}

/**
 * @brief Displays the elements of the list.
 * 
 * @tparam T The type of data stored in the list.
 */
template <typename T>
void DoublyLinked<T>::displayList() {
    Node<T>* node = head;
    while (node != nullptr) {
        cout << node->data << "<==>";
        node = node->next;
    }
    if (node == nullptr)
        cout << "BEGIN";
}

/**
 * @brief Returns the size of the list.
 * 
 * @tparam T The type of data stored in the list.
 * @return int The size of the list.
 */
template <typename T>
int DoublyLinked<T>::size() {
    Node<T>* currentNode = head;
    int size = 0;
    while (currentNode != nullptr) {
        size++;
        currentNode = currentNode->next;
    }
    return size;
}

/**
 * @brief Checks if the list is empty.
 * 
 * @tparam T The type of data stored in the list.
 * @return bool True if the list is empty, false otherwise.
 */
template <typename T>
bool DoublyLinked<T>::isEmpty() {
    return head == nullptr;
}

/**
 * @brief Reverses the order of elements in the list.
 * 
 * @tparam T The type of data stored in the list.
 * @return bool True if successful, false otherwise.
 */
template <typename T>
bool DoublyLinked<T>::reverseList() {
    if (count == 0 || head == nullptr)
        return false;

    Node<T> *front = head;
    Node<T> *back = tail;

    for (int i = 0; i < count / 2; i++) {
        T temp = front->data;
        front->data = back->data;
        back->data = temp;

        front = front->next;
        back = back->prev;
    }

    return true;
}

/**
 * @brief Deletes all nodes with the specified value.
 * 
 * @tparam T The type of data stored in the list.
 * @param value The value to be deleted.
 */
template <typename T>
void DoublyLinked<T>::deleteItem(T value) {
    Node<T> *current = head;
    Node<T> *temp = nullptr;
    Node<T> *prevNode = nullptr;

    while (current != nullptr) {
        if (current->data == value) {
            if (prevNode == nullptr) {
                temp = current->next;
                delete current;
                current = temp;
                if (current != nullptr) {
                    current->prev = nullptr;
                }
            } else {
                prevNode->next = current->next;
                delete current;
                current = prevNode->next;
                if (current != nullptr) {
                    current->prev = prevNode;
                }
            }
        } else {
            prevNode = current;
            current = current->next;
        }
    }
}

/**
 * @brief Searches for nodes with the specified value.
 * 
 * @tparam T The type of data stored in the list.
 * @param value The value to be searched for.
 * @return vector<Node<T>*> A vector of pointers to nodes containing the specified value.
 */
template <typename T>
vector<Node<T>*> DoublyLinked<T>::searchItems(T value) {
    vector<Node<T>*> nodes;
    Node<T> *current = head;

    while (current != nullptr) {
        if (current->data == value) {
            nodes.push_back(current);
        }
        current = current->next;
    }

    return nodes;
}

#endif

// Class representing a Student
class Student {
private:
    std::string name;
    float gpa;
    std::string address;

public:
    Student();
    Student(std::string n, float g, std::string a);
    Student(const Student &copyy);
    std::string to_string() const;
    bool operator==(const Student&) const;
    friend std::ostream &operator<<(std::ostream &oo, const Student &student);
};

// Overloading the << operator for easy printing of Student objects
std::ostream &operator<<(std::ostream &oo, const Student &student) {
    oo << student.to_string();
    return oo;
}

// Default constructor for Student
Student::Student() : name(""), gpa(0.0), address("") {}

// Parameterized constructor for Student
Student::Student(std::string n, float g, std::string a) : name(n), gpa(g), address(a) {}

// Copy constructor for Student
Student::Student(const Student &copyy) : name(copyy.name), gpa(copyy.gpa), address(copyy.address) {}

// Converts Student object to a string
std::string Student::to_string() const {
    return "\nname: " + name + ", gpa: (" + std::to_string(gpa) + "), address: " + address;
}

// Overloading the == operator for Student
bool Student::operator==(const Student &copyy) const {
    return (name == copyy.name && gpa == copyy.gpa && address == copyy.address);
}

// Main function
int main() {
    //Creating a doubly linked list of Students 
    DoublyLinked<Student> studVector;
    //Adding students to the list 
    Student student1("student1", 4.0, "address1");
    studVector.push_back(student1);
    //Likewise for other students 
    Student student2("student2", 4.0, "address2");
    studVector.push_back(student2);
    Student student3("student3", 4.0, "address3");
    studVector.push_back(student3);
    Student student4("student4", 4.0, "address4");
    studVector.push_back(student4);
    Student student5("student5", 4.0, "address5");
    studVector.push_back(student5);
    Student student6("student6", 4.0, "address6");
    studVector.push_back(student6);
    Student student7("student7", 4.0, "address7");
    studVector.push_back(student7);
    Student student8("student8", 4.0, "address8");
    studVector.push_back(student8);
    Student student9("student9", 4.0, "address9");
    studVector.push_back(student9);
    Student student10("student10", 4.0, "address10");
    studVector.push_back(student10);
    studVector.displayList();
    cout << endl;

    //Creating a copy of the list using the copy constructor 
    DoublyLinked<Student> cpStudVector = studVector;
    cpStudVector.displayList();
    cout << endl << endl;

    //Reversing the original list 
    studVector.reverseList();
    studVector.displayList();
    cout << endl << endl;

    //Searching for students with a specific value and printing them 
    Student stObj("student5", 4.0, "address5");
    vector<Node<Student>*> nodes = studVector.searchItems(stObj);

    for (const auto& node : nodes) {
        cout << node->data << " ";
    }
    cout << endl << endl;

    //Deleting a note at a specific index and displaying the updated list
    studVector.deleteNode(7);
    studVector.displayList();

    return 0;
}
