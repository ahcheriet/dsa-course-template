#include <iostream>
#include <algorithm>

/**
 * Linear search - search for target element in array
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * Returns: index of target element, -1 if not found
 */
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

/**
 * Binary search - search for target element in sorted array
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 * Returns: index of target element, -1 if not found
 * Prerequisite: Array must be sorted
 */
int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

/**
 * Binary search recursive implementation
 * Time Complexity: O(log n)
 * Space Complexity: O(log n) due to recursion stack
 */
int binarySearchRecursive(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, mid + 1, right, target);
    } else {
        return binarySearchRecursive(arr, left, mid - 1, target);
    }
}

/**
 * Find the first occurrence of target in sorted array
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
int findFirstOccurrence(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1; // Continue searching in left half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

/**
 * Find the last occurrence of target in sorted array
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
int findLastOccurrence(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1; // Continue searching in right half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

/**
 * Find peak element in array (element greater than its neighbors)
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
int findPeakElement(int arr[], int size) {
    if (size == 1) return 0;
    
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Check if mid is a peak
        if ((mid == 0 || arr[mid] >= arr[mid - 1]) && 
            (mid == size - 1 || arr[mid] >= arr[mid + 1])) {
            return mid;
        }
        
        // If left neighbor is greater, peak must be in left half
        if (mid > 0 && arr[mid - 1] > arr[mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}