#include <iostream>
#include <stdexcept>
#include <vector>

/**
 * Queue Implementation using Circular Array
 * FIFO (First In, First Out) data structure
 */

template<typename T>
class Queue {
private:
    T* queueArray;
    int capacity;
    int frontIndex;
    int rearIndex;
    int currentSize;
    static const int DEFAULT_CAPACITY = 10;
    
    void resize() {
        int oldCapacity = capacity;
        capacity *= 2;
        T* newArray = new T[capacity];
        
        // Copy elements in order
        for (int i = 0; i < currentSize; i++) {
            newArray[i] = queueArray[(frontIndex + i) % oldCapacity];
        }
        
        delete[] queueArray;
        queueArray = newArray;
        frontIndex = 0;
        rearIndex = currentSize - 1;
    }

public:
    /**
     * Constructor - Initialize empty queue
     * Time Complexity: O(1)
     * Space Complexity: O(capacity)
     */
    Queue(int initialCapacity = DEFAULT_CAPACITY) 
        : capacity(initialCapacity), frontIndex(0), rearIndex(-1), currentSize(0) {
        if (initialCapacity <= 0) {
            throw std::invalid_argument("Capacity must be positive");
        }
        queueArray = new T[capacity];
    }

    /**
     * Copy Constructor
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    Queue(const Queue& other) 
        : capacity(other.capacity), frontIndex(0), rearIndex(-1), currentSize(other.currentSize) {
        queueArray = new T[capacity];
        
        // Copy elements in order
        for (int i = 0; i < currentSize; i++) {
            queueArray[i] = other.queueArray[(other.frontIndex + i) % other.capacity];
            rearIndex = i;
        }
    }

    /**
     * Assignment Operator
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            delete[] queueArray;
            capacity = other.capacity;
            currentSize = other.currentSize;
            frontIndex = 0;
            rearIndex = -1;
            queueArray = new T[capacity];
            
            for (int i = 0; i < currentSize; i++) {
                queueArray[i] = other.queueArray[(other.frontIndex + i) % other.capacity];
                rearIndex = i;
            }
        }
        return *this;
    }

    /**
     * Destructor - Clean up memory
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    ~Queue() {
        delete[] queueArray;
    }

    /**
     * Add element to rear of queue
     * Time Complexity: O(1) amortized, O(n) worst case for resize
     * Space Complexity: O(1)
     */
    void enqueue(const T& element) {
        if (currentSize == capacity) {
            resize();
        }
        
        rearIndex = (rearIndex + 1) % capacity;
        queueArray[rearIndex] = element;
        currentSize++;
    }

