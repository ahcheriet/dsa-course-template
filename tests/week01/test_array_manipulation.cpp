#include <gtest/gtest.h>
#include <stdexcept>

// Include the student's implementation
extern void insertElement(int arr[], int& size, int index, int element);
extern void deleteElement(int arr[], int& size, int index);
extern void rotateLeft(int arr[], int size, int k);
extern void rotateRight(int arr[], int size, int k);
extern int removeDuplicates(int arr[], int size);
extern void mergeSortedArrays(int arr1[], int size1, int arr2[], int size2);
extern int partition(int arr[], int low, int high);

class ArrayManipulationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test data
    }
};

// Insert Element Tests
TEST_F(ArrayManipulationTest, InsertAtBeginning) {
    int arr[10] = {2, 3, 4, 5};
    int size = 4;
    int expected[] = {1, 2, 3, 4, 5};
    
    insertElement(arr, size, 0, 1);
    
    EXPECT_EQ(size, 5);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, InsertAtEnd) {
    int arr[10] = {1, 2, 3, 4};
    int size = 4;
    int expected[] = {1, 2, 3, 4, 5};
    
    insertElement(arr, size, 4, 5);
    
    EXPECT_EQ(size, 5);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, InsertInMiddle) {
    int arr[10] = {1, 2, 4, 5};
    int size = 4;
    int expected[] = {1, 2, 3, 4, 5};
    
    insertElement(arr, size, 2, 3);
    
    EXPECT_EQ(size, 5);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, InsertInvalidIndex) {
    int arr[10] = {1, 2, 3};
    int size = 3;
    
    EXPECT_THROW(insertElement(arr, size, -1, 0), std::invalid_argument);
    EXPECT_THROW(insertElement(arr, size, 5, 0), std::invalid_argument);
}

// Delete Element Tests
TEST_F(ArrayManipulationTest, DeleteFromBeginning) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int expected[] = {2, 3, 4, 5};
    
    deleteElement(arr, size, 0);
    
    EXPECT_EQ(size, 4);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, DeleteFromEnd) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int expected[] = {1, 2, 3, 4};
    
    deleteElement(arr, size, 4);
    
    EXPECT_EQ(size, 4);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, DeleteFromMiddle) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int expected[] = {1, 2, 4, 5};
    
    deleteElement(arr, size, 2);
    
    EXPECT_EQ(size, 4);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, DeleteInvalidIndex) {
    int arr[] = {1, 2, 3};
    int size = 3;
    
    EXPECT_THROW(deleteElement(arr, size, -1), std::invalid_argument);
    EXPECT_THROW(deleteElement(arr, size, 3), std::invalid_argument);
    
    int emptySize = 0;
    EXPECT_THROW(deleteElement(arr, emptySize, 0), std::invalid_argument);
}

// Rotate Left Tests
TEST_F(ArrayManipulationTest, RotateLeftBasic) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int expected[] = {3, 4, 5, 1, 2};
    
    rotateLeft(arr, size, 2);
    
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, RotateLeftByOne) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int expected[] = {2, 3, 4, 5, 1};
    
    rotateLeft(arr, size, 1);
    
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, RotateLeftBySize) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int expected[] = {1, 2, 3, 4, 5};  // Should be same as original
    
    rotateLeft(arr, size, 5);
    
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, RotateLeftLargeK) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int expected[] = {3, 4, 5, 1, 2};  // k=7 should be same as k=2
    
    rotateLeft(arr, size, 7);
    
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, RotateLeftZero) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int expected[] = {1, 2, 3, 4, 5};  // Should remain unchanged
    
    rotateLeft(arr, size, 0);
    
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Rotate Right Tests
TEST_F(ArrayManipulationTest, RotateRightBasic) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int expected[] = {4, 5, 1, 2, 3};
    
    rotateRight(arr, size, 2);
    
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, RotateRightByOne) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int expected[] = {5, 1, 2, 3, 4};
    
    rotateRight(arr, size, 1);
    
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Remove Duplicates Tests
TEST_F(ArrayManipulationTest, RemoveDuplicatesBasic) {
    int arr[] = {1, 1, 2, 2, 3, 3, 4};
    int size = 7;
    int expected[] = {1, 2, 3, 4};
    
    int newSize = removeDuplicates(arr, size);
    
    EXPECT_EQ(newSize, 4);
    for (int i = 0; i < newSize; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, RemoveDuplicatesNoDuplicates) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    
    int newSize = removeDuplicates(arr, size);
    
    EXPECT_EQ(newSize, 5);
    for (int i = 0; i < newSize; i++) {
        EXPECT_EQ(arr[i], i + 1);
    }
}

