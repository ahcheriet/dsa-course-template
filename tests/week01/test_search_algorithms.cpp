#include <gtest/gtest.h>

// Include the student's implementation
extern int linearSearch(int arr[], int size, int target);
extern int binarySearch(int arr[], int size, int target);
extern int binarySearchRecursive(int arr[], int left, int right, int target);
extern int findFirstOccurrence(int arr[], int size, int target);
extern int findLastOccurrence(int arr[], int size, int target);
extern int findPeakElement(int arr[], int size);

class SearchAlgorithmsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test data
    }
};

// Linear Search Tests
TEST_F(SearchAlgorithmsTest, LinearSearchFoundAtBeginning) {
    int arr[] = {1, 5, 3, 9, 2};
    int size = 5;
    EXPECT_EQ(linearSearch(arr, size, 1), 0);
}

TEST_F(SearchAlgorithmsTest, LinearSearchFoundAtEnd) {
    int arr[] = {1, 5, 3, 9, 2};
    int size = 5;
    EXPECT_EQ(linearSearch(arr, size, 2), 4);
}

TEST_F(SearchAlgorithmsTest, LinearSearchFoundInMiddle) {
    int arr[] = {1, 5, 3, 9, 2};
    int size = 5;
    EXPECT_EQ(linearSearch(arr, size, 3), 2);
}

TEST_F(SearchAlgorithmsTest, LinearSearchNotFound) {
    int arr[] = {1, 5, 3, 9, 2};
    int size = 5;
    EXPECT_EQ(linearSearch(arr, size, 7), -1);
}

TEST_F(SearchAlgorithmsTest, LinearSearchSingleElement) {
    int arr[] = {42};
    int size = 1;
    EXPECT_EQ(linearSearch(arr, size, 42), 0);
    EXPECT_EQ(linearSearch(arr, size, 24), -1);
}

// Binary Search Tests (assuming sorted arrays)
TEST_F(SearchAlgorithmsTest, BinarySearchFoundAtBeginning) {
    int arr[] = {1, 3, 5, 7, 9};
    int size = 5;
    EXPECT_EQ(binarySearch(arr, size, 1), 0);
}

TEST_F(SearchAlgorithmsTest, BinarySearchFoundAtEnd) {
    int arr[] = {1, 3, 5, 7, 9};
    int size = 5;
    EXPECT_EQ(binarySearch(arr, size, 9), 4);
}

TEST_F(SearchAlgorithmsTest, BinarySearchFoundInMiddle) {
    int arr[] = {1, 3, 5, 7, 9};
    int size = 5;
    EXPECT_EQ(binarySearch(arr, size, 5), 2);
}

TEST_F(SearchAlgorithmsTest, BinarySearchNotFound) {
    int arr[] = {1, 3, 5, 7, 9};
    int size = 5;
    EXPECT_EQ(binarySearch(arr, size, 4), -1);
    EXPECT_EQ(binarySearch(arr, size, 10), -1);
    EXPECT_EQ(binarySearch(arr, size, 0), -1);
}

TEST_F(SearchAlgorithmsTest, BinarySearchSingleElement) {
    int arr[] = {42};
    int size = 1;
    EXPECT_EQ(binarySearch(arr, size, 42), 0);
    EXPECT_EQ(binarySearch(arr, size, 24), -1);
}

TEST_F(SearchAlgorithmsTest, BinarySearchLargeArray) {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int size = 10;
    EXPECT_EQ(binarySearch(arr, size, 14), 6);
    EXPECT_EQ(binarySearch(arr, size, 15), -1);
}

// Binary Search Recursive Tests
TEST_F(SearchAlgorithmsTest, BinarySearchRecursiveBasicTest) {
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int size = 7;
    EXPECT_EQ(binarySearchRecursive(arr, 0, size - 1, 7), 3);
    EXPECT_EQ(binarySearchRecursive(arr, 0, size - 1, 1), 0);
    EXPECT_EQ(binarySearchRecursive(arr, 0, size - 1, 13), 6);
}

