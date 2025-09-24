#include <iostream>
#include <algorithm>
#include <climits>
#include <stdexcept>

/**
 * Find the maximum element in an array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int findMax(int arr[], int size) {
    if (size <= 0) {
        throw std::invalid_argument("Array size must be positive");
    }
    
    int maxElement = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxElement) {
            maxElement = arr[i];
        }
    }
    return maxElement;
}

/**
 * Find the minimum element in an array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int findMin(int arr[], int size) {
    if (size <= 0) {
        throw std::invalid_argument("Array size must be positive");
    }
    
    int minElement = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minElement) {
            minElement = arr[i];
        }
    }
    return minElement;
}

/**
 * Calculate the sum of all elements in an array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
long long calculateSum(int arr[], int size) {
    if (size <= 0) {
        return 0;
    }
    
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

/**
 * Calculate the average of all elements in an array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
double calculateAverage(int arr[], int size) {
    if (size <= 0) {
        throw std::invalid_argument("Array size must be positive");
    }
    
    long long sum = calculateSum(arr, size);
    return static_cast<double>(sum) / size;
}

/**
 * Reverse the array in-place
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
void reverseArray(int arr[], int size) {
    if (size <= 1) {
        return;
    }
    
    int left = 0;
    int right = size - 1;
    
    while (left < right) {
        std::swap(arr[left], arr[right]);
        left++;
        right--;
    }
}

/**
 * Check if array is sorted in ascending order
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
bool isSorted(int arr[], int size) {
    if (size <= 1) {
        return true;
    }
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i-1]) {
            return false;
        }
    }
    return true;
}

/**
 * Find the second largest element in an array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int findSecondLargest(int arr[], int size) {
    if (size < 2) {
        throw std::invalid_argument("Array must have at least 2 elements");
    }
    
    int largest = INT_MIN;
    int secondLargest = INT_MIN;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] > largest) {
            secondLargest = largest;
            largest = arr[i];
        } else if (arr[i] > secondLargest && arr[i] != largest) {
            secondLargest = arr[i];
        }
    }
    
    if (secondLargest == INT_MIN) {
        throw std::runtime_error("No second largest element found (all elements are the same)");
    }
    
    return secondLargest;
}

/**
 * Count occurrences of a specific element in the array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int countOccurrences(int arr[], int size, int target) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            count++;
        }
    }
    return count;
}