TEST_F(ArrayManipulationTest, RemoveDuplicatesAllSame) {
    int arr[] = {5, 5, 5, 5, 5};
    int size = 5;
    
    int newSize = removeDuplicates(arr, size);
    
    EXPECT_EQ(newSize, 1);
    EXPECT_EQ(arr[0], 5);
}

// Merge Sorted Arrays Tests
TEST_F(ArrayManipulationTest, MergeSortedArraysBasic) {
    int arr1[10] = {1, 3, 5, 7, 0, 0, 0, 0}; // Extra space for arr2
    int arr2[] = {2, 4, 6, 8};
    int size1 = 4;
    int size2 = 4;
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    mergeSortedArrays(arr1, size1, arr2, size2);
    
    for (int i = 0; i < size1 + size2; i++) {
        EXPECT_EQ(arr1[i], expected[i]);
    }
}

TEST_F(ArrayManipulationTest, MergeSortedArraysOneEmpty) {
    int arr1[5] = {0, 0, 0, 0, 0}; // All space for arr2
    int arr2[] = {1, 2, 3, 4, 5};
    int size1 = 0;
    int size2 = 5;
    int expected[] = {1, 2, 3, 4, 5};
    
    mergeSortedArrays(arr1, size1, arr2, size2);
    
    for (int i = 0; i < size2; i++) {
        EXPECT_EQ(arr1[i], expected[i]);
    }
}

// Partition Tests
TEST_F(ArrayManipulationTest, PartitionBasic) {
    int arr[] = {3, 6, 8, 10, 1, 2, 1};
    int size = 7;
    int low = 0;
    int high = size - 1;
    
    int pivotIndex = partition(arr, low, high);
    
    // Check that pivot is in correct position
    EXPECT_GE(pivotIndex, 0);
    EXPECT_LT(pivotIndex, size);
    
    // Check that all elements left of pivot are <= pivot
    // and all elements right of pivot are > pivot
    int pivotValue = arr[pivotIndex];
    for (int i = 0; i < pivotIndex; i++) {
        EXPECT_LE(arr[i], pivotValue);
    }
    for (int i = pivotIndex + 1; i < size; i++) {
        EXPECT_GT(arr[i], pivotValue);
    }
}

// Edge cases
TEST_F(ArrayManipulationTest, SingleElementOperations) {
    int arr[5] = {42};
    int size = 1;
    
    // Insert at beginning
    insertElement(arr, size, 0, 1);
    EXPECT_EQ(size, 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 42);
    
    // Delete from beginning
    deleteElement(arr, size, 0);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(arr[0], 42);
    
    // Rotate single element
    rotateLeft(arr, size, 3);
    EXPECT_EQ(arr[0], 42);  // Should remain unchanged
}

TEST_F(ArrayManipulationTest, EmptyArrayOperations) {
    int arr[5] = {};
    int size = 0;
    
    // Insert into empty array
    insertElement(arr, size, 0, 42);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(arr[0], 42);
    
    // Test removeDuplicates with empty array
    int emptySize = 0;
    EXPECT_EQ(removeDuplicates(arr, emptySize), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}