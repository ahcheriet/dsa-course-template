#include <gtest/gtest.h>
#include "../../assignments/week04-trees/tree_applications.cpp"
#include <vector>
#include <algorithm>
#include <limits>

// Helper function to create test trees
template<typename T>
TreeNode<T>* createSampleBST() {
    TreeNode<T>* root = new TreeNode<T>(50);
    root->left = new TreeNode<T>(30);
    root->right = new TreeNode<T>(70);
    root->left->left = new TreeNode<T>(20);
    root->left->right = new TreeNode<T>(40);
    root->right->left = new TreeNode<T>(60);
    root->right->right = new TreeNode<T>(80);
    return root;
}

template<typename T>
TreeNode<T>* createUnbalancedTree() {
    TreeNode<T>* root = new TreeNode<T>(1);
    root->right = new TreeNode<T>(2);
    root->right->right = new TreeNode<T>(3);
    root->right->right->right = new TreeNode<T>(4);
    return root;
}

template<typename T>
TreeNode<T>* createCompleteTree() {
    TreeNode<T>* root = new TreeNode<T>(1);
    root->left = new TreeNode<T>(2);
    root->right = new TreeNode<T>(3);
    root->left->left = new TreeNode<T>(4);
    root->left->right = new TreeNode<T>(5);
    root->right->left = new TreeNode<T>(6);
    return root;
}

// Tree Validation Tests
class TreeValidatorTest : public ::testing::Test {
protected:
    void TearDown() override {
        if (bst) deleteTree(bst);
        if (invalidBST) deleteTree(invalidBST);
        if (unbalanced) deleteTree(unbalanced);
        if (complete) deleteTree(complete);
    }
    
    TreeNode<int>* bst = nullptr;
    TreeNode<int>* invalidBST = nullptr;
    TreeNode<int>* unbalanced = nullptr;
    TreeNode<int>* complete = nullptr;
};

TEST_F(TreeValidatorTest, ValidBSTTest) {
    bst = createSampleBST<int>();
    EXPECT_TRUE(TreeValidator::isValidBST(bst));
    
    // Test with single node
    TreeNode<int>* singleNode = new TreeNode<int>(5);
    EXPECT_TRUE(TreeValidator::isValidBST(singleNode));
    deleteTree(singleNode);
    
    // Test with empty tree
    EXPECT_TRUE(TreeValidator::isValidBST<int>(nullptr));
}

TEST_F(TreeValidatorTest, InvalidBSTTest) {
    // Create invalid BST where right child of left subtree > root
    invalidBST = new TreeNode<int>(50);
    invalidBST->left = new TreeNode<int>(30);
    invalidBST->right = new TreeNode<int>(70);
    invalidBST->left->right = new TreeNode<int>(60); // This violates BST property
    
    EXPECT_FALSE(TreeValidator::isValidBST(invalidBST));
}

TEST_F(TreeValidatorTest, CompleteTreeTest) {
    complete = createCompleteTree<int>();
    EXPECT_TRUE(TreeValidator::isCompleteTree(complete));
    
    // Test incomplete tree
    TreeNode<int>* incomplete = new TreeNode<int>(1);
    incomplete->left = new TreeNode<int>(2);
    incomplete->right = new TreeNode<int>(3);
    incomplete->left->left = new TreeNode<int>(4);
    incomplete->right->left = new TreeNode<int>(5); // Gap in level
    
    EXPECT_FALSE(TreeValidator::isCompleteTree(incomplete));
    deleteTree(incomplete);
    
    // Test empty tree
    EXPECT_TRUE(TreeValidator::isCompleteTree<int>(nullptr));
}

