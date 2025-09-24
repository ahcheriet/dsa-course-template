#include <iostream>
#include <stdexcept>

/**
 * Singly Linked List Implementation
 * Each node contains data and a pointer to the next node
 */

// Node structure for singly linked list
struct Node {
    int data;
    Node* next;
    
    Node(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
    int listSize;

public:
    /**
     * Constructor - Initialize empty list
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    SinglyLinkedList() : head(nullptr), listSize(0) {}

    /**
     * Destructor - Clean up all nodes
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    ~SinglyLinkedList() {
        clear();
    }

    /**
     * Insert element at the beginning of the list
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void insert(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        listSize++;
    }

    /**
     * Insert element at specific position (0-indexed)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void insertAt(int index, int data) {
        if (index < 0 || index > listSize) {
            throw std::out_of_range("Index out of bounds");
        }

        if (index == 0) {
            insert(data);
            return;
        }

        Node* newNode = new Node(data);
        Node* current = head;
        
        // Traverse to position index-1
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        listSize++;
    }

    /**
     * Insert element at the end of the list
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void append(int data) {
        if (head == nullptr) {
            insert(data);
            return;
        }

        Node* newNode = new Node(data);
        Node* current = head;
        
        // Traverse to the last node
        while (current->next != nullptr) {
            current = current->next;
        }
        
        current->next = newNode;
        listSize++;
    }

    /**
     * Delete first occurrence of element
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool deleteElement(int data) {
        if (head == nullptr) {
            return false;
        }

        // If head node contains the data
        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            listSize--;
            return true;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->data != data) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node* nodeToDelete = current->next;
            current->next = current->next->next;
            delete nodeToDelete;
            listSize--;
            return true;
        }

        return false; // Element not found
    }

    /**
     * Delete node at specific index
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool deleteAt(int index) {
        if (index < 0 || index >= listSize || head == nullptr) {
            return false;
        }

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            listSize--;
            return true;
        }

        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* nodeToDelete = current->next;
        current->next = current->next->next;
        delete nodeToDelete;
        listSize--;
        return true;
    }

    /**
     * Search for element and return its position (0-indexed)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int search(int data) const {
        Node* current = head;
        int position = 0;

        while (current != nullptr) {
            if (current->data == data) {
                return position;
            }
            current = current->next;
            position++;
        }

        return -1; // Element not found
    }

    /**
     * Get element at specific index
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int get(int index) const {
        if (index < 0 || index >= listSize) {
            throw std::out_of_range("Index out of bounds");
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    /**
     * Return the size of the list
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int size() const {
        return listSize;
    }

    /**
     * Check if the list is empty
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool isEmpty() const {
        return head == nullptr;
    }

    /**
     * Reverse the linked list iteratively
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void reverse() {
        Node* previous = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }

    /**
     * Find the middle element using slow/fast pointer technique
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int getMiddle() const {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }

        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow->data;
    }

    /**
     * Remove duplicates from sorted linked list
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void removeDuplicates() {
        if (head == nullptr) {
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->data == current->next->data) {
                Node* duplicate = current->next;
                current->next = current->next->next;
                delete duplicate;
                listSize--;
            } else {
                current = current->next;
            }
        }
    }

    /**
     * Detect if there's a cycle in the list using Floyd's algorithm
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool detectLoop() const {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }

        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                return true; // Loop detected
            }
        }

        return false; // No loop
    }

    /**
     * Merge this list with another sorted linked list
     * Time Complexity: O(m + n)
     * Space Complexity: O(1)
     */
    void mergeSorted(SinglyLinkedList& other) {
        Node* current1 = head;
        Node* current2 = other.head;
        Node* dummy = new Node(0);
        Node* tail = dummy;

        while (current1 != nullptr && current2 != nullptr) {
            if (current1->data <= current2->data) {
                tail->next = current1;
                current1 = current1->next;
            } else {
                tail->next = current2;
                current2 = current2->next;
            }
            tail = tail->next;
        }

        // Append remaining nodes
        if (current1 != nullptr) {
            tail->next = current1;
        } else {
            tail->next = current2;
        }

        // Update heads and sizes
        head = dummy->next;
        listSize += other.listSize;
        other.head = nullptr;
        other.listSize = 0;

        delete dummy;
    }

    /**
     * Display all elements in the list
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void display() const {
        Node* current = head;
        std::cout << "[";
        
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        
        std::cout << "]" << std::endl;
    }

    /**
     * Clear all nodes from the list
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        listSize = 0;
    }

    // Utility function for testing - create a loop for testing detectLoop
    void createLoopForTesting(int position) {
        if (position < 0 || position >= listSize) {
            return;
        }

        Node* loopNode = head;
        for (int i = 0; i < position; i++) {
            loopNode = loopNode->next;
        }

        Node* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
        }

        tail->next = loopNode;
    }
};

// Example usage and testing
int main() {
    SinglyLinkedList list;

    // Test basic operations
    std::cout << "=== Testing Singly Linked List ===" << std::endl;
    
    // Insert elements
    list.insert(3);
    list.insert(1);
    list.append(5);
    list.insertAt(1, 2);
    
    std::cout << "List after insertions: ";
    list.display();
    std::cout << "Size: " << list.size() << std::endl;

    // Search operations
    std::cout << "Position of 5: " << list.search(5) << std::endl;
    std::cout << "Element at index 2: " << list.get(2) << std::endl;
    std::cout << "Middle element: " << list.getMiddle() << std::endl;

    // Test reverse
    list.reverse();
    std::cout << "List after reverse: ";
    list.display();

    // Test delete operations
    list.deleteElement(2);
    std::cout << "List after deleting 2: ";
    list.display();

    // Test with duplicates
    SinglyLinkedList sortedList;
    sortedList.append(1);
    sortedList.append(2);
    sortedList.append(2);
    sortedList.append(3);
    sortedList.append(3);
    sortedList.append(4);
    
    std::cout << "Sorted list with duplicates: ";
    sortedList.display();
    
    sortedList.removeDuplicates();
    std::cout << "After removing duplicates: ";
    sortedList.display();

    // Test loop detection
    std::cout << "Has loop: " << (list.detectLoop() ? "Yes" : "No") << std::endl;

    return 0;
}