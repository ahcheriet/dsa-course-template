#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <limits>

/**
 * Advanced Tree Applications and Algorithms
 * This file contains implementations of various tree-based algorithms
 * and applications commonly used in computer science
 */

// Generic tree node for general tree algorithms
template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

/**
 * Tree Validation Algorithms
 */
class TreeValidator {
public:
    /**
     * Validate if a binary tree is a valid BST
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    template<typename T>
    static bool isValidBST(TreeNode<T>* root) {
        return isValidBST(root, std::numeric_limits<T>::lowest(), 
                          std::numeric_limits<T>::max());
    }
    
private:
    template<typename T>
    static bool isValidBST(TreeNode<T>* node, T minVal, T maxVal) {
        if (node == nullptr) {
            return true;
        }
        
        if (node->data <= minVal || node->data >= maxVal) {
            return false;
        }
        
        return isValidBST(node->left, minVal, node->data) &&
               isValidBST(node->right, node->data, maxVal);
    }

public:
    /**
     * Check if binary tree is complete
     * Time Complexity: O(n)
     * Space Complexity: O(w) where w is maximum width
     */
    template<typename T>
    static bool isCompleteTree(TreeNode<T>* root) {
        if (root == nullptr) {
            return true;
        }
        
        std::queue<TreeNode<T>*> queue;
        queue.push(root);
        bool foundNull = false;
        
        while (!queue.empty()) {
            TreeNode<T>* current = queue.front();
            queue.pop();
            
            if (current == nullptr) {
                foundNull = true;
            } else {
                if (foundNull) {
                    return false; // Found non-null after null
                }
                queue.push(current->left);
                queue.push(current->right);
            }
        }
        
        return true;
    }
    