TEST_F(TreeValidatorTest, BalancedTreeTest) {
    bst = createSampleBST<int>();
    EXPECT_TRUE(TreeValidator::isBalanced(bst));
    
    unbalanced = createUnbalancedTree<int>();
    EXPECT_FALSE(TreeValidator::isBalanced(unbalanced));
    
    // Test empty tree
    EXPECT_TRUE(TreeValidator::isBalanced<int>(nullptr));
    
    // Test single node
    TreeNode<int>* singleNode = new TreeNode<int>(5);
    EXPECT_TRUE(TreeValidator::isBalanced(singleNode));
    deleteTree(singleNode);
}

// Tree Path Tests
class TreePathFinderTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create tree:     10
        //                 /  \
        //                5    15
        //               / \     \
        //              3   7    20
        root = new TreeNode<int>(10);
        root->left = new TreeNode<int>(5);
        root->right = new TreeNode<int>(15);
        root->left->left = new TreeNode<int>(3);
        root->left->right = new TreeNode<int>(7);
        root->right->right = new TreeNode<int>(20);
    }
    
    void TearDown() override {
        deleteTree(root);
    }
    
    TreeNode<int>* root;
};

TEST_F(TreePathFinderTest, FindAllPathsTest) {
    auto paths = TreePathFinder::findAllPaths(root);
    
    EXPECT_EQ(paths.size(), 3); // Three leaf nodes
    
    // Sort paths for consistent testing
    std::sort(paths.begin(), paths.end());
    
    std::vector<std::vector<int>> expected = {
        {10, 5, 3},
        {10, 5, 7},
        {10, 15, 20}
    };
    std::sort(expected.begin(), expected.end());
    
    EXPECT_EQ(paths, expected);
}

TEST_F(TreePathFinderTest, HasPathSumTest) {
    EXPECT_TRUE(TreePathFinder::hasPathSum(root, 18));  // 10 + 5 + 3
    EXPECT_TRUE(TreePathFinder::hasPathSum(root, 22));  // 10 + 5 + 7
    EXPECT_TRUE(TreePathFinder::hasPathSum(root, 45));  // 10 + 15 + 20
    EXPECT_FALSE(TreePathFinder::hasPathSum(root, 100));
    
    // Test single node
    TreeNode<int>* singleNode = new TreeNode<int>(5);
    EXPECT_TRUE(TreePathFinder::hasPathSum(singleNode, 5));
    EXPECT_FALSE(TreePathFinder::hasPathSum(singleNode, 10));
    deleteTree(singleNode);
    
    // Test empty tree
    EXPECT_FALSE(TreePathFinder::hasPathSum<int>(nullptr, 0));
}

TEST_F(TreePathFinderTest, FindPathsWithSumTest) {
    auto paths = TreePathFinder::findPathsWithSum(root, 22);
    
    EXPECT_EQ(paths.size(), 1);
    EXPECT_EQ(paths[0], std::vector<int>({10, 5, 7}));
    
    // Test no paths found
    auto noPaths = TreePathFinder::findPathsWithSum(root, 999);
    EXPECT_TRUE(noPaths.empty());
}

TEST_F(TreePathFinderTest, MaxPathSumTest) {
    int maxSum = TreePathFinder::maxPathSum(root);
    // Maximum path is 3->5->10->15->20 = 55 (not going through root) or 7->5->10->15->20 = 57
    EXPECT_EQ(maxSum, 57);
    
    // Test with negative values
    TreeNode<int>* negativeTree = new TreeNode<int>(-3);
    negativeTree->left = new TreeNode<int>(3);
    negativeTree->right = new TreeNode<int>(3);
    negativeTree->left->left = new TreeNode<int>(3);
    negativeTree->left->right = new TreeNode<int>(2);
    
    int negativeMaxSum = TreePathFinder::maxPathSum(negativeTree);
    EXPECT_EQ(negativeMaxSum, 8); // 3->3->2 = 8
    
    deleteTree(negativeTree);
}

// Tree Builder Tests
class TreeBuilderTest : public ::testing::Test {
protected:
    void TearDown() override {
        if (builtTree) deleteTree(builtTree);
    }
    
    TreeNode<int>* builtTree = nullptr;
};