    /**
     * Remove and return front element
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        
        T frontElement = queueArray[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        currentSize--;
        return frontElement;
    }

    /**
     * Get front element without removing
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    T front() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return queueArray[frontIndex];
    }

    /**
     * Get rear element without removing
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    T rear() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return queueArray[rearIndex];
    }

    /**
     * Check if queue is empty
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool isEmpty() const {
        return currentSize == 0;
    }

    /**
     * Check if queue is full
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool isFull() const {
        return currentSize == capacity;
    }

    /**
     * Get number of elements in queue
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int size() const {
        return currentSize;
    }

    /**
     * Get current capacity of queue
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int getCapacity() const {
        return capacity;
    }

    /**
     * Clear all elements from queue
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void clear() {
        frontIndex = 0;
        rearIndex = -1;
        currentSize = 0;
    }

    /**
     * Display queue contents (for debugging)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void display() const {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Queue (front to rear): ";
        for (int i = 0; i < currentSize; i++) {
            std::cout << queueArray[(frontIndex + i) % capacity];
            if (i < currentSize - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
};

/**
 * Priority Queue implementation using max heap
 */
template<typename T>
class PriorityQueue {
private:
    std::vector<T> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)] < heap[index]) {
            std::swap(heap[parent(index)], heap[index]);
            index = parent(index);
        }
    }
    
    void heapifyDown(int index) {
        int maxIndex = index;
        int left = leftChild(index);
        int right = rightChild(index);
        
        if (left < heap.size() && heap[left] > heap[maxIndex]) {
            maxIndex = left;
        }
        
        if (right < heap.size() && heap[right] > heap[maxIndex]) {
            maxIndex = right;
        }
        
        if (index != maxIndex) {
            std::swap(heap[index], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    /**
     * Insert element with priority
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    void enqueue(const T& element) {
        heap.push_back(element);
        heapifyUp(heap.size() - 1);
    }

    /**
     * Remove and return highest priority element
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Priority queue is empty");
        }
        
        T maxElement = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!isEmpty()) {
            heapifyDown(0);
        }
        
        return maxElement;
    }

    /**
     * Get highest priority element without removing
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    T top() const {
        if (isEmpty()) {
            throw std::underflow_error("Priority queue is empty");
        }
        return heap[0];
    }

    /**
     * Check if priority queue is empty
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool isEmpty() const {
        return heap.empty();
    }

    /**
     * Get number of elements
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int size() const {
        return heap.size();
    }
};

// Queue Applications

/**
 * Solve Josephus Problem using circular queue
 * Time Complexity: O(n * k)
 * Space Complexity: O(n)
 */
int josephusProblem(int n, int k) {
    if (n <= 0 || k <= 0) {
        throw std::invalid_argument("n and k must be positive");
    }
    
    Queue<int> queue;
    
    // Add all people to queue (1 to n)
    for (int i = 1; i <= n; i++) {
        queue.enqueue(i);
    }
    
    // Eliminate every k-th person
    while (queue.size() > 1) {
        // Move k-1 people from front to rear
        for (int i = 0; i < k - 1; i++) {
            int person = queue.dequeue();
            queue.enqueue(person);
        }
        // Eliminate the k-th person
        queue.dequeue();
    }
    
    return queue.front();
}

/**
 * Generate binary numbers from 1 to n using queue
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
std::vector<std::string> generateBinaryNumbers(int n) {
    std::vector<std::string> result;
    
    if (n <= 0) {
        return result;
    }
    
    Queue<std::string> queue;
    queue.enqueue("1");
    
    for (int i = 0; i < n; i++) {
        std::string binary = queue.dequeue();
        result.push_back(binary);
        
        // Generate next binary numbers by appending 0 and 1
        queue.enqueue(binary + "0");
        queue.enqueue(binary + "1");
    }
    
    return result;
}

/**
 * Level order traversal simulation (BFS pattern)
 * Time Complexity: O(n)
 * Space Complexity: O(w) where w is maximum width
 */
void levelOrderTraversal(const std::vector<std::vector<int>>& graph, int start) {
    if (start < 0 || start >= graph.size()) {
        throw std::invalid_argument("Invalid start vertex");
    }
    
    Queue<int> queue;
    std::vector<bool> visited(graph.size(), false);
    
    queue.enqueue(start);
    visited[start] = true;
    
    std::cout << "Level order traversal: ";
    while (!queue.isEmpty()) {
        int vertex = queue.dequeue();
        std::cout << vertex << " ";
        
        // Add all unvisited neighbors
        for (int neighbor : graph[vertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.enqueue(neighbor);
            }
        }
    }
    std::cout << std::endl;
}

/**
 * Reverse first k elements of queue
 * Time Complexity: O(k)
 * Space Complexity: O(k)
 */
template<typename T>
void reverseFirstKElements(Queue<T>& queue, int k) {
    if (k <= 0 || k > queue.size()) {
        throw std::invalid_argument("Invalid value of k");
    }
    
    // Use a stack to reverse first k elements
    T* stack = new T[k];
    int top = -1;
    
    // Push first k elements to stack
    for (int i = 0; i < k; i++) {
        stack[++top] = queue.dequeue();
    }
    
    // Pop from stack and enqueue back (reversed order)
    while (top >= 0) {
        queue.enqueue(stack[top--]);
    }
    
    // Move remaining elements from front to rear
    int remaining = queue.size() - k;
    for (int i = 0; i < remaining; i++) {
        T element = queue.dequeue();
        queue.enqueue(element);
    }
    
    delete[] stack;
}

// Example usage and testing functions
void demonstrateQueue() {
    std::cout << "=== Queue Demonstration ===" << std::endl;
    
    Queue<int> queue;
    
    // Test enqueue operations
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    
    std::cout << "After enqueueing 10, 20, 30:" << std::endl;
    queue.display();
    
    // Test front and rear
    std::cout << "Front: " << queue.front() << std::endl;
    std::cout << "Rear: " << queue.rear() << std::endl;
    std::cout << "Size: " << queue.size() << std::endl;
    
    // Test dequeue operations
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    
    std::cout << "After dequeuing twice:" << std::endl;
    queue.display();
    
    // Test applications
    std::cout << "\n=== Queue Applications ===" << std::endl;
    
    int survivor = josephusProblem(7, 3);
    std::cout << "Josephus Problem (n=7, k=3): Survivor is " << survivor << std::endl;
    
    std::vector<std::string> binaries = generateBinaryNumbers(10);
    std::cout << "Binary numbers 1 to 10: ";
    for (const std::string& binary : binaries) {
        std::cout << binary << " ";
    }
    std::cout << std::endl;
    
    // Priority Queue demonstration
    std::cout << "\n=== Priority Queue Demonstration ===" << std::endl;
    
    PriorityQueue<int> pq;
    pq.enqueue(10);
    pq.enqueue(30);
    pq.enqueue(20);
    pq.enqueue(40);
    
    std::cout << "Priority Queue elements (max first): ";
    while (!pq.isEmpty()) {
        std::cout << pq.dequeue() << " ";
    }
    std::cout << std::endl;
}