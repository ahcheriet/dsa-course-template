# Week 1: Arrays and Basic Operations

## Learning Objectives
- Understand array data structure fundamentals
- Implement basic array operations and advanced manipulations
- Practice time and space complexity analysis
- Master searching algorithms and their applications

## Assignment Tasks

### Task 1: Array Operations (30 points)
Implement the following functions in `array_operations.cpp`:

1. **findMax(arr, size)** - Find the maximum element in an array
2. **findMin(arr, size)** - Find the minimum element in an array
3. **calculateSum(arr, size)** - Calculate the sum of all elements
4. **calculateAverage(arr, size)** - Calculate the average of all elements
5. **reverseArray(arr, size)** - Reverse the array in-place
6. **isSorted(arr, size)** - Check if array is sorted in ascending order
7. **findSecondLargest(arr, size)** - Find the second largest element
8. **countOccurrences(arr, size, target)** - Count occurrences of a specific element

### Task 2: Search Algorithms (40 points)
Implement search algorithms in `search_algorithms.cpp`:

1. **linearSearch(arr, size, target)** - Linear search implementation
2. **binarySearch(arr, size, target)** - Iterative binary search (assume sorted array)
3. **binarySearchRecursive(arr, left, right, target)** - Recursive binary search
4. **findFirstOccurrence(arr, size, target)** - Find first occurrence in sorted array
5. **findLastOccurrence(arr, size, target)** - Find last occurrence in sorted array
6. **findPeakElement(arr, size)** - Find peak element using binary search

### Task 3: Array Manipulation (30 points)
Implement array manipulation functions in `array_manipulation.cpp`:

1. **insertElement(arr, size, index, element)** - Insert element at specific index
2. **deleteElement(arr, size, index)** - Delete element at specific index
3. **rotateLeft(arr, size, k)** - Rotate array left by k positions
4. **rotateRight(arr, size, k)** - Rotate array right by k positions
5. **removeDuplicates(arr, size)** - Remove duplicates from sorted array
6. **mergeSortedArrays(arr1, size1, arr2, size2)** - Merge two sorted arrays
7. **partition(arr, low, high)** - Partition array around pivot (for quicksort)

## Advanced Features
- **Error Handling**: All functions include proper exception handling for invalid inputs
- **Edge Cases**: Comprehensive handling of empty arrays, single elements, and boundary conditions
- **Optimal Algorithms**: Implementations use optimal time and space complexities
- **Memory Safety**: All array operations are bounds-checked

## Time Complexity Requirements
- Basic operations (find, sum, reverse): O(n)
- Binary search operations: O(log n)
- Array manipulations: O(n)
- Merge operations: O(m + n)

## Requirements
- Use C++17 standard
- Include proper error handling with exceptions
- Add time complexity comments for each function
- Follow the provided function signatures
- Write clean, well-documented code
- Handle all edge cases appropriately

## Testing
Your code will be tested against multiple test cases including:
- Empty arrays and null pointers
- Single element arrays
- Large arrays (performance testing)
- Boundary conditions and edge cases
- Invalid inputs and error conditions
- Memory safety tests

## Compilation
```bash
g++ -std=c++17 -Wall -Wextra -g array_operations.cpp -o array_ops
g++ -std=c++17 -Wall -Wextra -g search_algorithms.cpp -o search_algos
g++ -std=c++17 -Wall -Wextra -g array_manipulation.cpp -o array_manip
```

## Submission
- Complete all `.cpp` files in this directory
- Ensure your code compiles without warnings
- Test your implementation thoroughly
- Include comments explaining your approach

## Grading Criteria
- **Correctness (50%)**: All functions work correctly for given inputs
- **Error Handling (20%)**: Proper exception handling and edge case management
- **Code Quality (15%)**: Clean, readable, well-documented code
- **Efficiency (15%)**: Optimal time and space complexity implementations

## Due Date
Check course schedule for submission deadline
See course schedule for submission deadline.