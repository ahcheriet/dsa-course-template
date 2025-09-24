# Week 3: Stacks and Queues

## Learning Objectives
- Understand LIFO (Last In, First Out) and FIFO (First In, First Out) principles
- Implement comprehensive stack and queue data structures
- Apply stacks and queues to solve complex real-world problems
- Master advanced applications including expression evaluation and algorithm optimization

## Assignment Tasks

### Task 1: Stack Implementation (25 points)
Implement a comprehensive stack class in `stack.cpp`:

**Core Operations:**
1. **push(element)** - Add element to top with dynamic resizing
2. **pop()** - Remove and return top element with error handling
3. **peek()** - Return top element without removing
4. **isEmpty()** - Check if stack is empty
5. **size()** - Return number of elements
6. **clear()** - Remove all elements
7. **display()** - Print stack contents for debugging

**Memory Management:**
- Dynamic resizing when capacity is exceeded
- Proper copy constructor and assignment operator
- Exception handling for underflow conditions

### Task 2: Queue Implementation (25 points) 
Implement circular queue and priority queue in `queue.cpp`:

**Circular Queue Operations:**
1. **enqueue(element)** - Add element to rear with dynamic resizing
2. **dequeue()** - Remove and return front element
3. **front()** - Return front element without removing
4. **rear()** - Return rear element without removing
5. **isEmpty()** - Check if queue is empty
6. **size()** - Return number of elements
7. **display()** - Print queue contents

**Priority Queue:**
- Max heap-based implementation
- **enqueue(element)** - O(log n) insertion
- **dequeue()** - O(log n) extraction of maximum

### Task 3: Stack Applications (25 points)
Implement advanced stack applications:

1. **isBalanced(expression)** - Check balanced parentheses/brackets/braces
2. **infixToPostfix(expression)** - Convert infix to postfix with operator precedence
3. **evaluatePostfix(expression)** - Evaluate postfix expressions with error handling
4. **isPalindrome(string)** - Check palindrome using stack
5. **nextGreaterElement(array)** - Find next greater element for each position

### Task 4: Queue Applications (25 points)
Implement advanced queue applications:

1. **josephusProblem(n, k)** - Solve Josephus problem using circular queue
2. **generateBinaryNumbers(n)** - Generate binary representations 1 to n
3. **levelOrderTraversal(graph, start)** - BFS traversal simulation
4. **reverseFirstKElements(queue, k)** - Reverse first k elements
5. **slidingWindowMaximum(array, k)** - Maximum in sliding windows

### Task 5: Advanced Implementations (Bonus - 10 points)
Implement in `applications.cpp`:

1. **StackUsingQueues** - Implement stack using two queues
2. **QueueUsingStacks** - Implement queue using two stacks  
3. **MinStack** - Stack with O(1) minimum element access
4. **CircularQueue** - Fixed-size circular queue implementation
5. **evaluateExpression(infix)** - Direct infix expression evaluation

## Advanced Features

### Error Handling
- **Underflow Protection**: Proper exception handling for empty containers
- **Overflow Management**: Dynamic resizing prevents overflow
- **Input Validation**: Comprehensive validation for all operations
- **Memory Safety**: RAII principles and proper resource management

### Performance Optimizations
- **Amortized O(1)**: Push/pop operations with dynamic resizing
- **Space Efficiency**: Circular queue implementation minimizes memory usage
- **Cache Locality**: Array-based implementations for better performance

### Algorithm Complexity Requirements
- **Stack Operations**: O(1) for push, pop, peek, isEmpty, size
- **Queue Operations**: O(1) for enqueue, dequeue, front, rear
- **Priority Queue**: O(log n) for enqueue/dequeue, O(1) for peek
- **Applications**: Optimal complexity for each algorithm

## Technical Requirements

### C++ Standards
- Use C++17 features including auto, range-based loops, smart pointers
- Template-based implementations for generic data types
- RAII (Resource Acquisition Is Initialization) principles
- Exception safety guarantees

### Memory Management
- Dynamic memory allocation with proper cleanup
- Copy constructors and assignment operators (Rule of Three)
- Move semantics where appropriate
- No memory leaks (verify with Valgrind)

### Code Quality
- Comprehensive documentation with time/space complexity
- Consistent naming conventions and formatting
- Modular design with clear separation of concerns
- Unit-testable functions with clear interfaces

## Testing Requirements

Your implementations will be tested with:
- **Edge Cases**: Empty containers, single elements, maximum capacity
- **Stress Tests**: Large datasets and performance benchmarks
- **Error Conditions**: Invalid inputs and boundary violations
- **Memory Tests**: Leak detection and proper cleanup verification
- **Correctness**: Algorithm verification with known expected outputs

## Compilation Instructions

```bash
# Individual compilation
g++ -std=c++17 -Wall -Wextra -g -O2 stack.cpp -o stack_test
g++ -std=c++17 -Wall -Wextra -g -O2 queue.cpp -o queue_test
g++ -std=c++17 -Wall -Wextra -g -O2 applications.cpp -o apps_test

# Memory checking
valgrind --tool=memcheck --leak-check=full ./stack_test
valgrind --tool=memcheck --leak-check=full ./queue_test
```

## Submission Guidelines

### Required Files
- `stack.cpp` - Complete stack implementation with applications
- `queue.cpp` - Complete queue and priority queue implementations
- `applications.cpp` - Advanced stack/queue applications and hybrid structures

### Code Documentation
- Function-level comments with complexity analysis
- Implementation strategy explanations
- Edge case handling documentation
- Performance consideration notes

## Grading Criteria

- **Correctness (40%)**: All functions work correctly for given inputs
- **Performance (20%)**: Optimal time and space complexity implementations
- **Code Quality (20%)**: Clean, readable, well-documented code following best practices
- **Error Handling (10%)**: Comprehensive exception handling and edge case management  
- **Advanced Features (10%)**: Bonus implementations and optimization techniques

## Learning Resources

### Key Concepts
- **Stack**: LIFO principle, function call management, expression evaluation
- **Queue**: FIFO principle, scheduling, breadth-first search
- **Applications**: Parsing algorithms, graph traversals, optimization problems

### Algorithm Patterns
- **Two-Pointer Technique**: Using stacks for bracket matching
- **Monotonic Stack**: Next greater/smaller element problems
- **Level-Order Processing**: BFS using queues
- **Circular Buffer**: Efficient queue implementation

## Due Date
Check course schedule for submission deadline. Late submissions will incur penalties as per course policy.