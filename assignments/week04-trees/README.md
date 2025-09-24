# Week 4: Binary Search Trees and AVL Trees

## Learning Objectives
- Understand tree data structures and their properties
- Implement binary search tree operations efficiently
- Master AVL tree self-balancing mechanisms
- Apply tree traversal algorithms and analyze their complexities
- Solve real-world problems using tree-based data structures

## Assignment Tasks

### Task 1: Binary Search Tree Implementation (30 points)
Implement a comprehensive BST class in `binary_search_tree.cpp`:

**Core Operations:**
1. **insert(value)** - Insert element maintaining BST property
2. **remove(value)** - Remove element with proper restructuring
3. **contains(value)** - Search for element in tree
4. **findMin()** - Find minimum element (leftmost node)
5. **findMax()** - Find maximum element (rightmost node)
6. **isEmpty()** - Check if tree is empty
7. **size()** - Return total number of nodes
8. **height()** - Calculate tree height
9. **makeEmpty()** - Remove all nodes

**Traversal Operations:**
1. **inorderTraversal()** - Left, Root, Right (sorted order)
2. **preorderTraversal()** - Root, Left, Right  
3. **postorderTraversal()** - Left, Right, Root
4. **levelOrderTraversal()** - Breadth-first traversal

### Task 2: AVL Tree Implementation (35 points)
Implement self-balancing AVL tree in `avl_tree.cpp`:

**Core Operations:**
1. **insert(value)** - Insert with automatic balancing
2. **remove(value)** - Remove with rebalancing
3. **contains(value)** - Search operation
4. **findMin()** - Minimum element
5. **findMax()** - Maximum element
6. **getBalance(node)** - Calculate balance factor
7. **rotateLeft(node)** - Left rotation for balancing
8. **rotateRight(node)** - Right rotation for balancing
9. **rotateLeftRight(node)** - Double rotation LR
10. **rotateRightLeft(node)** - Double rotation RL

**Balancing Properties:**
- Maintain height difference ≤ 1 between subtrees
- Automatic rebalancing after insertions/deletions
- Height calculation and balance factor maintenance

### Task 3: Tree Applications and Algorithms (35 points)
Implement advanced tree operations in `tree_applications.cpp`:

**Validation and Analysis:**
1. **isBST(root)** - Validate BST property
2. **isBalanced(root)** - Check if tree is height-balanced
3. **diameter(root)** - Find diameter of tree
4. **lowestCommonAncestor(root, p, q)** - Find LCA of two nodes

**Tree Construction:**
1. **buildFromSorted(array)** - Build balanced BST from sorted array
2. **buildFromPreorder(preorder)** - Reconstruct BST from preorder
3. **serializeTree(root)** - Serialize tree to string
4. **deserializeTree(data)** - Deserialize string to tree

**Advanced Operations:**
1. **kthSmallest(root, k)** - Find k-th smallest element
2. **rangeSum(root, low, high)** - Sum of values in range
3. **pathSum(root, sum)** - Find paths with given sum
4. **mirrorTree(root)** - Create mirror image of tree

## Advanced Features

### Memory Management
- **RAII Principles**: Automatic resource management
- **Copy Semantics**: Deep copy constructor and assignment operator
- **Move Semantics**: Efficient move constructor and assignment
- **Exception Safety**: Strong exception safety guarantees

### Performance Optimizations
- **Iterative Implementations**: Stack-based iterative traversals
- **Tail Recursion**: Optimized recursive operations where possible
- **Memory Pool**: Optional memory pool for node allocation
- **Cache Efficiency**: Node layout optimized for cache locality

### Complexity Requirements
- **BST Operations**: O(h) where h is height (O(log n) average, O(n) worst)
- **AVL Operations**: O(log n) guaranteed for all operations
- **Traversals**: O(n) time, O(h) space for recursive, O(n) space for iterative
- **Balancing**: O(log n) rotations maximum per operation

## Implementation Guidelines

### Node Structure
```cpp
template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    int height;  // For AVL trees
    
    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
};
```

