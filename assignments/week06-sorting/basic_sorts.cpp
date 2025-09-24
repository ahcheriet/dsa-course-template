// Basic Sorting Algorithms Implementation
// Week 6: Sorting Assignment

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

/**
 * Implementation of basic sorting algorithms
 * Students: Implement the TODO sections marked below
 */

class BasicSorts {
public:
    /**
     * Bubble Sort - Simple comparison-based sorting algorithm
     * Time Complexity: O(n²), Space Complexity: O(1)
     * Stable: Yes, In-place: Yes
     */
    static void bubbleSort(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    /**
     * Selection Sort - Find minimum and place at beginning
     * Time Complexity: O(n²), Space Complexity: O(1)
     * Stable: No, In-place: Yes
     */
    static void selectionSort(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                std::swap(arr[i], arr[minIdx]);
            }
        }
    }

    /**
     * Insertion Sort - Build sorted array one element at a time
     * Time Complexity: O(n²), Space Complexity: O(1)
     * Stable: Yes, In-place: Yes
     */
    static void insertionSort(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    /**
     * Demonstration function to show all sorting algorithms
     */
    static void demonstrateBasicSorts() {
        std::vector<int> original = {64, 34, 25, 12, 22, 11, 90};
        
        std::cout << "Original array: ";
        for (int x : original) std::cout << x << " ";
        std::cout << std::endl;
        
        // Test bubble sort
        auto bubbleData = original;
        BasicSorts::bubbleSort(bubbleData);
        std::cout << "Bubble Sort: ";
        for (int x : bubbleData) std::cout << x << " ";
        std::cout << std::endl;
        
        // Test selection sort
        auto selectionData = original;
        BasicSorts::selectionSort(selectionData);
        std::cout << "Selection Sort: ";
        for (int x : selectionData) std::cout << x << " ";
        std::cout << std::endl;
        
        // Test insertion sort
        auto insertionData = original;
        BasicSorts::insertionSort(insertionData);
        std::cout << "Insertion Sort: ";
        for (int x : insertionData) std::cout << x << " ";
        std::cout << std::endl;
    }

    /**
     * Performance comparison and analysis tools
     */
    template<typename T>
    static void compareSorts(std::vector<T> data) {
        std::cout << "\n=== Sorting Algorithm Performance Comparison ===" << std::endl;
        std::cout << "Array size: " << data.size() << std::endl;
        
        auto bubbleData = data;
        auto selectionData = data;
        auto insertionData = data;
        
        // Time measurements would go here in a real implementation
        bubbleSort(bubbleData);
        std::cout << "Bubble Sort completed" << std::endl;
        
        selectionSort(selectionData);
        std::cout << "Selection Sort completed" << std::endl;
        
        insertionSort(insertionData);
        std::cout << "Insertion Sort completed" << std::endl;
    }

    // TODO: Students should implement additional utility functions:
    // - generateWorstCase(int n) - creates reverse sorted array
    // - generateBestCase(int n) - creates already sorted array  
    // - generateRandomCase(int n) - creates randomly shuffled array
    // - isSorted(vector) - checks if array is sorted
    // - Advanced sorting algorithms (merge sort, quick sort, heap sort)
    // - Timing mechanisms for actual performance measurement
    // - Stability analysis and comparison tools
};

// Students can add a main function here for testing their implementations
// int main() {
//     BasicSorts::demonstrateBasicSorts();
//     return 0;
// }