    /**
     * Check if binary tree is balanced (height difference <= 1)
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    template<typename T>
    static bool isBalanced(TreeNode<T>* root) {
        return checkBalance(root) != -1;
    }
    
private:
    template<typename T>
    static int checkBalance(TreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        
        int leftHeight = checkBalance(node->left);
        if (leftHeight == -1) return -1;
        
        int rightHeight = checkBalance(node->right);
        if (rightHeight == -1) return -1;
        
        if (abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        
        return 1 + std::max(leftHeight, rightHeight);
    }
};

/**
 * Tree Path Algorithms
 */
class TreePathFinder {
public:
    /**
     * Find all root-to-leaf paths
     * Time Complexity: O(n * h)
     * Space Complexity: O(n * h)
     */
    template<typename T>
    static std::vector<std::vector<T>> findAllPaths(TreeNode<T>* root) {
        std::vector<std::vector<T>> allPaths;
        std::vector<T> currentPath;
        findPaths(root, currentPath, allPaths);
        return allPaths;
    }
    
private:
    template<typename T>
    static void findPaths(TreeNode<T>* node, std::vector<T>& currentPath, 
                         std::vector<std::vector<T>>& allPaths) {
        if (node == nullptr) {
            return;
        }
        
        currentPath.push_back(node->data);
        
        // If leaf node, add path to result
        if (node->left == nullptr && node->right == nullptr) {
            allPaths.push_back(currentPath);
        } else {
            findPaths(node->left, currentPath, allPaths);
            findPaths(node->right, currentPath, allPaths);
        }
        
        currentPath.pop_back(); // Backtrack
    }

public:
    /**
     * Find path with given sum
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    template<typename T>
    static bool hasPathSum(TreeNode<T>* root, T targetSum) {
        if (root == nullptr) {
            return false;
        }
        
        // If leaf node, check if sum matches
        if (root->left == nullptr && root->right == nullptr) {
            return root->data == targetSum;
        }
        
        T remainingSum = targetSum - root->data;
        return hasPathSum(root->left, remainingSum) || 
               hasPathSum(root->right, remainingSum);
    }
    
    /**
     * Find all paths with given sum
     * Time Complexity: O(n * h)
     * Space Complexity: O(n * h)
     */
    template<typename T>
    static std::vector<std::vector<T>> findPathsWithSum(TreeNode<T>* root, T targetSum) {
        std::vector<std::vector<T>> result;
        std::vector<T> currentPath;
        findPathsWithSum(root, targetSum, currentPath, result);
        return result;
    }
    
private:
    template<typename T>
    static void findPathsWithSum(TreeNode<T>* node, T targetSum, 
                                std::vector<T>& currentPath,
                                std::vector<std::vector<T>>& result) {
        if (node == nullptr) {
            return;
        }
        
        currentPath.push_back(node->data);
        
        if (node->left == nullptr && node->right == nullptr && 
            node->data == targetSum) {
            result.push_back(currentPath);
        } else {
            T remainingSum = targetSum - node->data;
            findPathsWithSum(node->left, remainingSum, currentPath, result);
            findPathsWithSum(node->right, remainingSum, currentPath, result);
        }
        
        currentPath.pop_back();
    }

public:
    /**
     * Find maximum path sum (path can start and end at any nodes)
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    template<typename T>
    static T maxPathSum(TreeNode<T>* root) {
        T maxSum = std::numeric_limits<T>::lowest();
        maxPathSumHelper(root, maxSum);
        return maxSum;
    }
    
private:
    template<typename T>
    static T maxPathSumHelper(TreeNode<T>* node, T& maxSum) {
        if (node == nullptr) {
            return 0;
        }
        
        // Get maximum sum from left and right subtrees
        T leftSum = std::max(static_cast<T>(0), maxPathSumHelper(node->left, maxSum));
        T rightSum = std::max(static_cast<T>(0), maxPathSumHelper(node->right, maxSum));
        
        // Maximum path sum including current node
        T currentMax = node->data + leftSum + rightSum;
        maxSum = std::max(maxSum, currentMax);
        
        // Return maximum path sum starting from current node
        return node->data + std::max(leftSum, rightSum);
    }
};

/**
 * Tree Construction Algorithms
 */
class TreeBuilder {
public:
    /**
     * Build BST from sorted array (creates balanced BST)
     * Time Complexity: O(n)
     * Space Complexity: O(log n)
     */
    template<typename T>
    static TreeNode<T>* sortedArrayToBST(const std::vector<T>& nums) {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }
    
private:
    template<typename T>
    static TreeNode<T>* sortedArrayToBST(const std::vector<T>& nums, 
                                        int left, int right) {
        if (left > right) {
            return nullptr;
        }
        
        int mid = left + (right - left) / 2;
        TreeNode<T>* root = new TreeNode<T>(nums[mid]);
        
        root->left = sortedArrayToBST(nums, left, mid - 1);
        root->right = sortedArrayToBST(nums, mid + 1, right);
        
        return root;
    }

public:
    /**
     * Build tree from preorder and inorder traversals
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    template<typename T>
    static TreeNode<T>* buildTree(const std::vector<T>& preorder, 
                                 const std::vector<T>& inorder) {
        std::unordered_map<T, int> inorderMap;
        for (size_t i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        int preorderIndex = 0;
        return buildTree(preorder, inorderMap, preorderIndex, 0, inorder.size() - 1);
    }
    
private:
    template<typename T>
    static TreeNode<T>* buildTree(const std::vector<T>& preorder,
                                 const std::unordered_map<T, int>& inorderMap,
                                 int& preorderIndex, int inorderStart, int inorderEnd) {
        if (inorderStart > inorderEnd) {
            return nullptr;
        }
        
        T rootVal = preorder[preorderIndex++];
        TreeNode<T>* root = new TreeNode<T>(rootVal);
        
        int inorderIndex = inorderMap.at(rootVal);
        
        root->left = buildTree(preorder, inorderMap, preorderIndex, 
                              inorderStart, inorderIndex - 1);
        root->right = buildTree(preorder, inorderMap, preorderIndex, 
                               inorderIndex + 1, inorderEnd);
        
        return root;
    }
};

/**
 * Advanced Tree Operations
 */
class TreeOperations {
public:
    /**
     * Serialize tree to string
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    template<typename T>
    static std::string serialize(TreeNode<T>* root) {
        std::string result;
        serializeHelper(root, result);
        return result;
    }
    
private:
    template<typename T>
    static void serializeHelper(TreeNode<T>* node, std::string& result) {
        if (node == nullptr) {
            result += "null,";
            return;
        }
        
        result += std::to_string(node->data) + ",";
        serializeHelper(node->left, result);
        serializeHelper(node->right, result);
    }

public:
    /**
     * Deserialize string to tree
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static TreeNode<int>* deserialize(const std::string& data) {
        std::vector<std::string> tokens;
        std::string token;
        for (char c : data) {
            if (c == ',') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            } else {
                token += c;
            }
        }
        
        int index = 0;
        return deserializeHelper(tokens, index);
    }
    
private:
    static TreeNode<int>* deserializeHelper(const std::vector<std::string>& tokens, 
                                           int& index) {
        if (static_cast<size_t>(index) >= tokens.size() || tokens[index] == "null") {
            index++;
            return nullptr;
        }
        
        TreeNode<int>* node = new TreeNode<int>(std::stoi(tokens[index++]));
        node->left = deserializeHelper(tokens, index);
        node->right = deserializeHelper(tokens, index);
        
        return node;
    }

public:
    /**
     * Find lowest common ancestor in BST
     * Time Complexity: O(h)
     * Space Complexity: O(1) iterative, O(h) recursive
     */
    template<typename T>
    static TreeNode<T>* lowestCommonAncestorBST(TreeNode<T>* root, 
                                                TreeNode<T>* p, TreeNode<T>* q) {
        while (root != nullptr) {
            if (p->data < root->data && q->data < root->data) {
                root = root->left;
            } else if (p->data > root->data && q->data > root->data) {
                root = root->right;
            } else {
                return root;
            }
        }
        return nullptr;
    }
    
