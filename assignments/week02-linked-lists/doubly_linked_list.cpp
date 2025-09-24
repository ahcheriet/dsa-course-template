#include <iostream>
#include <stdexcept>

/**
 * Doubly Linked List Implementation
 * Each node contains data and pointers to both next and previous nodes
 */

// Node structure for doubly linked list
struct DoublyNode {
    int data;
    DoublyNode* next;
    DoublyNode* prev;
    
    DoublyNode(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    DoublyNode* head;
    DoublyNode* tail;
    int listSize;

public:
    /**
     * Constructor - Initialize empty list
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    /**
     * Destructor - Clean up all nodes
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    ~DoublyLinkedList() {
        clear();
    }

    /**
     * Insert element at the beginning of the list
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void insertFront(int data) {
        DoublyNode* newNode = new DoublyNode(data);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        
        listSize++;
    }

    /**
     * Insert element at the end of the list
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void insertBack(int data) {
        DoublyNode* newNode = new DoublyNode(data);
        
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        
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
            insertFront(data);
            return;
        }

        if (index == listSize) {
            insertBack(data);
            return;
        }

        DoublyNode* newNode = new DoublyNode(data);
        DoublyNode* current = getNodeAt(index);
        
        // Insert before current node
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        
        listSize++;
    }

    /**
     * Delete first occurrence of element
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool deleteElement(int data) {
        DoublyNode* current = head;
        
        while (current != nullptr) {
            if (current->data == data) {
                deleteNode(current);
                return true;
            }
            current = current->next;
        }
        
        return false; // Element not found
    }

    /**
     * Delete node at specific index
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool deleteAt(int index) {
        if (index < 0 || index >= listSize) {
            return false;
        }

        DoublyNode* nodeToDelete = getNodeAt(index);
        deleteNode(nodeToDelete);
        return true;
    }

    /**
     * Delete first element
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool deleteFront() {
        if (head == nullptr) {
            return false;
        }

        deleteNode(head);
        return true;
    }

    /**
     * Delete last element
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool deleteBack() {
        if (tail == nullptr) {
            return false;
        }

        deleteNode(tail);
        return true;
    }

    /**
     * Search for element and return its position (0-indexed)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int search(int data) const {
        DoublyNode* current = head;
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

        return getNodeAt(index)->data;
    }

    /**
     * Get first element
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int front() const {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }

    /**
     * Get last element
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int back() const {
        if (tail == nullptr) {
            throw std::runtime_error("List is empty");
        }
        return tail->data;
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
     * Reverse the doubly linked list
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void reverse() {
        DoublyNode* current = head;
        DoublyNode* temp = nullptr;

        // Swap next and prev pointers for all nodes
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev; // Move to next node (which is now prev)
        }

        // Swap head and tail
        temp = head;
        head = tail;
        tail = temp;
    }

    /**
     * Find the middle element
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int getMiddle() const {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }

        DoublyNode* slow = head;
        DoublyNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow->data;
    }

    /**
     * Remove duplicates from sorted doubly linked list
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void removeDuplicates() {
        if (head == nullptr) {
            return;
        }

        DoublyNode* current = head;
        while (current->next != nullptr) {
            if (current->data == current->next->data) {
                DoublyNode* duplicate = current->next;
                deleteNode(duplicate);
            } else {
                current = current->next;
            }
        }
    }

    /**
     * Display all elements forward
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void displayForward() const {
        DoublyNode* current = head;
        std::cout << "Forward: [";
        
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " <-> ";
            }
            current = current->next;
        }
        
        std::cout << "]" << std::endl;
    }

    /**
     * Display all elements backward
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void displayBackward() const {
        DoublyNode* current = tail;
        std::cout << "Backward: [";
        
        while (current != nullptr) {
            std::cout << current->data;
            if (current->prev != nullptr) {
                std::cout << " <-> ";
            }
            current = current->prev;
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
            DoublyNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        listSize = 0;
    }

private:
    /**
     * Helper function to get node at specific index
     * Optimized to traverse from head or tail based on index position
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    DoublyNode* getNodeAt(int index) const {
        if (index < 0 || index >= listSize) {
            return nullptr;
        }

        DoublyNode* current;
        
        // Traverse from head or tail based on which is closer
        if (index < listSize / 2) {
            // Traverse from head
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            // Traverse from tail
            current = tail;
            for (int i = listSize - 1; i > index; i--) {
                current = current->prev;
            }
        }

        return current;
    }

    /**
     * Helper function to delete a specific node
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void deleteNode(DoublyNode* node) {
        if (node == nullptr) {
            return;
        }

        // Update previous node's next pointer
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head = node->next; // Node is head
        }

        // Update next node's prev pointer
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev; // Node is tail
        }

        delete node;
        listSize--;
    }
};

// Example usage and testing
int main() {
    DoublyLinkedList list;

    std::cout << "=== Testing Doubly Linked List ===" << std::endl;
    
    // Test insertions
    list.insertBack(2);
    list.insertBack(4);
    list.insertFront(1);
    list.insertAt(2, 3);
    list.insertBack(5);
    
    std::cout << "List after insertions: " << std::endl;
    list.displayForward();
    list.displayBackward();
    std::cout << "Size: " << list.size() << std::endl;

    // Test access operations
    std::cout << "Front element: " << list.front() << std::endl;
    std::cout << "Back element: " << list.back() << std::endl;
    std::cout << "Middle element: " << list.getMiddle() << std::endl;
    std::cout << "Element at index 2: " << list.get(2) << std::endl;
    std::cout << "Position of element 4: " << list.search(4) << std::endl;

    // Test deletions
    list.deleteElement(3);
    std::cout << "After deleting 3: " << std::endl;
    list.displayForward();

    list.deleteFront();
    list.deleteBack();
    std::cout << "After deleting front and back: " << std::endl;
    list.displayForward();

    // Test reverse
    list.reverse();
    std::cout << "After reverse: " << std::endl;
    list.displayForward();

    // Test with duplicates
    DoublyLinkedList sortedList;
    sortedList.insertBack(1);
    sortedList.insertBack(2);
    sortedList.insertBack(2);
    sortedList.insertBack(3);
    sortedList.insertBack(3);
    sortedList.insertBack(4);
    
    std::cout << "Sorted list with duplicates: " << std::endl;
    sortedList.displayForward();
    
    sortedList.removeDuplicates();
    std::cout << "After removing duplicates: " << std::endl;
    sortedList.displayForward();

    return 0;
}