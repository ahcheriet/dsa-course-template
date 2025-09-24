#include <gtest/gtest.h>
#include <stdexcept>

// Include the student's implementation
// Note: In actual testing, this would include the compiled object or header

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
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}
    ~DoublyLinkedList() { clear(); }
    
    // Test interface methods (these would be defined in student's implementation)
    void insertFront(int data);
    void insertBack(int data);
    void insertAt(int index, int data);
    bool deleteValue(int data);
    void deleteAt(int index);
    bool search(int data);
    int size() const;
    void reverse();
    void clear();
    bool isEmpty() const;
    int getAt(int index);
    int getFront();
    int getBack();
    void displayForward();
    void displayBackward();
};

class DoublyLinkedListTest : public ::testing::Test {
protected:
    DoublyLinkedList list;
    
    void SetUp() override {
        // Initialize with empty list for each test
    }
    
    void TearDown() override {
        // Cleanup is handled by destructor
    }
};

// Front Insertion Tests
TEST_F(DoublyLinkedListTest, InsertFrontSingleElement) {
    list.insertFront(5);
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.getFront(), 5);
    EXPECT_EQ(list.getBack(), 5);
}

TEST_F(DoublyLinkedListTest, InsertFrontMultipleElements) {
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getFront(), 3);
    EXPECT_EQ(list.getBack(), 1);
    EXPECT_EQ(list.getAt(1), 2);
}

// Back Insertion Tests  
TEST_F(DoublyLinkedListTest, InsertBackSingleElement) {
    list.insertBack(5);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.getFront(), 5);
    EXPECT_EQ(list.getBack(), 5);
}

TEST_F(DoublyLinkedListTest, InsertBackMultipleElements) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getFront(), 1);
    EXPECT_EQ(list.getBack(), 3);
    EXPECT_EQ(list.getAt(1), 2);
}

// Mixed Insertion Tests
TEST_F(DoublyLinkedListTest, MixedInsertions) {
    list.insertFront(2);
    list.insertBack(3);
    list.insertFront(1);
    list.insertBack(4);
    
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.getAt(0), 1);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 3);
    EXPECT_EQ(list.getAt(3), 4);
}

// Insert At Index Tests
TEST_F(DoublyLinkedListTest, InsertAtBeginning) {
    list.insertBack(2);
    list.insertBack(3);
    list.insertAt(0, 1);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getAt(0), 1);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 3);
}

TEST_F(DoublyLinkedListTest, InsertAtMiddle) {
    list.insertBack(1);
    list.insertBack(3);
    list.insertAt(1, 2);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getAt(0), 1);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 3);
}

TEST_F(DoublyLinkedListTest, InsertAtEnd) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertAt(2, 3);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.getAt(2), 3);
    EXPECT_EQ(list.getBack(), 3);
}

TEST_F(DoublyLinkedListTest, InsertAtInvalidIndex) {
    list.insertBack(1);
    EXPECT_THROW(list.insertAt(-1, 0), std::out_of_range);
    EXPECT_THROW(list.insertAt(2, 0), std::out_of_range);
}

// Deletion Tests
TEST_F(DoublyLinkedListTest, DeleteExistingElement) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    EXPECT_TRUE(list.deleteValue(2));
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.getAt(0), 1);
    EXPECT_EQ(list.getAt(1), 3);
}

TEST_F(DoublyLinkedListTest, DeleteFrontElement) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    EXPECT_TRUE(list.deleteValue(1));
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.getFront(), 2);
}

TEST_F(DoublyLinkedListTest, DeleteBackElement) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    EXPECT_TRUE(list.deleteValue(3));
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.getBack(), 2);
}

TEST_F(DoublyLinkedListTest, DeleteNonExistingElement) {
    list.insertBack(1);
    list.insertBack(2);
    
    EXPECT_FALSE(list.deleteValue(5));
    EXPECT_EQ(list.size(), 2);
}

TEST_F(DoublyLinkedListTest, DeleteFromEmptyList) {
    EXPECT_FALSE(list.deleteValue(1));
    EXPECT_EQ(list.size(), 0);
}

