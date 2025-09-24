#include <gtest/gtest.h>
#include <stdexcept>

// Include the student's implementation
extern int findMax(int arr[], int size);
extern int findMin(int arr[], int size);
extern long long calculateSum(int arr[], int size);
extern double calculateAverage(int arr[], int size);
extern void reverseArray(int arr[], int size);
extern bool isSorted(int arr[], int size);
extern int findSecondLargest(int arr[], int size);
extern int countOccurrences(int arr[], int size, int target);

class ArrayOperationsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test data
    }
    
    void TearDown() override {
        // Clean up
    }
};

// Tests for findMax
TEST_F(ArrayOperationsTest, FindMaxBasicTest) {
    int arr[] = {1, 5, 3, 9, 2};
    int size = 5;
    EXPECT_EQ(findMax(arr, size), 9);
}

TEST_F(ArrayOperationsTest, FindMaxSingleElement) {
    int arr[] = {42};
    int size = 1;
    EXPECT_EQ(findMax(arr, size), 42);
}

TEST_F(ArrayOperationsTest, FindMaxNegativeNumbers) {
    int arr[] = {-10, -5, -20, -1};
    int size = 4;
    EXPECT_EQ(findMax(arr, size), -1);
}

TEST_F(ArrayOperationsTest, FindMaxEmptyArray) {
    int* arr = nullptr;
    int size = 0;
    EXPECT_THROW(findMax(arr, size), std::invalid_argument);
}

// Tests for findMin
TEST_F(ArrayOperationsTest, FindMinBasicTest) {
    int arr[] = {1, 5, 3, 9, 2};
    int size = 5;
    EXPECT_EQ(findMin(arr, size), 1);
}

TEST_F(ArrayOperationsTest, FindMinSingleElement) {
    int arr[] = {42};
    int size = 1;
    EXPECT_EQ(findMin(arr, size), 42);
}

TEST_F(ArrayOperationsTest, FindMinNegativeNumbers) {
    int arr[] = {-10, -5, -20, -1};
    int size = 4;
    EXPECT_EQ(findMin(arr, size), -20);
}

TEST_F(ArrayOperationsTest, FindMinEmptyArray) {
    int* arr = nullptr;
    int size = 0;
    EXPECT_THROW(findMin(arr, size), std::invalid_argument);
}

// Tests for calculateSum
TEST_F(ArrayOperationsTest, CalculateSumBasicTest) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    EXPECT_EQ(calculateSum(arr, size), 15);
}

TEST_F(ArrayOperationsTest, CalculateSumZeroSum) {
    int arr[] = {-1, 1, -2, 2};
    int size = 4;
    EXPECT_EQ(calculateSum(arr, size), 0);
}

TEST_F(ArrayOperationsTest, CalculateSumEmptyArray) {
    int* arr = nullptr;
    int size = 0;
    EXPECT_EQ(calculateSum(arr, size), 0);
}

// Tests for calculateAverage
TEST_F(ArrayOperationsTest, CalculateAverageBasicTest) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    EXPECT_DOUBLE_EQ(calculateAverage(arr, size), 3.0);
}

TEST_F(ArrayOperationsTest, CalculateAverageEmptyArray) {
    int* arr = nullptr;
    int size = 0;
    EXPECT_THROW(calculateAverage(arr, size), std::invalid_argument);
}

// Tests for reverseArray
TEST_F(ArrayOperationsTest, ReverseArrayBasicTest) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {5, 4, 3, 2, 1};
    int size = 5;
    
    reverseArray(arr, size);
    
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayOperationsTest, ReverseArrayEvenSize) {
    int arr[] = {1, 2, 3, 4};
    int expected[] = {4, 3, 2, 1};
    int size = 4;
    
    reverseArray(arr, size);
    
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST_F(ArrayOperationsTest, ReverseArraySingleElement) {
    int arr[] = {42};
    int expected[] = {42};
    int size = 1;
    
    reverseArray(arr, size);
    
    EXPECT_EQ(arr[0], expected[0]);
}

// Tests for isSorted
TEST_F(ArrayOperationsTest, IsSortedAscending) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    EXPECT_TRUE(isSorted(arr, size));
}

TEST_F(ArrayOperationsTest, IsSortedNotSorted) {
    int arr[] = {1, 3, 2, 4, 5};
    int size = 5;
    EXPECT_FALSE(isSorted(arr, size));
}

TEST_F(ArrayOperationsTest, IsSortedWithDuplicates) {
    int arr[] = {1, 2, 2, 3, 3};
    int size = 5;
    EXPECT_TRUE(isSorted(arr, size));
}

TEST_F(ArrayOperationsTest, IsSortedSingleElement) {
    int arr[] = {42};
    int size = 1;
    EXPECT_TRUE(isSorted(arr, size));
}

// Tests for findSecondLargest
TEST_F(ArrayOperationsTest, FindSecondLargestBasicTest) {
    int arr[] = {1, 5, 3, 9, 2};
    int size = 5;
    EXPECT_EQ(findSecondLargest(arr, size), 5);
}

TEST_F(ArrayOperationsTest, FindSecondLargestWithDuplicates) {
    int arr[] = {1, 9, 3, 9, 2};
    int size = 5;
    EXPECT_EQ(findSecondLargest(arr, size), 3);
}

TEST_F(ArrayOperationsTest, FindSecondLargestAllSame) {
    int arr[] = {5, 5, 5, 5};
    int size = 4;
    EXPECT_THROW(findSecondLargest(arr, size), std::runtime_error);
}

TEST_F(ArrayOperationsTest, FindSecondLargestTooSmall) {
    int arr[] = {42};
    int size = 1;
    EXPECT_THROW(findSecondLargest(arr, size), std::invalid_argument);
}

// Tests for countOccurrences
TEST_F(ArrayOperationsTest, CountOccurrencesBasicTest) {
    int arr[] = {1, 2, 3, 2, 2, 4};
    int size = 6;
    EXPECT_EQ(countOccurrences(arr, size, 2), 3);
}

TEST_F(ArrayOperationsTest, CountOccurrencesNotFound) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = 5;
    EXPECT_EQ(countOccurrences(arr, size, 6), 0);
}

TEST_F(ArrayOperationsTest, CountOccurrencesAllSame) {
    int arr[] = {7, 7, 7, 7};
    int size = 4;
    EXPECT_EQ(countOccurrences(arr, size, 7), 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}