TEST_F(TreeBuilderTest, SortedArrayToBSTTest) {
    std::vector<int> sortedArray = {1, 2, 3, 4, 5, 6, 7};
    builtTree = TreeBuilder::sortedArrayToBST(sortedArray);
    
    EXPECT_TRUE(TreeValidator::isValidBST(builtTree));
    EXPECT_TRUE(TreeValidator::isBalanced(builtTree));
    
    // Verify inorder traversal gives original array
    std::vector<int> inorder;
    std::function<void(TreeNode<int>*)> traverse = [&](TreeNode<int>* node) {
        if (node) {
            traverse(node->left);
            inorder.push_back(node->data);
            traverse(node->right);
        }
    };
    traverse(builtTree);
    
    EXPECT_EQ(inorder, sortedArray);
}

TEST_F(TreeBuilderTest, BuildTreeFromTraversalsTest) {
    std::vector<int> preorder = {3, 9, 20, 15, 7};
    std::vector<int> inorder = {9, 3, 15, 20, 7};
    
    builtTree = TreeBuilder::buildTree(preorder, inorder);
    
    EXPECT_EQ(builtTree->data, 3);
    EXPECT_EQ(builtTree->left->data, 9);
    EXPECT_EQ(builtTree->right->data, 20);
    EXPECT_EQ(builtTree->right->left->data, 15);
    EXPECT_EQ(builtTree->right->right->data, 7);
}

TEST_F(TreeBuilderTest, EmptyArrayTest) {
    std::vector<int> emptyArray;
    builtTree = TreeBuilder::sortedArrayToBST(emptyArray);
    
    EXPECT_EQ(builtTree, nullptr);
}

// Tree Operations Tests
class TreeOperationsTest : public ::testing::Test {
protected:
    void SetUp() override {
        root = createSampleBST<int>();
    }
    
    void TearDown() override {
        deleteTree(root);
        if (deserializedTree) deleteTree(deserializedTree);
    }
    
    TreeNode<int>* root;
    TreeNode<int>* deserializedTree = nullptr;
};

TEST_F(TreeOperationsTest, SerializeDeserializeTest) {
    std::string serialized = TreeOperations::serialize(root);
    EXPECT_FALSE(serialized.empty());
    
    deserializedTree = TreeOperations::deserialize(serialized);
    
    // Verify trees are identical
    EXPECT_TRUE(TreeComparator::isSameTree(root, deserializedTree));
}

TEST_F(TreeOperationsTest, LowestCommonAncestorBSTTest) {
    TreeNode<int>* node20 = root->left->left;
    TreeNode<int>* node40 = root->left->right;
    TreeNode<int>* node60 = root->right->left;
    TreeNode<int>* node80 = root->right->right;
    
    TreeNode<int>* lca1 = TreeOperations::lowestCommonAncestorBST(root, node20, node40);
    EXPECT_EQ(lca1->data, 30);
    
    TreeNode<int>* lca2 = TreeOperations::lowestCommonAncestorBST(root, node20, node80);
    EXPECT_EQ(lca2->data, 50);
    
    TreeNode<int>* lca3 = TreeOperations::lowestCommonAncestorBST(root, node60, node80);
    EXPECT_EQ(lca3->data, 70);
}

TEST_F(TreeOperationsTest, LowestCommonAncestorGeneralTest) {
    TreeNode<int>* node20 = root->left->left;
    TreeNode<int>* node40 = root->left->right;
    // TreeNode<int>* node60 = root->right->left; // Unused in this test
    TreeNode<int>* node80 = root->right->right;
    
    TreeNode<int>* lca1 = TreeOperations::lowestCommonAncestor(root, node20, node40);
    EXPECT_EQ(lca1->data, 30);
    
    TreeNode<int>* lca2 = TreeOperations::lowestCommonAncestor(root, node20, node80);
    EXPECT_EQ(lca2->data, 50);
}

