#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <stdexcept>

/**
 * AVL Tree Implementation
 * Self-balancing binary search tree where height difference 
 * between left and right subtrees is at most 1
 */

template<typename T>
struct AVLNode {
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(const T& value) : data(value), left(nullptr), right(nullptr), height(0) {}
};

template<typename T>
class AVLTree {
private:
    AVLNode<T>* root;
    size_t nodeCount;
    
    /**
     * Get height of node (handles null nodes)
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int getHeight(AVLNode<T>* node) const {
        return (node == nullptr) ? -1 : node->height;
    }
    
    /**
     * Update height of node based on children
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void updateHeight(AVLNode<T>* node) {
        if (node != nullptr) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }
    
    /**
     * Get balance factor (left height - right height)
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int getBalance(AVLNode<T>* node) const {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }
    
    /**
     * Right rotation (used when left subtree is heavier)
     *       y                               x
     *      / \     Right Rotation          /  \
     *     x   T3   - - - - - - - >        T1   y 
     *    / \       < - - - - - - -             / \
     *   T1  T2     Left Rotation             T2  T3
     * 
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;
        
        // Perform rotation
        x->right = y;
        y->left = T2;
        
        // Update heights
        updateHeight(y);
        updateHeight(x);
        
        return x; // New root
    }
    
    /**
     * Left rotation (used when right subtree is heavier)
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    AVLNode<T>* rotateLeft(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;
        
        // Perform rotation
        y->left = x;
        x->right = T2;
        
        // Update heights
        updateHeight(x);
        updateHeight(y);
        
        return y; // New root
    }
    
    /**
     * Insert a node and maintain AVL property
     * Time Complexity: O(log n)
     * Space Complexity: O(log n)
     */
    AVLNode<T>* insert(AVLNode<T>* node, const T& value) {
        // Step 1: Perform normal BST insertion
        if (node == nullptr) {
            nodeCount++;
            return new AVLNode<T>(value);
        }
        
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            // Duplicate values are not allowed
            return node;
        }
        
        // Step 2: Update height of current node
        updateHeight(node);
        
        // Step 3: Get balance factor
        int balance = getBalance(node);
        
