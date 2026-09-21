#include <iostream>
#include <stdexcept>
#include <string>
#include <Windows.h>

using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;

        Node(int value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (!isEmpty()) {
            removeFirst();
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void append(int value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void prepend(int value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void remove(int value) {
        Node* current = head;

        while (current != nullptr && current->data != value) {
            current = current->next;
        }

        if (current == nullptr) {
            throw runtime_error("Element not found: " + to_string(value));
        }

        if (current == head) {
            removeFirst();
            return;
        }

        if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
    }

    void removeFirst() {
        if (isEmpty()) {
            throw runtime_error("List is empty");
        }

        Node* temp = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }

        delete temp;
    }

    void printList() const {
        Node* current = head;

        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }
};

int main() 
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    cout << "======= Try Catch(робота з виключеннями) =======\n";
    DoublyLinkedList list;

    try {
        list.append(10);
        list.append(20);
        list.prepend(5);
        list.printList(); 

        list.remove(10);
        list.printList(); 

        list.remove(30);
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    try {
        while (!list.isEmpty()) {
            list.removeFirst(); 
        }

        list.remove(5);
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}