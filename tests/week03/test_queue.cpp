#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include <string>

// Mock Queue class for testing (replace with actual implementation)
template<typename T>
class Queue {
public:
    Queue() {}
    ~Queue() {}
    
    void enqueue(const T& element);
    T dequeue();
    T front() const;
    T rear() const;
    bool isEmpty() const;
    int size() const;
    void clear();
    void display() const;
};

template<typename T>
class PriorityQueue {
public:
    PriorityQueue() {}
    ~PriorityQueue() {}
    
    void enqueue(const T& element);
    T dequeue();
    T top() const;
    bool isEmpty() const;
    int size() const;
};

// Forward declare application functions
int josephusProblem(int n, int k);
std::vector<std::string> generateBinaryNumbers(int n);
void levelOrderTraversal(const std::vector<std::vector<int>>& graph, int start);
template<typename T> void reverseFirstKElements(Queue<T>& queue, int k);
std::vector<int> slidingWindowMaximum(const std::vector<int>& nums, int k);

class QueueTest : public ::testing::Test {
protected:
    Queue<int> queue;
    
    void SetUp() override {
        // Start with empty queue for each test
    }
    
    void TearDown() override {
        // Cleanup handled by destructor
    }
};

// Basic Queue Operations Tests
TEST_F(QueueTest, EnqueueSingleElement) {
    queue.enqueue(10);
    EXPECT_EQ(queue.size(), 1);
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.rear(), 10);
}

TEST_F(QueueTest, EnqueueMultipleElements) {
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.rear(), 30);
}

TEST_F(QueueTest, DequeueSingleElement) {
    queue.enqueue(42);
    int dequeued = queue.dequeue();
    
    EXPECT_EQ(dequeued, 42);
    EXPECT_EQ(queue.size(), 0);
    EXPECT_TRUE(queue.isEmpty());
}

TEST_F(QueueTest, DequeueMultipleElements) {
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    
    EXPECT_EQ(queue.dequeue(), 10);
    EXPECT_EQ(queue.dequeue(), 20);
    EXPECT_EQ(queue.dequeue(), 30);
    EXPECT_TRUE(queue.isEmpty());
}

TEST_F(QueueTest, DequeueFromEmptyQueue) {
    EXPECT_THROW(queue.dequeue(), std::underflow_error);
}

TEST_F(QueueTest, FrontOfEmptyQueue) {
    EXPECT_THROW(queue.front(), std::underflow_error);
}

TEST_F(QueueTest, RearOfEmptyQueue) {
    EXPECT_THROW(queue.rear(), std::underflow_error);
}

TEST_F(QueueTest, FrontDoesNotRemoveElement) {
    queue.enqueue(100);
    
    EXPECT_EQ(queue.front(), 100);
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 100); // Should still be there
}

TEST_F(QueueTest, IsEmptyOnNewQueue) {
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.size(), 0);
}

TEST_F(QueueTest, IsEmptyAfterOperations) {
    queue.enqueue(1);
    EXPECT_FALSE(queue.isEmpty());
    
    queue.dequeue();
    EXPECT_TRUE(queue.isEmpty());
}

TEST_F(QueueTest, ClearQueue) {
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    queue.clear();
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.size(), 0);
}

TEST_F(QueueTest, FIFOBehavior) {
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    
    EXPECT_EQ(queue.dequeue(), 1);
    EXPECT_EQ(queue.dequeue(), 2);
    EXPECT_EQ(queue.dequeue(), 3);
    EXPECT_EQ(queue.dequeue(), 4);
}

TEST_F(QueueTest, MixedOperations) {
    queue.enqueue(1);
    queue.enqueue(2);
    EXPECT_EQ(queue.dequeue(), 1);
    
    queue.enqueue(3);
    queue.enqueue(4);
    EXPECT_EQ(queue.dequeue(), 2);
    EXPECT_EQ(queue.dequeue(), 3);
    
    queue.enqueue(5);
    EXPECT_EQ(queue.front(), 4);
    EXPECT_EQ(queue.rear(), 5);
}

// Circular Behavior Tests
TEST_F(QueueTest, CircularBehavior) {
    // Test that queue handles wraparound correctly
    for (int i = 0; i < 20; i++) {
        queue.enqueue(i);
        queue.enqueue(i + 100);
        EXPECT_EQ(queue.dequeue(), i);
    }
    
    // Should have 20 elements left (100-119)
    EXPECT_EQ(queue.size(), 20);
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(queue.dequeue(), i + 100);
    }
}

// Dynamic Resizing Tests
TEST_F(QueueTest, DynamicResizing) {
    // Enqueue many elements to test resizing
    for (int i = 0; i < 100; i++) {
        queue.enqueue(i);
    }
    
    EXPECT_EQ(queue.size(), 100);
    EXPECT_EQ(queue.front(), 0);
    EXPECT_EQ(queue.rear(), 99);
    
    // Dequeue all elements
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(queue.dequeue(), i);
    }
    
    EXPECT_TRUE(queue.isEmpty());
}

// String Queue Tests
class StringQueueTest : public ::testing::Test {
protected:
    Queue<std::string> stringQueue;
};