        // Step 4: If node is unbalanced, perform rotations
        
        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }
        
        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }
        
        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        // Return unchanged node if balanced
        return node;
    }
    
    /**
     * Find minimum node in subtree
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    AVLNode<T>* findMinNode(AVLNode<T>* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    /**
     * Remove a node and maintain AVL property
     * Time Complexity: O(log n)
     * Space Complexity: O(log n)
     */
    AVLNode<T>* remove(AVLNode<T>* node, const T& value) {
        // Step 1: Perform normal BST deletion
        if (node == nullptr) {
            return node;
        }
        
        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            // Node to be deleted found
            nodeCount--;
            
            // Node with only one child or no child
            if (node->left == nullptr || node->right == nullptr) {
                AVLNode<T>* temp = node->left ? node->left : node->right;
                
                // No child case
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    // One child case
                    *node = *temp; // Copy contents of non-empty child
                }
                delete temp;
            } else {
                // Node with two children
                AVLNode<T>* temp = findMinNode(node->right);
                
                // Copy the inorder successor's data to this node
                node->data = temp->data;
                
                // Delete the inorder successor
                node->right = remove(node->right, temp->data);
                nodeCount++; // Compensate for decrement in recursive call
            }
        }
        
        // If tree had only one node
        if (node == nullptr) {
            return node;
        }
        
        // Step 2: Update height of current node
        updateHeight(node);
        
        // Step 3: Get balance factor
        int balance = getBalance(node);
        
        // Step 4: If node is unbalanced, perform rotations
        
        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        
        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        
        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    /**
     * Search for a value in the tree
     * Time Complexity: O(log n)
     * Space Complexity: O(log n)
     */
    bool contains(AVLNode<T>* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }
        
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return contains(node->left, value);
        } else {
            return contains(node->right, value);
        }
    }
    
    /**
     * Delete all nodes in the tree
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    void makeEmpty(AVLNode<T>* node) {
        if (node != nullptr) {
            makeEmpty(node->left);
            makeEmpty(node->right);
            delete node;
        }
    }
    
    /**
     * Clone the tree
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    AVLNode<T>* clone(AVLNode<T>* node) const {
        if (node == nullptr) {
            return nullptr;
        }
        
        AVLNode<T>* newNode = new AVLNode<T>(node->data);
        newNode->height = node->height;
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);
        return newNode;
    }
    
    /**
     * Inorder traversal helper
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    void inorderTraversal(AVLNode<T>* node, std::vector<T>& result) const {
        if (node != nullptr) {
            inorderTraversal(node->left, result);
            result.push_back(node->data);
            inorderTraversal(node->right, result);
        }
    }
    
    /**
     * Preorder traversal helper
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    void preorderTraversal(AVLNode<T>* node, std::vector<T>& result) const {
        if (node != nullptr) {
            result.push_back(node->data);
            preorderTraversal(node->left, result);
            preorderTraversal(node->right, result);
        }
    }

public:
    /**
     * Default constructor
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    AVLTree() : root(nullptr), nodeCount(0) {}
    
    /**
     * Copy constructor
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    AVLTree(const AVLTree& other) : root(nullptr), nodeCount(other.nodeCount) {
        root = clone(other.root);
    }
    
    /**
     * Assignment operator
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            makeEmpty();
            root = clone(other.root);
            nodeCount = other.nodeCount;
        }
        return *this;
    }
    
    /**
     * Destructor
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    ~AVLTree() {
        makeEmpty();
    }
    
    /**
     * Insert a value into the tree
     * Time Complexity: O(log n)
     * Space Complexity: O(log n)
     */
    void insert(const T& value) {
        root = insert(root, value);
    }
    
    /**
     * Remove a value from the tree
     * Time Complexity: O(log n)
     * Space Complexity: O(log n)
     */
    void remove(const T& value) {
        root = remove(root, value);
    }
    
    /**
     * Check if value exists in tree
     * Time Complexity: O(log n)
     * Space Complexity: O(log n)
     */
    bool contains(const T& value) const {
        return contains(root, value);
    }
    
    /**
     * Find minimum value in tree
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    T findMin() const {
        if (isEmpty()) {
            throw std::runtime_error("Tree is empty");
        }
        
        AVLNode<T>* minNode = findMinNode(root);
        return minNode->data;
    }
    
    /**
     * Find maximum value in tree
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    T findMax() const {
        if (isEmpty()) {
            throw std::runtime_error("Tree is empty");
        }
        
        AVLNode<T>* node = root;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node->data;
    }
    
    /**
     * Check if tree is empty
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool isEmpty() const {
        return root == nullptr;
    }
    
    /**
     * Get number of nodes in tree
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    size_t size() const {
        return nodeCount;
    }
    
    /**
     * Get height of tree
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int getHeight() const {
        return getHeight(root);
    }
    
    /**
     * Remove all nodes from tree
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    void makeEmpty() {
        makeEmpty(root);
        root = nullptr;
        nodeCount = 0;
    }
    
    /**
     * Check if tree is balanced (for testing)
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    bool isBalanced() const {
        return isBalanced(root);
    }
    
private:
    bool isBalanced(AVLNode<T>* node) const {
        if (node == nullptr) {
            return true;
        }
        
        int balance = getBalance(node);
        return (abs(balance) <= 1) && 
               isBalanced(node->left) && 
               isBalanced(node->right);
    }

public:
    /**
     * Inorder traversal (sorted order)
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    std::vector<T> inorderTraversal() const {
        std::vector<T> result;
        inorderTraversal(root, result);
        return result;
    }
    
    /**
     * Preorder traversal
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    std::vector<T> preorderTraversal() const {
        std::vector<T> result;
        preorderTraversal(root, result);
        return result;
    }
    
    /**
     * Level order traversal
     * Time Complexity: O(n)
     * Space Complexity: O(w) where w is max width
     */
    std::vector<T> levelOrderTraversal() const {
        std::vector<T> result;
        if (root == nullptr) return result;
        
        std::queue<AVLNode<T>*> queue;
        queue.push(root);
        
        while (!queue.empty()) {
            AVLNode<T>* current = queue.front();
            queue.pop();
            result.push_back(current->data);
            
            if (current->left != nullptr) {
                queue.push(current->left);
            }
            if (current->right != nullptr) {
                queue.push(current->right);
            }
        }
        
        return result;
    }
    
    /**
     * Print tree structure with balance factors
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    void printTree() const {
        printTree(root, "", false);
    }
    
private:
    void printTree(AVLNode<T>* node, const std::string& prefix, bool isLeft) const {
        if (node != nullptr) {
            std::cout << prefix;
            std::cout << (isLeft ? "├── " : "└── ");
            std::cout << node->data << " (h:" << node->height 
                      << ", b:" << getBalance(node) << ")" << std::endl;
            
            if (node->left != nullptr || node->right != nullptr) {
                if (node->left != nullptr) {
                    printTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
                } else {
                    std::cout << prefix + (isLeft ? "│   " : "    ") + "├── null" << std::endl;
                }
                
                if (node->right != nullptr) {
                    printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
                } else {
                    std::cout << prefix + (isLeft ? "│   " : "    ") + "└── null" << std::endl;
                }
            }
        }
    }

public:
    /**
     * Get rotation count during insertion (for analysis)
     */
    struct InsertionStats {
        int rotations;
        bool inserted;
    };
    
    InsertionStats insertWithStats(const T& value) {
        int rotations = 0;
        size_t oldCount = nodeCount;
        root = insertWithStats(root, value, rotations);
        return {rotations, nodeCount > oldCount};
    }
    