TEST_F(SearchAlgorithmsTest, BinarySearchRecursiveNotFound) {
    int arr[] = {1, 3, 5, 7, 9};
    int size = 5;
    EXPECT_EQ(binarySearchRecursive(arr, 0, size - 1, 4), -1);
    EXPECT_EQ(binarySearchRecursive(arr, 0, size - 1, 0), -1);
    EXPECT_EQ(binarySearchRecursive(arr, 0, size - 1, 10), -1);
}

// First Occurrence Tests
TEST_F(SearchAlgorithmsTest, FindFirstOccurrenceBasicTest) {
    int arr[] = {1, 2, 2, 2, 3, 4, 4, 5};
    int size = 8;
    EXPECT_EQ(findFirstOccurrence(arr, size, 2), 1);
    EXPECT_EQ(findFirstOccurrence(arr, size, 4), 5);
    EXPECT_EQ(findFirstOccurrence(arr, size, 1), 0);
    EXPECT_EQ(findFirstOccurrence(arr, size, 5), 7);
}

TEST_F(SearchAlgorithmsTest, FindFirstOccurrenceNotFound) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    EXPECT_EQ(findFirstOccurrence(arr, size, 6), -1);
    EXPECT_EQ(findFirstOccurrence(arr, size, 0), -1);
}

// Last Occurrence Tests
TEST_F(SearchAlgorithmsTest, FindLastOccurrenceBasicTest) {
    int arr[] = {1, 2, 2, 2, 3, 4, 4, 5};
    int size = 8;
    EXPECT_EQ(findLastOccurrence(arr, size, 2), 3);
    EXPECT_EQ(findLastOccurrence(arr, size, 4), 6);
    EXPECT_EQ(findLastOccurrence(arr, size, 1), 0);
    EXPECT_EQ(findLastOccurrence(arr, size, 5), 7);
}

TEST_F(SearchAlgorithmsTest, FindLastOccurrenceNotFound) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    EXPECT_EQ(findLastOccurrence(arr, size, 6), -1);
    EXPECT_EQ(findLastOccurrence(arr, size, 0), -1);
}

// Peak Element Tests
TEST_F(SearchAlgorithmsTest, FindPeakElementBasicTest) {
    int arr[] = {1, 3, 20, 4, 1, 0};
    int size = 6;
    int peak = findPeakElement(arr, size);
    EXPECT_EQ(peak, 2); // Index of element 20
}

TEST_F(SearchAlgorithmsTest, FindPeakElementAtBeginning) {
    int arr[] = {5, 4, 3, 2, 1};
    int size = 5;
    int peak = findPeakElement(arr, size);
    EXPECT_EQ(peak, 0); // First element is peak
}

TEST_F(SearchAlgorithmsTest, FindPeakElementAtEnd) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    int peak = findPeakElement(arr, size);
    EXPECT_EQ(peak, 4); // Last element is peak
}

TEST_F(SearchAlgorithmsTest, FindPeakElementSingleElement) {
    int arr[] = {42};
    int size = 1;
    EXPECT_EQ(findPeakElement(arr, size), 0);
}

// Edge cases
TEST_F(SearchAlgorithmsTest, EmptyArraySearch) {
    int* arr = nullptr;
    int size = 0;
    EXPECT_EQ(linearSearch(arr, size, 5), -1);
    EXPECT_EQ(binarySearch(arr, size, 5), -1);
}

TEST_F(SearchAlgorithmsTest, DuplicateElementsTest) {
    int arr[] = {1, 1, 1, 1, 1};
    int size = 5;
    EXPECT_EQ(findFirstOccurrence(arr, size, 1), 0);
    EXPECT_EQ(findLastOccurrence(arr, size, 1), 4);
    EXPECT_GE(linearSearch(arr, size, 1), 0);
    EXPECT_GE(binarySearch(arr, size, 1), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}