TEST_F(StringQueueTest, StringOperations) {
    stringQueue.enqueue("First");
    stringQueue.enqueue("Second");
    stringQueue.enqueue("Third");
    
    EXPECT_EQ(stringQueue.dequeue(), "First");
    EXPECT_EQ(stringQueue.dequeue(), "Second");
    EXPECT_EQ(stringQueue.dequeue(), "Third");
}

// Priority Queue Tests
class PriorityQueueTest : public ::testing::Test {
protected:
    PriorityQueue<int> pq;
};

TEST_F(PriorityQueueTest, BasicOperations) {
    pq.enqueue(10);
    pq.enqueue(30);
    pq.enqueue(20);
    pq.enqueue(40);
    
    EXPECT_EQ(pq.size(), 4);
    EXPECT_EQ(pq.top(), 40);
    
    EXPECT_EQ(pq.dequeue(), 40);
    EXPECT_EQ(pq.dequeue(), 30);
    EXPECT_EQ(pq.dequeue(), 20);
    EXPECT_EQ(pq.dequeue(), 10);
    
    EXPECT_TRUE(pq.isEmpty());
}

TEST_F(PriorityQueueTest, EmptyOperations) {
    EXPECT_TRUE(pq.isEmpty());
    EXPECT_EQ(pq.size(), 0);
    EXPECT_THROW(pq.top(), std::underflow_error);
    EXPECT_THROW(pq.dequeue(), std::underflow_error);
}

TEST_F(PriorityQueueTest, DuplicateElements) {
    pq.enqueue(5);
    pq.enqueue(5);
    pq.enqueue(5);
    
    EXPECT_EQ(pq.size(), 3);
    EXPECT_EQ(pq.dequeue(), 5);
    EXPECT_EQ(pq.dequeue(), 5);
    EXPECT_EQ(pq.dequeue(), 5);
}

// Queue Applications Tests
class QueueApplicationsTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(QueueApplicationsTest, JosephusProblemBasic) {
    EXPECT_EQ(josephusProblem(5, 2), 3);
    EXPECT_EQ(josephusProblem(7, 3), 4);
    EXPECT_EQ(josephusProblem(1, 1), 1);
    EXPECT_EQ(josephusProblem(3, 1), 3);
}

TEST_F(QueueApplicationsTest, JosephusProblemEdgeCases) {
    EXPECT_EQ(josephusProblem(1, 5), 1); // k > n
    EXPECT_EQ(josephusProblem(10, 1), 10); // k = 1, survivor is last person
}

TEST_F(QueueApplicationsTest, JosephusProblemInvalidInput) {
    EXPECT_THROW(josephusProblem(0, 1), std::invalid_argument);
    EXPECT_THROW(josephusProblem(1, 0), std::invalid_argument);
    EXPECT_THROW(josephusProblem(-1, 1), std::invalid_argument);
}

TEST_F(QueueApplicationsTest, GenerateBinaryNumbersBasic) {
    std::vector<std::string> result1 = generateBinaryNumbers(5);
    std::vector<std::string> expected1 = {"1", "10", "11", "100", "101"};
    EXPECT_EQ(result1, expected1);
    
    std::vector<std::string> result2 = generateBinaryNumbers(3);
    std::vector<std::string> expected2 = {"1", "10", "11"};
    EXPECT_EQ(result2, expected2);
}

TEST_F(QueueApplicationsTest, GenerateBinaryNumbersEdgeCases) {
    std::vector<std::string> result0 = generateBinaryNumbers(0);
    EXPECT_TRUE(result0.empty());
    
    std::vector<std::string> result1 = generateBinaryNumbers(1);
    std::vector<std::string> expected1 = {"1"};
    EXPECT_EQ(result1, expected1);
}

TEST_F(QueueApplicationsTest, GenerateBinaryNumbersLarge) {
    std::vector<std::string> result = generateBinaryNumbers(10);
    std::vector<std::string> expected = {
        "1", "10", "11", "100", "101", "110", "111", "1000", "1001", "1010"
    };
    EXPECT_EQ(result, expected);
}

TEST_F(QueueApplicationsTest, ReverseFirstKElements) {
    Queue<int> testQueue;
    testQueue.enqueue(1);
    testQueue.enqueue(2);
    testQueue.enqueue(3);
    testQueue.enqueue(4);
    testQueue.enqueue(5);
    
    reverseFirstKElements(testQueue, 3);
    
    // After reversing first 3: should be 3, 2, 1, 4, 5
    EXPECT_EQ(testQueue.dequeue(), 3);
    EXPECT_EQ(testQueue.dequeue(), 2);
    EXPECT_EQ(testQueue.dequeue(), 1);
    EXPECT_EQ(testQueue.dequeue(), 4);
    EXPECT_EQ(testQueue.dequeue(), 5);
}