private:
    AVLNode<T>* insertWithStats(AVLNode<T>* node, const T& value, int& rotations) {
        // Normal BST insertion
        if (node == nullptr) {
            nodeCount++;
            return new AVLNode<T>(value);
        }
        
        if (value < node->data) {
            node->left = insertWithStats(node->left, value, rotations);
        } else if (value > node->data) {
            node->right = insertWithStats(node->right, value, rotations);
        } else {
            return node; // Duplicate
        }
        
        // Update height
        updateHeight(node);
        
        // Get balance factor
        int balance = getBalance(node);
        
        // Perform rotations if needed
        if (balance > 1 && value < node->left->data) {
            rotations++;
            return rotateRight(node);
        }
        
        if (balance < -1 && value > node->right->data) {
            rotations++;
            return rotateLeft(node);
        }
        
        if (balance > 1 && value > node->left->data) {
            rotations += 2; // Left-Right rotation
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        if (balance < -1 && value < node->right->data) {
            rotations += 2; // Right-Left rotation
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }

public:
    /**
     * Range query: find all values in [low, high]
     * Time Complexity: O(log n + k) where k is number of results
     * Space Complexity: O(log n + k)
     */
    std::vector<T> rangeQuery(const T& low, const T& high) const {
        std::vector<T> result;
        rangeQuery(root, low, high, result);
        return result;
    }
    
private:
    void rangeQuery(AVLNode<T>* node, const T& low, const T& high, std::vector<T>& result) const {
        if (node == nullptr) {
            return;
        }
        
        // If current node is in range, add it
        if (node->data >= low && node->data <= high) {
            result.push_back(node->data);
        }
        
        // Recurse on left subtree if there might be values in range
        if (node->data > low) {
            rangeQuery(node->left, low, high, result);
        }
        
        // Recurse on right subtree if there might be values in range
        if (node->data < high) {
            rangeQuery(node->right, low, high, result);
        }
    }
};

// Example usage and testing
void demonstrateAVL() {
    std::cout << "=== AVL Tree Demonstration ===" << std::endl;
    
    AVLTree<int> avl;
    
    // Insert elements that would create imbalance in regular BST
    std::vector<int> values = {10, 20, 30, 40, 50, 25};
    
    std::cout << "Inserting values: ";
    for (int val : values) {
        std::cout << val << " ";
        auto stats = avl.insertWithStats(val);
        if (stats.inserted) {
            std::cout << "(rotations: " << stats.rotations << ") ";
        }
    }
    std::cout << std::endl;
    
    std::cout << "\nAVL Tree structure:" << std::endl;
    avl.printTree();
    
    std::cout << "\nTree statistics:" << std::endl;
    std::cout << "Size: " << avl.size() << std::endl;
    std::cout << "Height: " << avl.getHeight() << std::endl;
    std::cout << "Is balanced: " << std::boolalpha << avl.isBalanced() << std::endl;
    std::cout << "Min: " << avl.findMin() << std::endl;
    std::cout << "Max: " << avl.findMax() << std::endl;
    
    std::cout << "\nTraversals:" << std::endl;
    
    auto inorder = avl.inorderTraversal();
    std::cout << "Inorder: ";
    for (int val : inorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    auto levelorder = avl.levelOrderTraversal();
    std::cout << "Level order: ";
    for (int val : levelorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test range query
    std::cout << "\nRange query [20, 40]: ";
    auto range = avl.rangeQuery(20, 40);
    for (int val : range) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test deletion
    std::cout << "\nAfter removing 30:" << std::endl;
    avl.remove(30);
    avl.printTree();
    std::cout << "Still balanced: " << std::boolalpha << avl.isBalanced() << std::endl;
}