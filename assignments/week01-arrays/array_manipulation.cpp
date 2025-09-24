#include <iostream>
#include <algorithm>
#include <stdexcept>

/**
 * Insert element at specific index in array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * Note: Assumes array has enough capacity
 */
void insertElement(int arr[], int& size, int index, int element) {
    if (index < 0 || index > size) {
        throw std::invalid_argument("Index out of bounds");
    }
    
    // Shift elements to the right
    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    
    // Insert new element
    arr[index] = element;
    size++;
}

/**
 * Delete element at specific index from array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
void deleteElement(int arr[], int& size, int index) {
    if (size <= 0) {
        throw std::invalid_argument("Array is empty");
    }
    if (index < 0 || index >= size) {
        throw std::invalid_argument("Index out of bounds");
    }
    
    // Shift elements to the left
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    
    size--;
}

/**
 * Rotate array left by k positions
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * Example: [1,2,3,4,5] rotated left by 2 becomes [3,4,5,1,2]
 */
void rotateLeft(int arr[], int size, int k) {
    if (size <= 1) return;
    
    k = k % size; // Handle case where k > size
    if (k == 0) return;
    
    // Reverse the entire array
    std::reverse(arr, arr + size);
    
    // Reverse the first (size - k) elements
    std::reverse(arr, arr + size - k);
    
    // Reverse the last k elements
    std::reverse(arr + size - k, arr + size);
}

/**
 * Rotate array right by k positions
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * Example: [1,2,3,4,5] rotated right by 2 becomes [4,5,1,2,3]
 */
void rotateRight(int arr[], int size, int k) {
    if (size <= 1) return;
    
    k = k % size; // Handle case where k > size
    if (k == 0) return;
    
    // Reverse the entire array
    std::reverse(arr, arr + size);
    
    // Reverse the first k elements
    std::reverse(arr, arr + k);
    
    // Reverse the remaining elements
    std::reverse(arr + k, arr + size);
}

/**
 * Remove duplicates from sorted array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * Returns: new size of array after removing duplicates
 */
int removeDuplicates(int arr[], int size) {
    if (size <= 1) return size;
    
    int writeIndex = 1;
    
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[i - 1]) {
            arr[writeIndex] = arr[i];
            writeIndex++;
        }
    }
    
    return writeIndex;
}

/**
 * Merge two sorted arrays
 * Time Complexity: O(m + n)
 * Space Complexity: O(1) - modifies arr1 in place
 * Assumes arr1 has enough space to hold both arrays
 */
void mergeSortedArrays(int arr1[], int size1, int arr2[], int size2) {
    int i = size1 - 1; // Last element in arr1
    int j = size2 - 1; // Last element in arr2
    int k = size1 + size2 - 1; // Last position in merged array
    
    // Merge from the end
    while (i >= 0 && j >= 0) {
        if (arr1[i] > arr2[j]) {
            arr1[k] = arr1[i];
            i--;
        } else {
            arr1[k] = arr2[j];
            j--;
        }
        k--;
    }
    
    // Copy remaining elements from arr2
    while (j >= 0) {
        arr1[k] = arr2[j];
        j--;
        k--;
    }
}

/**
 * Partition array around a pivot (used in quicksort)
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * Returns: index of pivot after partitioning
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = low - 1; // Index of smaller element
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}