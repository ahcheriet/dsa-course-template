#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>

// Include the student's implementation
// Note: In actual testing, this would include the compiled object or header
// For now, we assume the SinglyLinkedList class is available

// Mock SinglyLinkedList class for testing (replace with actual implementation)
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
    SinglyLinkedList() : head(nullptr), listSize(0) {}
    
    ~SinglyLinkedList() {
        clear();
    }
    
    // Test interface methods (these would be defined in student's implementation)
    void insert(int data);
    void insertAt(int index, int data);
    bool deleteValue(int data);
    void deleteAt(int index);
    bool search(int data);
    int size() const;
    void reverse();
    int getMiddle();
    void removeDuplicates();
    bool detectLoop();
    void mergeSorted(SinglyLinkedList& other);
    void display();
    void clear();
    bool isEmpty() const;
    int getAt(int index);
};

class SinglyLinkedListTest : public ::testing::Test {
protected:
    SinglyLinkedList list;
    
    void SetUp() override {
        // Initialize with empty list for each test
    }
    
    void TearDown() override {
        // Cleanup is handled by destructor
    }
};

// Basic Insertion Tests
TEST_F(SinglyLinkedListTest, InsertSingleElement) {
    list.insert(5);
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.getAt(0), 5);
}

TEST_F(SinglyLinkedListTest, InsertMultipleElements) {
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    EXPECT_EQ(list.size(), 3);
    // Elements are inserted at the beginning, so order is reversed
    EXPECT_EQ(list.getAt(0), 3);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 1);
}

TEST_F(SinglyLinkedListTest, InsertAtBeginning) {
    list.insert(1);
    list.insert(2);
    list.insertAt(0, 0);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getAt(0), 0);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 1);
}

TEST_F(SinglyLinkedListTest, InsertAtMiddle) {
    list.insert(1);
    list.insert(3);
    list.insertAt(1, 2);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getAt(0), 3);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 1);
}

TEST_F(SinglyLinkedListTest, InsertAtEnd) {
    list.insert(1);
    list.insert(2);
    list.insertAt(2, 0);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getAt(2), 0);
}

TEST_F(SinglyLinkedListTest, InsertAtInvalidIndex) {
    list.insert(1);
    EXPECT_THROW(list.insertAt(-1, 0), std::out_of_range);
    EXPECT_THROW(list.insertAt(2, 0), std::out_of_range);
}

// Deletion Tests
TEST_F(SinglyLinkedListTest, DeleteExistingElement) {
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    EXPECT_TRUE(list.deleteValue(2));
    EXPECT_EQ(list.size(), 2);
    EXPECT_FALSE(list.search(2));
}

TEST_F(SinglyLinkedListTest, DeleteNonExistingElement) {
    list.insert(1);
    list.insert(2);
    
    EXPECT_FALSE(list.deleteValue(5));
    EXPECT_EQ(list.size(), 2);
}

TEST_F(SinglyLinkedListTest, DeleteFromEmptyList) {
    EXPECT_FALSE(list.deleteValue(1));
    EXPECT_EQ(list.size(), 0);
}

TEST_F(SinglyLinkedListTest, DeleteAtValidIndex) {
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    list.deleteAt(1); // Delete middle element
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.getAt(0), 3);
    EXPECT_EQ(list.getAt(1), 1);
}

TEST_F(SinglyLinkedListTest, DeleteAtInvalidIndex) {
    list.insert(1);
    EXPECT_THROW(list.deleteAt(-1), std::out_of_range);
    EXPECT_THROW(list.deleteAt(1), std::out_of_range);
}

// Search Tests
TEST_F(SinglyLinkedListTest, SearchExistingElement) {
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    EXPECT_TRUE(list.search(2));
    EXPECT_TRUE(list.search(1));
    EXPECT_TRUE(list.search(3));
}

TEST_F(SinglyLinkedListTest, SearchNonExistingElement) {
    list.insert(1);
    list.insert(2);
    
    EXPECT_FALSE(list.search(5));
}

TEST_F(SinglyLinkedListTest, SearchInEmptyList) {
    EXPECT_FALSE(list.search(1));
}

