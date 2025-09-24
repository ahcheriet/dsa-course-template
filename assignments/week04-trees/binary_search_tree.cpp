#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <functional>

/**
 * Binary Search Tree Implementation
 * A tree data structure where left child < parent < right child
 */

template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;
    size_t nodeCount;
    
    /**
     * Helper function to insert a node recursively
     * Time Complexity: O(h) where h is height
     * Space Complexity: O(h) for recursion stack
     */
    TreeNode<T>* insert(TreeNode<T>* node, const T& value) {
        if (node == nullptr) {
            nodeCount++;
            return new TreeNode<T>(value);
        }
        
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        // Duplicate values are ignored
        
        return node;
    }
    
    /**
     * Helper function to remove a node recursively
     * Time Complexity: O(h)
     * Space Complexity: O(h)
     */
    TreeNode<T>* remove(TreeNode<T>* node, const T& value) {
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
            
            // Case 1: Node with no children
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Case 2: Node with one child
            else if (node->left == nullptr) {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Node with two children
            else {
                TreeNode<T>* successor = findMinNode(node->right);
                node->data = successor->data;
                node->right = remove(node->right, successor->data);
                nodeCount++; // Compensate for the decrement in recursive call
            }
        }
        return node;
    }
    
    /**
     * Helper function to find minimum node in subtree
     * Time Complexity: O(h)
     * Space Complexity: O(1)
     */
    TreeNode<T>* findMinNode(TreeNode<T>* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    /**
     * Helper function to find maximum node in subtree
     * Time Complexity: O(h)
     * Space Complexity: O(1)
     */
    TreeNode<T>* findMaxNode(TreeNode<T>* node) const {
        while (node != nullptr && node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
    
    /**
     * Helper function to search for a value
     * Time Complexity: O(h)
     * Space Complexity: O(h)
     */
    bool contains(TreeNode<T>* node, const T& value) const {
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
     * Helper function to calculate height of tree
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    int height(TreeNode<T>* node) const {
        if (node == nullptr) {
            return -1; // Height of empty tree is -1
        }
        
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        
        return 1 + std::max(leftHeight, rightHeight);
    }
    
    /**
     * Helper function to delete all nodes
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    void makeEmpty(TreeNode<T>* node) {
        if (node != nullptr) {
            makeEmpty(node->left);
            makeEmpty(node->right);
            delete node;
        }
    }
    
    /**
     * Helper function to clone tree
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    TreeNode<T>* clone(TreeNode<T>* node) const {
        if (node == nullptr) {
            return nullptr;
        }
        
        TreeNode<T>* newNode = new TreeNode<T>(node->data);
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);
        return newNode;
    }
    
    /**
     * Helper function for inorder traversal
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    void inorderTraversal(TreeNode<T>* node, std::vector<T>& result) const {
        if (node != nullptr) {
            inorderTraversal(node->left, result);
            result.push_back(node->data);
            inorderTraversal(node->right, result);
        }
    }
    
    /**
     * Helper function for preorder traversal
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    void preorderTraversal(TreeNode<T>* node, std::vector<T>& result) const {
        if (node != nullptr) {
            result.push_back(node->data);
            preorderTraversal(node->left, result);
            preorderTraversal(node->right, result);
        }
    }
    
    /**
     * Helper function for postorder traversal
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    void postorderTraversal(TreeNode<T>* node, std::vector<T>& result) const {
        if (node != nullptr) {
            postorderTraversal(node->left, result);
            postorderTraversal(node->right, result);
            result.push_back(node->data);
        }
    }

public:
    /**
     * Default constructor
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    BinarySearchTree() : root(nullptr), nodeCount(0) {}
    
    /**
     * Copy constructor
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    BinarySearchTree(const BinarySearchTree& other) : root(nullptr), nodeCount(other.nodeCount) {
        root = clone(other.root);
    }
    
    /**
     * Assignment operator
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    BinarySearchTree& operator=(const BinarySearchTree& other) {
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
     * Space Complexity: O(h)
     */
    ~BinarySearchTree() {
        makeEmpty();
    }
    
    /**
     * Insert a value into the tree
     * Time Complexity: O(h) average, O(n) worst case
     * Space Complexity: O(h)
     */
    void insert(const T& value) {
        root = insert(root, value);
    }
    
    /**
     * Remove a value from the tree
     * Time Complexity: O(h) average, O(n) worst case
     * Space Complexity: O(h)
     */
    void remove(const T& value) {
        root = remove(root, value);
    }
    
    /**
     * Check if value exists in tree
     * Time Complexity: O(h) average, O(n) worst case
     * Space Complexity: O(h)
     */
    bool contains(const T& value) const {
        return contains(root, value);
    }
    
    /**
     * Find minimum value in tree
     * Time Complexity: O(h)
     * Space Complexity: O(1)
     */
    T findMin() const {
        if (isEmpty()) {
            throw std::runtime_error("Tree is empty");
        }
        
        TreeNode<T>* minNode = findMinNode(root);
        return minNode->data;
    }
    
    /**
     * Find maximum value in tree
     * Time Complexity: O(h)
     * Space Complexity: O(1)
     */
    T findMax() const {
        if (isEmpty()) {
            throw std::runtime_error("Tree is empty");
        }
        
        TreeNode<T>* maxNode = findMaxNode(root);
        return maxNode->data;
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
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    int getHeight() const {
        return height(root);
    }
    
    /**
     * Remove all nodes from tree
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    void makeEmpty() {
        makeEmpty(root);
        root = nullptr;
        nodeCount = 0;
    }
    
    /**
     * Inorder traversal (sorted order)
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    std::vector<T> inorderTraversal() const {
        std::vector<T> result;
        inorderTraversal(root, result);
        return result;
    }
    
    /**
     * Iterative inorder traversal
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    std::vector<T> inorderTraversalIterative() const {
        std::vector<T> result;
        std::stack<TreeNode<T>*> stack;
        TreeNode<T>* current = root;
        
        while (current != nullptr || !stack.empty()) {
            // Go to leftmost node
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            
            // Current is null, pop from stack
            current = stack.top();
            stack.pop();
            result.push_back(current->data);
            
            // Visit right subtree
            current = current->right;
        }
        
        return result;
    }
    
    /**
     * Preorder traversal
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    std::vector<T> preorderTraversal() const {
        std::vector<T> result;
        preorderTraversal(root, result);
        return result;
    }
    
    /**
     * Iterative preorder traversal
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    std::vector<T> preorderTraversalIterative() const {
        std::vector<T> result;
        if (root == nullptr) return result;
        
        std::stack<TreeNode<T>*> stack;
        stack.push(root);
        
        while (!stack.empty()) {
            TreeNode<T>* current = stack.top();
            stack.pop();
            result.push_back(current->data);
            
            // Push right first, then left (stack is LIFO)
            if (current->right != nullptr) {
                stack.push(current->right);
            }
            if (current->left != nullptr) {
                stack.push(current->left);
            }
        }
        
        return result;
    }
    
    /**
     * Postorder traversal
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    std::vector<T> postorderTraversal() const {
        std::vector<T> result;
        postorderTraversal(root, result);
        return result;
    }
    
    /**
     * Level order traversal (breadth-first)
     * Time Complexity: O(n)
     * Space Complexity: O(w) where w is maximum width
     */
    std::vector<T> levelOrderTraversal() const {
        std::vector<T> result;
        if (root == nullptr) return result;
        
        std::queue<TreeNode<T>*> queue;
        queue.push(root);
        
        while (!queue.empty()) {
            TreeNode<T>* current = queue.front();
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
     * Print tree structure (for debugging)
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    void printTree() const {
        printTree(root, "", false);
    }
    
private:
    void printTree(TreeNode<T>* node, const std::string& prefix, bool isLeft) const {
        if (node != nullptr) {
            std::cout << prefix;
            std::cout << (isLeft ? "├── " : "└── ");
            std::cout << node->data << std::endl;
            
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
     * Get k-th smallest element (1-indexed)
     * Time Complexity: O(h + k)
     * Space Complexity: O(h)
     */
    T kthSmallest(int k) const {
        if (k <= 0 || static_cast<size_t>(k) > nodeCount) {
            throw std::out_of_range("k is out of range");
        }
        
        int count = 0;
        return kthSmallest(root, k, count);
    }
    
private:
    T kthSmallest(TreeNode<T>* node, int k, int& count) const {
        if (node == nullptr) {
            throw std::runtime_error("k-th smallest not found");
        }
        
        // Search in left subtree
        if (node->left != nullptr) {
            try {
                return kthSmallest(node->left, k, count);
            } catch (const std::runtime_error&) {
                // Continue to current node
            }
        }
        
        // Check current node
        count++;
        if (count == k) {
            return node->data;
        }
        
        // Search in right subtree
        return kthSmallest(node->right, k, count);
    }

public:
    /**
     * Find lowest common ancestor of two values
     * Time Complexity: O(h)
     * Space Complexity: O(h)
     */
    T lowestCommonAncestor(const T& p, const T& q) const {
        TreeNode<T>* lca = lowestCommonAncestor(root, p, q);
        if (lca == nullptr) {
            throw std::runtime_error("LCA not found");
        }
        return lca->data;
    }
    
private:
    TreeNode<T>* lowestCommonAncestor(TreeNode<T>* node, const T& p, const T& q) const {
        if (node == nullptr) {
            return nullptr;
        }
        
        // If both p and q are smaller than root, LCA is in left subtree
        if (p < node->data && q < node->data) {
            return lowestCommonAncestor(node->left, p, q);
        }
        
        // If both p and q are greater than root, LCA is in right subtree
        if (p > node->data && q > node->data) {
            return lowestCommonAncestor(node->right, p, q);
        }
        
        // If p and q are on different sides, current node is LCA
        return node;
    }
};

// Example usage and testing
void demonstrateBST() {
    std::cout << "=== Binary Search Tree Demonstration ===" << std::endl;
    
    BinarySearchTree<int> bst;
    
    // Insert elements
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    for (int val : values) {
        bst.insert(val);
    }
    
    std::cout << "Tree structure:" << std::endl;
    bst.printTree();
    
    std::cout << "\nTree statistics:" << std::endl;
    std::cout << "Size: " << bst.size() << std::endl;
    std::cout << "Height: " << bst.getHeight() << std::endl;
    std::cout << "Min: " << bst.findMin() << std::endl;
    std::cout << "Max: " << bst.findMax() << std::endl;
    
    std::cout << "\nTraversals:" << std::endl;
    
    auto inorder = bst.inorderTraversal();
    std::cout << "Inorder: ";
    for (int val : inorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    auto preorder = bst.preorderTraversal();
    std::cout << "Preorder: ";
    for (int val : preorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    auto levelorder = bst.levelOrderTraversal();
    std::cout << "Level order: ";
    for (int val : levelorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test search
    std::cout << "\nSearch tests:" << std::endl;
    std::cout << "Contains 40: " << std::boolalpha << bst.contains(40) << std::endl;
    std::cout << "Contains 55: " << std::boolalpha << bst.contains(55) << std::endl;
    
    // Test k-th smallest
    std::cout << "\nK-th smallest:" << std::endl;
    std::cout << "3rd smallest: " << bst.kthSmallest(3) << std::endl;
    std::cout << "7th smallest: " << bst.kthSmallest(7) << std::endl;
    
    // Test LCA
    std::cout << "\nLowest Common Ancestor:" << std::endl;
    std::cout << "LCA(20, 40): " << bst.lowestCommonAncestor(20, 40) << std::endl;
    std::cout << "LCA(60, 80): " << bst.lowestCommonAncestor(60, 80) << std::endl;
    
    // Test removal
    std::cout << "\nAfter removing 30:" << std::endl;
    bst.remove(30);
    auto inorderAfterRemove = bst.inorderTraversal();
    for (int val : inorderAfterRemove) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}