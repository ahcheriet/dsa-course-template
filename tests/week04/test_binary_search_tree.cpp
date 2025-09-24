#include <gtest/gtest.h>
#include "../../assignments/week04-trees/binary_search_tree.cpp"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <cmath>

class BSTTest : public ::testing::Test {
protected:
    void SetUp() override {
        bst = new BinarySearchTree<int>();
    }
    
    void TearDown() override {
        delete bst;
    }
    
    BinarySearchTree<int>* bst;
};

// Basic Operations Tests
TEST_F(BSTTest, EmptyTreeOperations) {
    EXPECT_TRUE(bst->isEmpty());
    EXPECT_EQ(bst->size(), 0);
    EXPECT_EQ(bst->getHeight(), -1);
    EXPECT_FALSE(bst->contains(5));
    
    EXPECT_THROW(bst->findMin(), std::runtime_error);
    EXPECT_THROW(bst->findMax(), std::runtime_error);
}

TEST_F(BSTTest, SingleNodeOperations) {
    bst->insert(50);
    
    EXPECT_FALSE(bst->isEmpty());
    EXPECT_EQ(bst->size(), 1);
    EXPECT_EQ(bst->getHeight(), 0);
    EXPECT_TRUE(bst->contains(50));
    EXPECT_FALSE(bst->contains(25));
    
    EXPECT_EQ(bst->findMin(), 50);
    EXPECT_EQ(bst->findMax(), 50);
}

TEST_F(BSTTest, MultipleInsertions) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    EXPECT_EQ(bst->size(), values.size());
    EXPECT_EQ(bst->getHeight(), 2);
    
    for (int val : values) {
        EXPECT_TRUE(bst->contains(val));
    }
    
    EXPECT_EQ(bst->findMin(), 20);
    EXPECT_EQ(bst->findMax(), 80);
}

TEST_F(BSTTest, DuplicateInsertions) {
    bst->insert(50);
    bst->insert(50);
    bst->insert(50);
    
    EXPECT_EQ(bst->size(), 1);
    EXPECT_TRUE(bst->contains(50));
}

// Traversal Tests
TEST_F(BSTTest, InorderTraversal) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    auto inorder = bst->inorderTraversal();
    std::vector<int> expected = {20, 30, 40, 50, 60, 70, 80};
    
    EXPECT_EQ(inorder, expected);
}

TEST_F(BSTTest, InorderTraversalIterative) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    auto inorderRecursive = bst->inorderTraversal();
    auto inorderIterative = bst->inorderTraversalIterative();
    
    EXPECT_EQ(inorderRecursive, inorderIterative);
}

TEST_F(BSTTest, PreorderTraversal) {
    std::vector<int> values = {50, 30, 20, 40, 70, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    auto preorder = bst->preorderTraversal();
    std::vector<int> expected = {50, 30, 20, 40, 70, 60, 80};
    
    EXPECT_EQ(preorder, expected);
}

TEST_F(BSTTest, PreorderTraversalIterative) {
    std::vector<int> values = {50, 30, 20, 40, 70, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    auto preorderRecursive = bst->preorderTraversal();
    auto preorderIterative = bst->preorderTraversalIterative();
    
    EXPECT_EQ(preorderRecursive, preorderIterative);
}

TEST_F(BSTTest, PostorderTraversal) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    auto postorder = bst->postorderTraversal();
    std::vector<int> expected = {20, 40, 30, 60, 80, 70, 50};
    
    EXPECT_EQ(postorder, expected);
}

TEST_F(BSTTest, LevelOrderTraversal) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    auto levelorder = bst->levelOrderTraversal();
    std::vector<int> expected = {50, 30, 70, 20, 40, 60, 80};
    
    EXPECT_EQ(levelorder, expected);
}

// Deletion Tests
TEST_F(BSTTest, DeleteLeafNode) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    bst->remove(20);
    
    EXPECT_EQ(bst->size(), 6);
    EXPECT_FALSE(bst->contains(20));
    
    auto inorder = bst->inorderTraversal();
    std::vector<int> expected = {30, 40, 50, 60, 70, 80};
    EXPECT_EQ(inorder, expected);
}

TEST_F(BSTTest, DeleteNodeWithOneChild) {
    std::vector<int> values = {50, 30, 70, 20, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    bst->remove(30);
    
    EXPECT_EQ(bst->size(), 5);
    EXPECT_FALSE(bst->contains(30));
    
    auto inorder = bst->inorderTraversal();
    std::vector<int> expected = {20, 50, 60, 70, 80};
    EXPECT_EQ(inorder, expected);
}

TEST_F(BSTTest, DeleteNodeWithTwoChildren) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    bst->remove(50);
    
    EXPECT_EQ(bst->size(), 6);
    EXPECT_FALSE(bst->contains(50));
    
    auto inorder = bst->inorderTraversal();
    std::vector<int> expected = {20, 30, 40, 60, 70, 80};
    EXPECT_EQ(inorder, expected);
}

TEST_F(BSTTest, DeleteRoot) {
    bst->insert(50);
    bst->remove(50);
    
    EXPECT_TRUE(bst->isEmpty());
    EXPECT_EQ(bst->size(), 0);
}

