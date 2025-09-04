#include <iostream>
using namespace std;

// Node class for singly linked list
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    
    // Constructor
    Node(T value) : data(value), next(nullptr) {}
};

// Singly Linked List class
template <typename T>
class SinglyLinkedList {
private:
    Node<T>* head;
    int size;

public:
    // Constructor
    SinglyLinkedList() : head(nullptr), size(0) {}
    
    // Destructor to free memory
    ~SinglyLinkedList() {
        clear();
    }
    
    // Check if list is empty
    bool isEmpty() const {
        return head == nullptr;
    }
    
    // Get size of list
    int getSize() const {
        return size;
    }
    
    // Insert at beginning
    void insertAtBeginning(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    // Insert at end
    void insertAtEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (isEmpty()) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    
    // Insert at specific position (0-indexed)
    void insertAtPosition(T value, int position) {
        if (position < 0 || position > size) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if (position == 0) {
            insertAtBeginning(value);
            return;
        }
        
        Node<T>* newNode = new Node<T>(value);
        Node<T>* current = head;
        
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
    
    // Delete from beginning
    void deleteFromBeginning() {
        if (isEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }
        
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
    
    // Delete from end
    void deleteFromEnd() {
        if (isEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }
        
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* current = head;
            while (current->next->next != nullptr) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        size--;
    }
    
    // Delete from specific position (0-indexed)
    void deleteFromPosition(int position) {
        if (isEmpty() || position < 0 || position >= size) {
            cout << "Invalid position or list is empty!" << endl;
            return;
        }
        
        if (position == 0) {
            deleteFromBeginning();
            return;
        }
        
        Node<T>* current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        
        Node<T>* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
    }
    
    // Search for a value
    bool search(T value) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // Get value at specific position (0-indexed)
    T getAtPosition(int position) const {
        if (isEmpty() || position < 0 || position >= size) {
            throw out_of_range("Invalid position!");
        }
        
        Node<T>* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    // Reverse the linked list
    void reverse() {
        if (isEmpty() || head->next == nullptr) {
            return; // Already reversed or single element
        }
        
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;
        
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        head = prev;
    }
    
    // Display the linked list
    void display() const {
        if (isEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }
        
        Node<T>* current = head;
        cout << "Linked List: ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }
    
    // Clear the entire list
    void clear() {
        while (!isEmpty()) {
            deleteFromBeginning();
        }
    }
    
    // Check if list has cycle (Floyd's Cycle Finding Algorithm)
    bool hasCycle() const {
        if (isEmpty() || head->next == nullptr) {
            return false;
        }
        
        Node<T>* slow = head;
        Node<T>* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }
};

// Main function to demonstrate the linked list
int main() {
    cout << "=== Singly Linked List Implementation ===" << endl << endl;
    
    // Create a linked list of integers
    SinglyLinkedList<int> list;
    
    cout << "1. Inserting elements..." << endl;
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtBeginning(5);
    list.insertAtPosition(15, 2);
    
    list.display();
    cout << "Size: " << list.getSize() << endl << endl;
    
    cout << "2. Searching for elements..." << endl;
    cout << "Search for 15: " << (list.search(15) ? "Found" : "Not found") << endl;
    cout << "Search for 25: " << (list.search(25) ? "Found" : "Not found") << endl << endl;
    
    cout << "3. Getting element at position 2: " << list.getAtPosition(2) << endl << endl;
    
    cout << "4. Deleting elements..." << endl;
    list.deleteFromBeginning();
    list.display();
    cout << "Size: " << list.getSize() << endl;
    
    list.deleteFromEnd();
    list.display();
    cout << "Size: " << list.getSize() << endl;
    
    list.deleteFromPosition(1);
    list.display();
    cout << "Size: " << list.getSize() << endl << endl;
    
    cout << "5. Reversing the list..." << endl;
    list.insertAtEnd(40);
    list.insertAtEnd(50);
    list.display();
    
    list.reverse();
    list.display() << endl;
    
    cout << "6. Creating a string linked list..." << endl;
    SinglyLinkedList<string> stringList;
    stringList.insertAtEnd("Hello");
    stringList.insertAtEnd("World");
    stringList.insertAtEnd("C++");
    stringList.display();
    cout << "Size: " << stringList.getSize() << endl << endl;
    
    cout << "7. Cycle detection test..." << endl;
    cout << "Has cycle: " << (list.hasCycle() ? "Yes" : "No") << endl;
    
    return 0;
}