### Error Handling
- **Empty Tree Operations**: Proper exception handling for operations on empty trees
- **Invalid Operations**: Validation for all input parameters
- **Memory Allocation**: Handle allocation failures gracefully
- **Null Pointer Safety**: Comprehensive null pointer checks

### Code Quality Standards
- **Template-Based**: Generic implementation supporting any comparable type
- **Const Correctness**: Proper const methods and parameters
- **Documentation**: Comprehensive comments with complexity analysis
- **Testing**: Unit-testable design with clear interfaces

## Testing Requirements

### Functionality Tests
- **Basic Operations**: Insert, remove, search on various tree configurations
- **Edge Cases**: Empty trees, single nodes, linear trees, balanced trees
- **Traversal Verification**: Correct order for all traversal types
- **Balance Validation**: AVL property maintenance after all operations

### Performance Tests
- **Large Datasets**: Operations on trees with 10,000+ nodes
- **Worst Case Scenarios**: Linear trees, repeated operations
- **Memory Usage**: Memory leak detection and efficiency analysis
- **Benchmark Comparisons**: BST vs AVL performance characteristics

### Stress Tests
- **Random Operations**: Mixed insert/delete/search operations
- **Duplicate Handling**: Proper behavior with duplicate values
- **Boundary Conditions**: Maximum/minimum values, integer overflow
- **Concurrent Access**: Thread safety considerations (if applicable)

## Compilation Instructions

```bash
# Individual compilation with debugging
g++ -std=c++17 -Wall -Wextra -g -O2 binary_search_tree.cpp -o bst_test
g++ -std=c++17 -Wall -Wextra -g -O2 avl_tree.cpp -o avl_test
g++ -std=c++17 -Wall -Wextra -g -O2 tree_applications.cpp -o tree_apps

# Memory leak detection
valgrind --tool=memcheck --leak-check=full --track-origins=yes ./bst_test
valgrind --tool=memcheck --leak-check=full --track-origins=yes ./avl_test

# Performance profiling
g++ -std=c++17 -O3 -DNDEBUG binary_search_tree.cpp -o bst_optimized
time ./bst_optimized
```

## Grading Criteria

- **Correctness (35%)**: All tree operations work correctly with proper BST/AVL properties
- **Performance (25%)**: Optimal time and space complexity implementations
- **Code Quality (20%)**: Clean, readable, well-documented code following best practices
- **Advanced Features (10%)**: Bonus implementations and optimization techniques
- **Testing and Validation (10%)**: Comprehensive error handling and edge case management

## Submission Requirements

### Required Files
- `binary_search_tree.cpp` - Complete BST implementation with traversals
- `avl_tree.cpp` - Self-balancing AVL tree with rotations
- `tree_applications.cpp` - Advanced tree algorithms and applications

### Documentation
- **Algorithm Explanations**: Detailed comments for complex operations
- **Complexity Analysis**: Big-O notation for all operations
- **Design Decisions**: Rationale for implementation choices
- **Test Cases**: Description of edge cases handled

## Learning Resources

### Key Concepts
- **Binary Search Property**: Left subtree < root < right subtree
- **Tree Traversals**: In-order, pre-order, post-order, level-order
- **AVL Balancing**: Height-balanced trees with automatic rotations
- **Tree Rotations**: Single and double rotations for balancing

### Algorithm Patterns
- **Divide and Conquer**: Tree operations using recursive decomposition
- **Dynamic Programming**: Optimal substructure in tree problems
- **Two-Pointer Technique**: LCA and path-finding algorithms
- **Stack/Queue Usage**: Iterative traversal implementations

## Due Date
Check course schedule for submission deadline. Extensions available for complex implementations with prior approval.

## Advanced Challenges (Bonus)

### Red-Black Tree Implementation (10 bonus points)
- Implement red-black tree with color constraints
- Guarantee O(log n) operations with less strict balancing than AVL

### B-Tree Implementation (15 bonus points)  
- Multi-way search tree for database applications
- Variable branching factor with efficient disk I/O

### Tree Visualization (5 bonus points)
- ASCII art tree printing with proper formatting
- Graphical representation export (DOT format)

### Persistent Trees (20 bonus points)
- Immutable tree structures with structural sharing
- Version control for tree modifications