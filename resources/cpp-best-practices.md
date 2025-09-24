# C++ Best Practices for DSA Course

## Code Style Guidelines

### Naming Conventions
```cpp
// Variables and functions: camelCase
int arraySize;
void findMaxElement();

// Constants: UPPER_CASE
const int MAX_SIZE = 100;

// Classes: PascalCase
class LinkedList;
class BinaryTree;
```

### Function Structure
```cpp
/**
 * Brief description of what the function does
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * @param arr input array
 * @param size array size
 * @return description of return value
 */
int findMax(int arr[], int size) {
    // Input validation
    if (arr == nullptr || size <= 0) {
        // Handle error appropriately
        return -1; // or throw exception
    }
    
    // Main algorithm
    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    
    return maxVal;
}
```

## Memory Management

### Dynamic Allocation
```cpp
// Allocate
int* arr = new int[size];

// Use the array
// ...

// Always deallocate
delete[] arr;
arr = nullptr; // Prevent dangling pointer
```

### RAII Principle
```cpp
#include <memory>

// Prefer smart pointers
std::unique_ptr<int[]> arr(new int[size]);
// Automatic cleanup when out of scope
```

## Error Handling

### Input Validation
```cpp
bool isValidIndex(int index, int size) {
    return index >= 0 && index < size;
}

void insertElement(int arr[], int& size, int index, int element) {
    if (!isValidIndex(index, size + 1)) {
        std::cerr << "Error: Invalid index " << index << std::endl;
        return;
    }
    
    // Proceed with insertion
}
```

### Assertions for Debug Builds
```cpp
#include <cassert>

void binarySearch(int arr[], int size, int target) {
    assert(arr != nullptr);
    assert(size > 0);
    // Function implementation
}
```

## Algorithm Implementation Tips

### Loop Invariants
```cpp
// Maintain clear loop invariants
int linearSearch(int arr[], int size, int target) {
    // Loop invariant: target is not in arr[0..i-1]
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1; // target not found
}
```

### Boundary Conditions
```cpp
int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1; // Inclusive upper bound
    
    while (left <= right) { // Note: <= not <
        int mid = left + (right - left) / 2; // Avoid overflow
        
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
```

## Performance Considerations

### Choose Appropriate Data Types
```cpp
// Use size_t for array indices and sizes
void processArray(int arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        // Process arr[i]
    }
}

// Use const for read-only parameters
int findSum(const int arr[], size_t size) {
    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}
```

### Avoid Unnecessary Copying
```cpp
// Pass large objects by reference
void processVector(const std::vector<int>& vec) {
    // Read-only access, no copying
}

// Return by reference when appropriate
int& getElement(std::vector<int>& vec, size_t index) {
    return vec[index];
}
```

## Debugging Best Practices

### Use Meaningful Variable Names
```cpp
// Bad
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        if (a[i] > a[j]) {
            // swap
        }
    }
}

// Good
for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
    for (int compareIndex = currentIndex + 1; compareIndex < arraySize; compareIndex++) {
        if (array[currentIndex] > array[compareIndex]) {
            // swap elements
        }
    }
}
```

### Add Debug Output
```cpp
void bubbleSort(int arr[], int size) {
    #ifdef DEBUG
    std::cout << "Starting bubble sort with array size: " << size << std::endl;
    #endif
    
    for (int i = 0; i < size - 1; i++) {
        #ifdef DEBUG
        std::cout << "Pass " << i + 1 << ": ";
        printArray(arr, size);
        #endif
        
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
```

## Testing Your Code

### Unit Test Structure
```cpp
#include <cassert>

void testFindMax() {
    // Test normal case
    int arr1[] = {1, 5, 3, 9, 2};
    assert(findMax(arr1, 5) == 9);
    
    // Test single element
    int arr2[] = {42};
    assert(findMax(arr2, 1) == 42);
    
    // Test negative numbers
    int arr3[] = {-10, -5, -20, -1};
    assert(findMax(arr3, 4) == -1);
    
    std::cout << "All findMax tests passed!" << std::endl;
}
```

### Edge Cases to Consider
- Empty containers
- Single element containers
- Duplicate elements
- Extreme values (MIN_INT, MAX_INT)
- Invalid inputs (null pointers, negative sizes)

## Code Organization

### File Structure
```
assignment/
├── array_operations.cpp    // Implementation
├── array_operations.h      // Header (if needed)
└── test_operations.cpp     // Local tests
```

### Header Guards
```cpp
// array_operations.h
#ifndef ARRAY_OPERATIONS_H
#define ARRAY_OPERATIONS_H

// Function declarations
int findMax(int arr[], int size);
int findMin(int arr[], int size);

#endif // ARRAY_OPERATIONS_H
```

## Common Pitfalls to Avoid

1. **Array Bounds**: Always check indices
2. **Integer Overflow**: Be careful with large numbers
3. **Uninitialized Variables**: Initialize all variables
4. **Memory Leaks**: Match every `new` with `delete`
5. **Dangling Pointers**: Set pointers to `nullptr` after deletion
6. **Off-by-One Errors**: Carefully check loop conditions
7. **Modifying Read-Only Data**: Use `const` appropriately

Remember: Clean, readable code is just as important as correct algorithms!