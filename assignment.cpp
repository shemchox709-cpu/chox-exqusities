
#include <iostream>
#include <stdexcept>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;

public: CircularLinkedList() : head(nullptr) {}

    // Insert at the end
    void insertEnd(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            head->next = head;
            return;
        }
        Node* temp = head;
        while (temp->next != head) temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
    }

    // Insert at the beginning
    void insertBegin(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            head->next = head;
            return;
        }
        Node* temp = head;
        while (temp->next != head) temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
        head = newNode;
    }

    // Insert in sorted order
    void insertSorted(int value) {
        Node* newNode = new Node(value);
        if (!head) { // Empty list
            head = newNode;
            head->next = head;
            return;
        }
        if (value <= head->data) { // Insert before head
            insertBegin(value);
            return;
        }
        Node* curr = head;
        while (curr->next != head && curr->next->data < value) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }

    // Delete a node by value
    void deleteNode(int value) {
        if (!head) throw runtime_error("List is empty. Cannot delete.");

        Node* curr = head;
        Node* prev = nullptr;

        // If head node is to be deleted
        if (head->data == value) {
            if (head->next == head) { // Only one node
                delete head;
                head = nullptr;
                return;
            }
            Node* temp = head;
            while (temp->next != head) temp = temp->next;
            temp->next = head->next;
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        // Search for the node
        do {
            prev = curr;
            curr = curr->next;
            if (curr->data == value) {
                prev->next = curr->next;
                delete curr;
                return;
            }
        } while (curr != head);

        throw runtime_error("Value not found in the list.");
    }

    // Search for a value
    bool search(int value) const {
        if (!head) return false;
        Node* temp = head;
        do {
            if (temp->data == value) return true;
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    // Reverse the circular linked list
    void reverse() {
        if (!head || head->next == head) return; // Empty or single node

        Node* prev = nullptr;
        Node* curr = head;
        Node* nextNode = nullptr;
        Node* tail = head;

        // Find tail
        while (tail->next != head) tail = tail->next;

        do {
            nextNode = curr->next;
            curr->next = prev ? prev : head; // Temporarily point to prev
            prev = curr;
            curr = nextNode;
        } while (curr != head);

        head->next = prev; // Old head points to last node
        head = prev;       // New head
    }

    // Display the list
    void display() const {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(back to head)\n";
    }

    // Destructor to free memory
    ~CircularLinkedList() {
        if (!head) return;
        Node* curr = head;
        Node* nextNode;
        do {
            nextNode = curr->next;
            delete curr;
            curr = nextNode;
        } while (curr != head);
        head = nullptr;
    }
};

// Main function to test
int main() {
    CircularLinkedList cll;

    try {
        // Insert in sorted order
        cll.insertSorted(20);
        cll.insertSorted(10);
        cll.insertSorted(30);
        cll.insertSorted(25);

        cout << "List after sorted insertions: ";
        cll.display();

        // Search
        cout << "Searching for 25: " << (cll.search(25) ? "Found" : "Not Found") << "\n";
        cout << "Searching for 40: " << (cll.search(40) ? "Found" : "Not Found") << "\n";

        // Reverse
        cout << "Reversing list...\n";
        cll.reverse();
        cll.display();

        // Delete
        cout << "Deleting 20...\n";
        cll.deleteNode(20);
        cll.display();

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}