TEST_F(DoublyLinkedListTest, DeleteAtValidIndex) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    list.deleteAt(1); // Delete middle element
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.getAt(0), 1);
    EXPECT_EQ(list.getAt(1), 3);
}

TEST_F(DoublyLinkedListTest, DeleteAtFront) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    list.deleteAt(0);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.getFront(), 2);
}

TEST_F(DoublyLinkedListTest, DeleteAtBack) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    list.deleteAt(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.getBack(), 2);
}

TEST_F(DoublyLinkedListTest, DeleteAtInvalidIndex) {
    list.insertBack(1);
    EXPECT_THROW(list.deleteAt(-1), std::out_of_range);
    EXPECT_THROW(list.deleteAt(1), std::out_of_range);
}

// Search Tests
TEST_F(DoublyLinkedListTest, SearchExistingElement) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    EXPECT_TRUE(list.search(2));
    EXPECT_TRUE(list.search(1));
    EXPECT_TRUE(list.search(3));
}

TEST_F(DoublyLinkedListTest, SearchNonExistingElement) {
    list.insertBack(1);
    list.insertBack(2);
    
    EXPECT_FALSE(list.search(5));
}

TEST_F(DoublyLinkedListTest, SearchInEmptyList) {
    EXPECT_FALSE(list.search(1));
}

// Size and Empty Tests
TEST_F(DoublyLinkedListTest, EmptyListProperties) {
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, NonEmptyListProperties) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.isEmpty());
}

// Reverse Tests
TEST_F(DoublyLinkedListTest, ReverseList) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    list.reverse();
    
    EXPECT_EQ(list.getAt(0), 3);
    EXPECT_EQ(list.getAt(1), 2);
    EXPECT_EQ(list.getAt(2), 1);
    EXPECT_EQ(list.getFront(), 3);
    EXPECT_EQ(list.getBack(), 1);
}

TEST_F(DoublyLinkedListTest, ReverseSingleElement) {
    list.insertBack(42);
    list.reverse();
    
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.getFront(), 42);
    EXPECT_EQ(list.getBack(), 42);
}

TEST_F(DoublyLinkedListTest, ReverseEmptyList) {
    list.reverse();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

// Access Tests
TEST_F(DoublyLinkedListTest, GetFrontBack) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    EXPECT_EQ(list.getFront(), 1);
    EXPECT_EQ(list.getBack(), 3);
}

TEST_F(DoublyLinkedListTest, GetFrontBackSingleElement) {
    list.insertBack(42);
    
    EXPECT_EQ(list.getFront(), 42);
    EXPECT_EQ(list.getBack(), 42);
}

TEST_F(DoublyLinkedListTest, GetFrontBackEmptyList) {
    EXPECT_THROW(list.getFront(), std::runtime_error);
    EXPECT_THROW(list.getBack(), std::runtime_error);
}

TEST_F(DoublyLinkedListTest, GetAtValidIndex) {
    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);
    
    EXPECT_EQ(list.getAt(0), 10);
    EXPECT_EQ(list.getAt(1), 20);
    EXPECT_EQ(list.getAt(2), 30);
}

TEST_F(DoublyLinkedListTest, GetAtInvalidIndex) {
    list.insertBack(1);
    EXPECT_THROW(list.getAt(-1), std::out_of_range);
    EXPECT_THROW(list.getAt(1), std::out_of_range);
}

// Clear Tests
TEST_F(DoublyLinkedListTest, ClearNonEmptyList) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    list.clear();
    
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, ClearEmptyList) {
    list.clear();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

// Bidirectional Traversal Tests
TEST_F(DoublyLinkedListTest, ForwardTraversal) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    // Test that forward traversal works (would need capture of output)
    EXPECT_NO_THROW(list.displayForward());
}

TEST_F(DoublyLinkedListTest, BackwardTraversal) {
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    
    // Test that backward traversal works (would need capture of output)
    EXPECT_NO_THROW(list.displayBackward());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}