TEST_F(QueueApplicationsTest, ReverseFirstKElementsEdgeCases) {
    Queue<int> testQueue;
    testQueue.enqueue(1);
    testQueue.enqueue(2);
    testQueue.enqueue(3);
    
    // k = 0, no change
    reverseFirstKElements(testQueue, 0);
    EXPECT_EQ(testQueue.dequeue(), 1);
    
    // Reset queue
    testQueue.enqueue(1);
    testQueue.enqueue(2);
    testQueue.enqueue(3);
    
    // k = size, reverse entire queue
    reverseFirstKElements(testQueue, 3);
    EXPECT_EQ(testQueue.dequeue(), 3);
    EXPECT_EQ(testQueue.dequeue(), 2);
    EXPECT_EQ(testQueue.dequeue(), 1);
}

TEST_F(QueueApplicationsTest, ReverseFirstKElementsInvalidInput) {
    Queue<int> testQueue;
    testQueue.enqueue(1);
    testQueue.enqueue(2);
    
    EXPECT_THROW(reverseFirstKElements(testQueue, -1), std::invalid_argument);
    EXPECT_THROW(reverseFirstKElements(testQueue, 3), std::invalid_argument); // k > size
}

TEST_F(QueueApplicationsTest, SlidingWindowMaximumBasic) {
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    std::vector<int> result = slidingWindowMaximum(nums, 3);
    std::vector<int> expected = {3, 3, 5, 5, 6, 7};
    EXPECT_EQ(result, expected);
}

TEST_F(QueueApplicationsTest, SlidingWindowMaximumEdgeCases) {
    // Window size = 1
    std::vector<int> nums1 = {1, 2, 3, 4};
    std::vector<int> result1 = slidingWindowMaximum(nums1, 1);
    EXPECT_EQ(result1, nums1);
    
    // Window size = array size
    std::vector<int> nums2 = {1, 3, 2, 4};
    std::vector<int> result2 = slidingWindowMaximum(nums2, 4);
    std::vector<int> expected2 = {4};
    EXPECT_EQ(result2, expected2);
    
    // Single element
    std::vector<int> nums3 = {5};
    std::vector<int> result3 = slidingWindowMaximum(nums3, 1);
    std::vector<int> expected3 = {5};
    EXPECT_EQ(result3, expected3);
}

TEST_F(QueueApplicationsTest, SlidingWindowMaximumAllSame) {
    std::vector<int> nums = {2, 2, 2, 2, 2};
    std::vector<int> result = slidingWindowMaximum(nums, 3);
    std::vector<int> expected = {2, 2, 2};
    EXPECT_EQ(result, expected);
}

TEST_F(QueueApplicationsTest, SlidingWindowMaximumDescending) {
    std::vector<int> nums = {5, 4, 3, 2, 1};
    std::vector<int> result = slidingWindowMaximum(nums, 3);
    std::vector<int> expected = {5, 4, 3};
    EXPECT_EQ(result, expected);
}

// Performance Tests
TEST_F(QueueTest, PerformanceTest) {
    const int LARGE_SIZE = 10000;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Enqueue operations
    for (int i = 0; i < LARGE_SIZE; i++) {
        queue.enqueue(i);
    }
    
    // Dequeue operations
    for (int i = 0; i < LARGE_SIZE; i++) {
        queue.dequeue();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Should complete reasonably quickly (less than 100ms)
    EXPECT_LT(duration.count(), 100);
}

// Memory Safety Tests
TEST_F(QueueTest, CopyConstructor) {
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    Queue<int> copied(queue);
    
    EXPECT_EQ(copied.size(), 3);
    EXPECT_EQ(copied.dequeue(), 1);
    EXPECT_EQ(copied.dequeue(), 2);
    EXPECT_EQ(copied.dequeue(), 3);
    
    // Original should be unchanged
    EXPECT_EQ(queue.size(), 3);
}

TEST_F(QueueTest, AssignmentOperator) {
    queue.enqueue(10);
    queue.enqueue(20);
    
    Queue<int> assigned;
    assigned = queue;
    
    EXPECT_EQ(assigned.size(), 2);
    EXPECT_EQ(assigned.dequeue(), 10);
    EXPECT_EQ(assigned.dequeue(), 20);
    
    // Original should be unchanged
    EXPECT_EQ(queue.size(), 2);
}

// Level Order Traversal Test (requires capturing output)
TEST_F(QueueApplicationsTest, LevelOrderTraversalBasic) {
    // Create a simple graph: 0->1,2  1->3,4  2->5,6
    std::vector<std::vector<int>> graph = {
        {1, 2},    // 0 connects to 1, 2
        {3, 4},    // 1 connects to 3, 4
        {5, 6},    // 2 connects to 5, 6
        {},        // 3 connects to nothing
        {},        // 4 connects to nothing
        {},        // 5 connects to nothing
        {}         // 6 connects to nothing
    };
    
    // Test should not throw (actual output verification would require capturing stdout)
    EXPECT_NO_THROW(levelOrderTraversal(graph, 0));
}

TEST_F(QueueApplicationsTest, LevelOrderTraversalInvalidStart) {
    std::vector<std::vector<int>> graph = {{1}, {2}, {}};
    
    EXPECT_THROW(levelOrderTraversal(graph, -1), std::invalid_argument);
    EXPECT_THROW(levelOrderTraversal(graph, 3), std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}