// Size and Empty Tests
TEST_F(SinglyLinkedListTest, EmptyListSize) {
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(SinglyLinkedListTest, NonEmptyListSize) {
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.isEmpty());
}

// Reverse Tests
TEST_F(SinglyLinkedListTest, ReverseList) {
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    // Before reverse: 3 -> 2 -> 1
    list.reverse();
    
    // After reverse: 1 -> 2 -> 3
    EXPECT_EQ(list.getAt(0), 1);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 3);
}

TEST_F(SinglyLinkedListTest, ReverseSingleElement) {
    list.insert(42);
    list.reverse();
    
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.getAt(0), 42);
}

TEST_F(SinglyLinkedListTest, ReverseEmptyList) {
    list.reverse();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

// Get Middle Tests
TEST_F(SinglyLinkedListTest, GetMiddleOddSize) {
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    
    // List: 5 -> 4 -> 3 -> 2 -> 1, middle should be 3
    EXPECT_EQ(list.getMiddle(), 3);
}

TEST_F(SinglyLinkedListTest, GetMiddleEvenSize) {
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    
    // List: 4 -> 3 -> 2 -> 1, middle should be 3 (first of two middle elements)
    EXPECT_EQ(list.getMiddle(), 3);
}

TEST_F(SinglyLinkedListTest, GetMiddleSingleElement) {
    list.insert(42);
    EXPECT_EQ(list.getMiddle(), 42);
}

TEST_F(SinglyLinkedListTest, GetMiddleEmptyList) {
    EXPECT_THROW(list.getMiddle(), std::runtime_error);
}

// Remove Duplicates Tests (assuming sorted list)
TEST_F(SinglyLinkedListTest, RemoveDuplicatesFromSortedList) {
    // Create sorted list with duplicates: 1 -> 1 -> 2 -> 3 -> 3 -> 3
    list.insertAt(0, 1);
    list.insertAt(1, 1);
    list.insertAt(2, 2);
    list.insertAt(3, 3);
    list.insertAt(4, 3);
    list.insertAt(5, 3);
    
    list.removeDuplicates();
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getAt(0), 1);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 3);
}

TEST_F(SinglyLinkedListTest, RemoveDuplicatesNoDuplicates) {
    list.insertAt(0, 1);
    list.insertAt(1, 2);
    list.insertAt(2, 3);
    
    list.removeDuplicates();
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getAt(0), 1);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 3);
}

// Loop Detection Tests
TEST_F(SinglyLinkedListTest, DetectLoopNoLoop) {
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    EXPECT_FALSE(list.detectLoop());
}

TEST_F(SinglyLinkedListTest, DetectLoopEmptyList) {
    EXPECT_FALSE(list.detectLoop());
}

TEST_F(SinglyLinkedListTest, DetectLoopSingleElement) {
    list.insert(1);
    EXPECT_FALSE(list.detectLoop());
}

// Merge Sorted Lists Tests
TEST_F(SinglyLinkedListTest, MergeSortedLists) {
    // First list: 1 -> 3 -> 5
    list.insertAt(0, 1);
    list.insertAt(1, 3);
    list.insertAt(2, 5);
    
    // Second list: 2 -> 4 -> 6
    SinglyLinkedList list2;
    list2.insertAt(0, 2);
    list2.insertAt(1, 4);
    list2.insertAt(2, 6);
    
    list.mergeSorted(list2);
    
    // Merged list should be: 1 -> 2 -> 3 -> 4 -> 5 -> 6
    EXPECT_EQ(list.size(), 6);
    EXPECT_EQ(list.getAt(0), 1);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 3);
    EXPECT_EQ(list.getAt(3), 4);
    EXPECT_EQ(list.getAt(4), 5);
    EXPECT_EQ(list.getAt(5), 6);
}

TEST_F(SinglyLinkedListTest, MergeWithEmptyList) {
    list.insert(1);
    list.insert(2);
    
    SinglyLinkedList emptyList;
    list.mergeSorted(emptyList);
    
    EXPECT_EQ(list.size(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}