TEST_F(BSTTest, DeleteNonExistentNode) {
    std::vector<int> values = {50, 30, 70};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    size_t originalSize = bst->size();
    bst->remove(25);
    
    EXPECT_EQ(bst->size(), originalSize);
}

// Advanced Operations Tests
TEST_F(BSTTest, KthSmallestElement) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    EXPECT_EQ(bst->kthSmallest(1), 20);
    EXPECT_EQ(bst->kthSmallest(3), 40);
    EXPECT_EQ(bst->kthSmallest(7), 80);
    
    EXPECT_THROW(bst->kthSmallest(0), std::out_of_range);
    EXPECT_THROW(bst->kthSmallest(8), std::out_of_range);
}

TEST_F(BSTTest, LowestCommonAncestor) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    EXPECT_EQ(bst->lowestCommonAncestor(20, 40), 30);
    EXPECT_EQ(bst->lowestCommonAncestor(20, 80), 50);
    EXPECT_EQ(bst->lowestCommonAncestor(60, 80), 70);
    EXPECT_EQ(bst->lowestCommonAncestor(30, 30), 30);
}

// Copy Constructor and Assignment Tests
TEST_F(BSTTest, CopyConstructor) {
    std::vector<int> values = {50, 30, 70, 20, 40};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    BinarySearchTree<int> copy(*bst);
    
    EXPECT_EQ(copy.size(), bst->size());
    EXPECT_EQ(copy.getHeight(), bst->getHeight());
    
    auto originalInorder = bst->inorderTraversal();
    auto copyInorder = copy.inorderTraversal();
    EXPECT_EQ(originalInorder, copyInorder);
    
    // Modify original, copy should remain unchanged
    bst->insert(90);
    EXPECT_NE(copy.size(), bst->size());
}

TEST_F(BSTTest, AssignmentOperator) {
    std::vector<int> values = {50, 30, 70, 20, 40};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    BinarySearchTree<int> assigned;
    assigned.insert(100); // Add something to test proper assignment
    
    assigned = *bst;
    
    EXPECT_EQ(assigned.size(), bst->size());
    EXPECT_EQ(assigned.getHeight(), bst->getHeight());
    
    auto originalInorder = bst->inorderTraversal();
    auto assignedInorder = assigned.inorderTraversal();
    EXPECT_EQ(originalInorder, assignedInorder);
}

// Edge Cases and Error Handling
TEST_F(BSTTest, MakeEmpty) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        bst->insert(val);
    }
    
    EXPECT_FALSE(bst->isEmpty());
    
    bst->makeEmpty();
    
    EXPECT_TRUE(bst->isEmpty());
    EXPECT_EQ(bst->size(), 0);
    EXPECT_EQ(bst->getHeight(), -1);
}

TEST_F(BSTTest, StressTest) {
    const int NUM_ELEMENTS = 1000;
    std::vector<int> values;
    
    // Insert random values
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        values.push_back(i);
    }
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);
    
    for (int val : values) {
        bst->insert(val);
    }
    
    EXPECT_EQ(bst->size(), NUM_ELEMENTS);
    
    // Verify all values are present
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        EXPECT_TRUE(bst->contains(i));
    }
    
    // Verify inorder traversal is sorted
    auto inorder = bst->inorderTraversal();
    EXPECT_TRUE(std::is_sorted(inorder.begin(), inorder.end()));
    EXPECT_EQ(inorder.size(), NUM_ELEMENTS);
}

TEST_F(BSTTest, DegenrateCases) {
    // Test ascending insertion (worst case for BST)
    for (int i = 1; i <= 10; i++) {
        bst->insert(i);
    }
    
    EXPECT_EQ(bst->size(), 10);
    EXPECT_EQ(bst->getHeight(), 9); // Completely unbalanced
    EXPECT_EQ(bst->findMin(), 1);
    EXPECT_EQ(bst->findMax(), 10);
    
    auto inorder = bst->inorderTraversal();
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(inorder, expected);
}

// Template Tests with Different Types
TEST(BSTTemplateTest, StringBST) {
    BinarySearchTree<std::string> stringBST;
    
    std::vector<std::string> words = {"hello", "world", "apple", "banana", "zebra"};
    
    for (const auto& word : words) {
        stringBST.insert(word);
    }
    
    EXPECT_EQ(stringBST.size(), words.size());
    EXPECT_TRUE(stringBST.contains("hello"));
    EXPECT_FALSE(stringBST.contains("missing"));
    
    auto inorder = stringBST.inorderTraversal();
    std::vector<std::string> expected = {"apple", "banana", "hello", "world", "zebra"};
    EXPECT_EQ(inorder, expected);
}

TEST(BSTTemplateTest, DoubleBST) {
    BinarySearchTree<double> doubleBST;
    
    std::vector<double> values = {3.14, 2.71, 1.41, 0.57, 4.47};
    
    for (double val : values) {
        doubleBST.insert(val);
    }
    
    EXPECT_EQ(doubleBST.size(), values.size());
    EXPECT_DOUBLE_EQ(doubleBST.findMin(), 0.57);
    EXPECT_DOUBLE_EQ(doubleBST.findMax(), 4.47);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}