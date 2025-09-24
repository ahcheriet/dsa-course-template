// Week 6: Basic Sorting Algorithms - Test Suite
// Students: Implement the sorting algorithms in basic_sorts.cpp

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>
#include "../../assignments/week06-sorting/basic_sorts.cpp"

// Test fixture for sorting algorithms
class SortingTest : public ::testing::Test {
protected:
    void SetUp() override {
        testData = {64, 34, 25, 12, 22, 11, 90};
        sortedData = {11, 12, 22, 25, 34, 64, 90};
        emptyData = {};
        singleElement = {42};
        duplicates = {5, 2, 8, 2, 9, 1, 5, 4};
        reverseSorted = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    }

    // Helper function to verify sorting correctness
    void verifySort(std::vector<int> data, void (*sortFunc)(std::vector<int>&)) {
        std::vector<int> original = data;
        sortFunc(data);
        
        // Check if sorted using standard library
        EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
        
        // Check if all elements are preserved
        std::sort(original.begin(), original.end());
        EXPECT_EQ(data, original);
    }

    std::vector<int> testData;
    std::vector<int> sortedData;
    std::vector<int> emptyData;
    std::vector<int> singleElement;
    std::vector<int> duplicates;
    std::vector<int> reverseSorted;
};

// Bubble Sort Tests
TEST_F(SortingTest, BubbleSortBasic) {
    verifySort(testData, BasicSorts::bubbleSort);
}

TEST_F(SortingTest, BubbleSortEmpty) {
    verifySort(emptyData, BasicSorts::bubbleSort);
}

TEST_F(SortingTest, BubbleSortSingleElement) {
    verifySort(singleElement, BasicSorts::bubbleSort);
}

TEST_F(SortingTest, BubbleSortDuplicates) {
    verifySort(duplicates, BasicSorts::bubbleSort);
}

TEST_F(SortingTest, BubbleSortReverseSorted) {
    verifySort(reverseSorted, BasicSorts::bubbleSort);
}

TEST_F(SortingTest, BubbleSortAlreadySorted) {
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    BasicSorts::bubbleSort(sorted);
    EXPECT_TRUE(std::is_sorted(sorted.begin(), sorted.end()));
}

// Selection Sort Tests
TEST_F(SortingTest, SelectionSortBasic) {
    verifySort(testData, BasicSorts::selectionSort);
}

TEST_F(SortingTest, SelectionSortEmpty) {
    verifySort(emptyData, BasicSorts::selectionSort);
}

TEST_F(SortingTest, SelectionSortSingleElement) {
    verifySort(singleElement, BasicSorts::selectionSort);
}

TEST_F(SortingTest, SelectionSortDuplicates) {
    verifySort(duplicates, BasicSorts::selectionSort);
}

TEST_F(SortingTest, SelectionSortReverseSorted) {
    verifySort(reverseSorted, BasicSorts::selectionSort);
}

// Insertion Sort Tests
TEST_F(SortingTest, InsertionSortBasic) {
    verifySort(testData, BasicSorts::insertionSort);
}

TEST_F(SortingTest, InsertionSortEmpty) {
    verifySort(emptyData, BasicSorts::insertionSort);
}

TEST_F(SortingTest, InsertionSortSingleElement) {
    verifySort(singleElement, BasicSorts::insertionSort);
}

TEST_F(SortingTest, InsertionSortDuplicates) {
    verifySort(duplicates, BasicSorts::insertionSort);
}

TEST_F(SortingTest, InsertionSortReverseSorted) {
    verifySort(reverseSorted, BasicSorts::insertionSort);
}

// Performance Tests (Large datasets)
TEST_F(SortingTest, LargeDatasetBubbleSort) {
    std::vector<int> large(100);
    std::iota(large.rbegin(), large.rend(), 1); // Reverse sorted
    verifySort(large, BasicSorts::bubbleSort);
}

TEST_F(SortingTest, LargeDatasetSelectionSort) {
    std::vector<int> large(100);
    std::iota(large.rbegin(), large.rend(), 1); // Reverse sorted
    verifySort(large, BasicSorts::selectionSort);
}

TEST_F(SortingTest, LargeDatasetInsertionSort) {
    std::vector<int> large(100);
    std::iota(large.rbegin(), large.rend(), 1); // Reverse sorted
    verifySort(large, BasicSorts::insertionSort);
}

// Stability Tests (for stable sorts)
TEST_F(SortingTest, BubbleSortStability) {
    // This is a conceptual test - actual stability testing would require pairs
    std::vector<int> stableTest = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    BasicSorts::bubbleSort(stableTest);
    EXPECT_TRUE(std::is_sorted(stableTest.begin(), stableTest.end()));
}

TEST_F(SortingTest, InsertionSortStability) {
    std::vector<int> stableTest = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    BasicSorts::insertionSort(stableTest);
    EXPECT_TRUE(std::is_sorted(stableTest.begin(), stableTest.end()));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}