TEST_F(TreeOperationsTest, BSTToGSTTest) {
    // Create simple BST: 0,1,2
    TreeNode<int>* gstRoot = new TreeNode<int>(1);
    gstRoot->left = new TreeNode<int>(0);
    gstRoot->right = new TreeNode<int>(2);
    
    TreeOperations::bstToGST(gstRoot);
    
    // After conversion: greater sum tree
    // 0 -> 3 (0+1+2), 1 -> 3 (1+2), 2 -> 2
    EXPECT_EQ(gstRoot->left->data, 3);
    EXPECT_EQ(gstRoot->data, 3);
    EXPECT_EQ(gstRoot->right->data, 2);
    
    deleteTree(gstRoot);
}

TEST_F(TreeOperationsTest, CountNodesCompleteTreeTest) {
    TreeNode<int>* completeTree = new TreeNode<int>(1);
    completeTree->left = new TreeNode<int>(2);
    completeTree->right = new TreeNode<int>(3);
    completeTree->left->left = new TreeNode<int>(4);
    completeTree->left->right = new TreeNode<int>(5);
    completeTree->right->left = new TreeNode<int>(6);
    
    int count = TreeOperations::countNodes(completeTree);
    EXPECT_EQ(count, 6);
    
    deleteTree(completeTree);
    
    // Test empty tree
    EXPECT_EQ(TreeOperations::countNodes<int>(nullptr), 0);
}

// Tree Comparator Tests
class TreeComparatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        tree1 = createSampleBST<int>();
        tree2 = createSampleBST<int>();
        differentTree = new TreeNode<int>(100);
        differentTree->left = new TreeNode<int>(50);
        differentTree->right = new TreeNode<int>(150);
    }
    
    void TearDown() override {
        deleteTree(tree1);
        deleteTree(tree2);
        deleteTree(differentTree);
        if (mirrorTree) deleteTree(mirrorTree);
        if (symmetricTree) deleteTree(symmetricTree);
    }
    
    TreeNode<int>* tree1;
    TreeNode<int>* tree2;
    TreeNode<int>* differentTree;
    TreeNode<int>* mirrorTree = nullptr;
    TreeNode<int>* symmetricTree = nullptr;
};

TEST_F(TreeComparatorTest, SameTreeTest) {
    EXPECT_TRUE(TreeComparator::isSameTree(tree1, tree2));
    EXPECT_FALSE(TreeComparator::isSameTree(tree1, differentTree));
    EXPECT_TRUE(TreeComparator::isSameTree<int>(nullptr, nullptr));
    EXPECT_FALSE(TreeComparator::isSameTree(tree1, static_cast<TreeNode<int>*>(nullptr)));
}

TEST_F(TreeComparatorTest, IsSubtreeTest) {
    // Create subtree
    TreeNode<int>* subtree = new TreeNode<int>(30);
    subtree->left = new TreeNode<int>(20);
    subtree->right = new TreeNode<int>(40);
    
    EXPECT_TRUE(TreeComparator::isSubtree(tree1, subtree));
    EXPECT_FALSE(TreeComparator::isSubtree(tree1, differentTree));
    
    deleteTree(subtree);
}

TEST_F(TreeComparatorTest, IsMirrorTest) {
    // Create mirror of tree1
    mirrorTree = new TreeNode<int>(50);
    mirrorTree->left = new TreeNode<int>(70);
    mirrorTree->right = new TreeNode<int>(30);
    mirrorTree->left->left = new TreeNode<int>(80);
    mirrorTree->left->right = new TreeNode<int>(60);
    mirrorTree->right->left = new TreeNode<int>(40);
    mirrorTree->right->right = new TreeNode<int>(20);
    
    EXPECT_TRUE(TreeComparator::isMirror(tree1, mirrorTree));
    EXPECT_FALSE(TreeComparator::isMirror(tree1, tree2));
}