    /**
     * Find lowest common ancestor in general binary tree
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    template<typename T>
    static TreeNode<T>* lowestCommonAncestor(TreeNode<T>* root, 
                                            TreeNode<T>* p, TreeNode<T>* q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        
        TreeNode<T>* left = lowestCommonAncestor(root->left, p, q);
        TreeNode<T>* right = lowestCommonAncestor(root->right, p, q);
        
        if (left != nullptr && right != nullptr) {
            return root;
        }
        
        return (left != nullptr) ? left : right;
    }
    
    /**
     * Convert BST to greater sum tree
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    template<typename T>
    static void bstToGST(TreeNode<T>* root) {
        T sum = 0;
        bstToGSTHelper(root, sum);
    }
    
private:
    template<typename T>
    static void bstToGSTHelper(TreeNode<T>* node, T& sum) {
        if (node == nullptr) {
            return;
        }
        
        // Reverse inorder traversal (right -> root -> left)
        bstToGSTHelper(node->right, sum);
        sum += node->data;
        node->data = sum;
        bstToGSTHelper(node->left, sum);
    }

public:
    /**
     * Count number of nodes in complete tree efficiently
     * Time Complexity: O(log²n)
     * Space Complexity: O(log n)
     */
    template<typename T>
    static int countNodes(TreeNode<T>* root) {
        if (root == nullptr) {
            return 0;
        }
        
        int leftDepth = getDepth(root, true);
        int rightDepth = getDepth(root, false);
        
        if (leftDepth == rightDepth) {
            // Perfect binary tree
            return (1 << leftDepth) - 1;
        } else {
            // Recursively count left and right subtrees
            return 1 + countNodes(root->left) + countNodes(root->right);
        }
    }
    
private:
    template<typename T>
    static int getDepth(TreeNode<T>* node, bool goLeft) {
        int depth = 0;
        while (node != nullptr) {
            depth++;
            node = goLeft ? node->left : node->right;
        }
        return depth;
    }
};

/**
 * Tree Comparison and Morphing
 */
class TreeComparator {
public:
    /**
     * Check if two trees are identical
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    template<typename T>
    static bool isSameTree(TreeNode<T>* p, TreeNode<T>* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        }
        
        if (p == nullptr || q == nullptr) {
            return false;
        }
        
        return (p->data == q->data) && 
               isSameTree(p->left, q->left) && 
               isSameTree(p->right, q->right);
    }
    
    /**
     * Check if tree t is subtree of tree s
     * Time Complexity: O(m * n) where m, n are sizes of trees
     * Space Complexity: O(max(h1, h2))
     */
    template<typename T>
    static bool isSubtree(TreeNode<T>* s, TreeNode<T>* t) {
        if (s == nullptr) {
            return t == nullptr;
        }
        
        return isSameTree(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
    }
    
    /**
     * Check if one tree is mirror of another
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    template<typename T>
    static bool isMirror(TreeNode<T>* tree1, TreeNode<T>* tree2) {
        if (tree1 == nullptr && tree2 == nullptr) {
            return true;
        }
        
        if (tree1 == nullptr || tree2 == nullptr) {
            return false;
        }
        
        return (tree1->data == tree2->data) &&
               isMirror(tree1->left, tree2->right) &&
               isMirror(tree1->right, tree2->left);
    }
    
    /**
     * Check if tree is symmetric
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    template<typename T>
    static bool isSymmetric(TreeNode<T>* root) {
        if (root == nullptr) {
            return true;
        }
        
        return isMirror(root->left, root->right);
    }
};

// Utility functions for testing
template<typename T>
void deleteTree(TreeNode<T>* root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

template<typename T>
void printInorder(TreeNode<T>* root) {
    if (root != nullptr) {
        printInorder(root->left);
        std::cout << root->data << " ";
        printInorder(root->right);
    }
}

// Demonstration function
void demonstrateTreeApplications() {
    std::cout << "=== Tree Applications Demonstration ===" << std::endl;
    
    // Create a sample BST
    TreeNode<int>* root = new TreeNode<int>(50);
    root->left = new TreeNode<int>(30);
    root->right = new TreeNode<int>(70);
    root->left->left = new TreeNode<int>(20);
    root->left->right = new TreeNode<int>(40);
    root->right->left = new TreeNode<int>(60);
    root->right->right = new TreeNode<int>(80);
    
    std::cout << "Original tree (inorder): ";
    printInorder(root);
    std::cout << std::endl;
    
    // Test validation
    std::cout << "\nValidation Tests:" << std::endl;
    std::cout << "Is valid BST: " << std::boolalpha 
              << TreeValidator::isValidBST(root) << std::endl;
    std::cout << "Is balanced: " << std::boolalpha 
              << TreeValidator::isBalanced(root) << std::endl;
    std::cout << "Is complete: " << std::boolalpha 
              << TreeValidator::isCompleteTree(root) << std::endl;
    
    // Test path finding
    std::cout << "\nPath Finding Tests:" << std::endl;
    auto allPaths = TreePathFinder::findAllPaths(root);
    std::cout << "All root-to-leaf paths:" << std::endl;
    for (const auto& path : allPaths) {
        for (int val : path) {
            std::cout << val << " -> ";
        }
        std::cout << "END" << std::endl;
    }
    
    std::cout << "Has path sum 140: " << std::boolalpha 
              << TreePathFinder::hasPathSum(root, 140) << std::endl;
    std::cout << "Max path sum: " << TreePathFinder::maxPathSum(root) << std::endl;
    
    // Test tree operations
    std::cout << "\nTree Operations:" << std::endl;
    std::string serialized = TreeOperations::serialize(root);
    std::cout << "Serialized tree: " << serialized << std::endl;
    
    // Test BST to GST conversion
    TreeNode<int>* gstRoot = new TreeNode<int>(4);
    gstRoot->left = new TreeNode<int>(1);
    gstRoot->right = new TreeNode<int>(6);
    gstRoot->left->left = new TreeNode<int>(0);
    gstRoot->left->right = new TreeNode<int>(2);
    gstRoot->right->left = new TreeNode<int>(5);
    gstRoot->right->right = new TreeNode<int>(7);
    gstRoot->left->right->right = new TreeNode<int>(3);
    gstRoot->right->right->right = new TreeNode<int>(8);
    
    std::cout << "Before GST conversion: ";
    printInorder(gstRoot);
    std::cout << std::endl;
    
    TreeOperations::bstToGST(gstRoot);
    std::cout << "After GST conversion: ";
    printInorder(gstRoot);
    std::cout << std::endl;
    
    // Test tree construction
    std::cout << "\nTree Construction:" << std::endl;
    std::vector<int> sortedArray = {1, 2, 3, 4, 5, 6, 7};
    TreeNode<int>* balancedBST = TreeBuilder::sortedArrayToBST(sortedArray);
    std::cout << "Balanced BST from sorted array: ";
    printInorder(balancedBST);
    std::cout << std::endl;
    
    // Cleanup
    deleteTree(root);
    deleteTree(gstRoot);
    deleteTree(balancedBST);
}