TEST_F(TreeComparatorTest, IsSymmetricTest) {
    // Create symmetric tree
    symmetricTree = new TreeNode<int>(1);
    symmetricTree->left = new TreeNode<int>(2);
    symmetricTree->right = new TreeNode<int>(2);
    symmetricTree->left->left = new TreeNode<int>(3);
    symmetricTree->left->right = new TreeNode<int>(4);
    symmetricTree->right->left = new TreeNode<int>(4);
    symmetricTree->right->right = new TreeNode<int>(3);
    
    EXPECT_TRUE(TreeComparator::isSymmetric(symmetricTree));
    EXPECT_FALSE(TreeComparator::isSymmetric(tree1));
    EXPECT_TRUE(TreeComparator::isSymmetric<int>(nullptr));
}

// Edge Cases and Error Handling
TEST(TreeApplicationsEdgeCasesTest, NullTreeOperations) {
    // Test all operations with null trees
    EXPECT_TRUE(TreeValidator::isValidBST<int>(nullptr));
    EXPECT_TRUE(TreeValidator::isCompleteTree<int>(nullptr));
    EXPECT_TRUE(TreeValidator::isBalanced<int>(nullptr));
    
    auto paths = TreePathFinder::findAllPaths<int>(nullptr);
    EXPECT_TRUE(paths.empty());
    
    EXPECT_FALSE(TreePathFinder::hasPathSum<int>(nullptr, 5));
    
    auto pathsWithSum = TreePathFinder::findPathsWithSum<int>(nullptr, 5);
    EXPECT_TRUE(pathsWithSum.empty());
    
    EXPECT_EQ(TreeOperations::countNodes<int>(nullptr), 0);
}

TEST(TreeApplicationsEdgeCasesTest, SingleNodeOperations) {
    TreeNode<int>* singleNode = new TreeNode<int>(42);
    
    EXPECT_TRUE(TreeValidator::isValidBST(singleNode));
    EXPECT_TRUE(TreeValidator::isCompleteTree(singleNode));
    EXPECT_TRUE(TreeValidator::isBalanced(singleNode));
    
    auto paths = TreePathFinder::findAllPaths(singleNode);
    EXPECT_EQ(paths.size(), 1);
    EXPECT_EQ(paths[0], std::vector<int>({42}));
    
    EXPECT_TRUE(TreePathFinder::hasPathSum(singleNode, 42));
    EXPECT_FALSE(TreePathFinder::hasPathSum(singleNode, 100));
    
    EXPECT_EQ(TreePathFinder::maxPathSum(singleNode), 42);
    
    EXPECT_EQ(TreeOperations::countNodes(singleNode), 1);
    
    deleteTree(singleNode);
}

// Performance Tests
TEST(TreeApplicationsPerformanceTest, LargeTreeOperations) {
    const int NUM_NODES = 1000;
    
    // Create balanced BST from sorted array
    std::vector<int> sortedArray;
    for (int i = 1; i <= NUM_NODES; i++) {
        sortedArray.push_back(i);
    }
    
    TreeNode<int>* largeTree = TreeBuilder::sortedArrayToBST(sortedArray);
    
    // Test validation operations
    EXPECT_TRUE(TreeValidator::isValidBST(largeTree));
    EXPECT_TRUE(TreeValidator::isBalanced(largeTree));
    
    // Test path operations - find a valid path sum in the balanced tree
    // The root value will exist in some path from root to leaf
    auto paths = TreePathFinder::findAllPaths(largeTree);
    EXPECT_FALSE(paths.empty());
    if (!paths.empty()) {
        // Take the sum of the first path as our test case
        int testSum = 0;
        for (int val : paths[0]) {
            testSum += val;
        }
        EXPECT_TRUE(TreePathFinder::hasPathSum(largeTree, testSum));
    }
    
    // Test other operations
    EXPECT_EQ(TreeOperations::countNodes(largeTree), NUM_NODES);
    
    deleteTree(largeTree);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}