#include <gtest/gtest.h>
#include "../../assignments/week04-trees/avl_tree.cpp"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <cmath>

class AVLTest : public ::testing::Test {
protected:
    void SetUp() override {
        avl = new AVLTree<int>();
    }
    
    void TearDown() override {
        delete avl;
    }
    
    AVLTree<int>* avl;
};

// Basic Operations Tests
TEST_F(AVLTest, EmptyTreeOperations) {
    EXPECT_TRUE(avl->isEmpty());
    EXPECT_EQ(avl->size(), 0);
    EXPECT_EQ(avl->getHeight(), -1);
    EXPECT_FALSE(avl->contains(5));
    EXPECT_TRUE(avl->isBalanced());
    
    EXPECT_THROW(avl->findMin(), std::runtime_error);
    EXPECT_THROW(avl->findMax(), std::runtime_error);
}

TEST_F(AVLTest, SingleNodeOperations) {
    avl->insert(50);
    
    EXPECT_FALSE(avl->isEmpty());
    EXPECT_EQ(avl->size(), 1);
    EXPECT_EQ(avl->getHeight(), 0);
    EXPECT_TRUE(avl->contains(50));
    EXPECT_FALSE(avl->contains(25));
    EXPECT_TRUE(avl->isBalanced());
    
    EXPECT_EQ(avl->findMin(), 50);
    EXPECT_EQ(avl->findMax(), 50);
}

// Balance Testing - This is the key feature of AVL trees
TEST_F(AVLTest, RightRotation) {
    // Insert values that would cause left-heavy imbalance
    avl->insert(30);
    avl->insert(20);
    avl->insert(10); // This should trigger right rotation
    
    EXPECT_TRUE(avl->isBalanced());
    EXPECT_EQ(avl->getHeight(), 1); // Should be balanced with height 1
    
    auto inorder = avl->inorderTraversal();
    std::vector<int> expected = {10, 20, 30};
    EXPECT_EQ(inorder, expected);
}

TEST_F(AVLTest, LeftRotation) {
    // Insert values that would cause right-heavy imbalance
    avl->insert(10);
    avl->insert(20);
    avl->insert(30); // This should trigger left rotation
    
    EXPECT_TRUE(avl->isBalanced());
    EXPECT_EQ(avl->getHeight(), 1); // Should be balanced with height 1
    
    auto inorder = avl->inorderTraversal();
    std::vector<int> expected = {10, 20, 30};
    EXPECT_EQ(inorder, expected);
}

TEST_F(AVLTest, LeftRightRotation) {
    // Insert values that would cause left-right imbalance
    avl->insert(30);
    avl->insert(10);
    avl->insert(20); // This should trigger left-right rotation
    
    EXPECT_TRUE(avl->isBalanced());
    EXPECT_EQ(avl->getHeight(), 1);
    
    auto inorder = avl->inorderTraversal();
    std::vector<int> expected = {10, 20, 30};
    EXPECT_EQ(inorder, expected);
}

TEST_F(AVLTest, RightLeftRotation) {
    // Insert values that would cause right-left imbalance
    avl->insert(10);
    avl->insert(30);
    avl->insert(20); // This should trigger right-left rotation
    
    EXPECT_TRUE(avl->isBalanced());
    EXPECT_EQ(avl->getHeight(), 1);
    
    auto inorder = avl->inorderTraversal();
    std::vector<int> expected = {10, 20, 30};
    EXPECT_EQ(inorder, expected);
}

TEST_F(AVLTest, ComplexBalancing) {
    // Insert values that require multiple rotations
    std::vector<int> values = {10, 20, 30, 40, 50, 25};
    
    for (int val : values) {
        avl->insert(val);
        EXPECT_TRUE(avl->isBalanced()) << "Tree became unbalanced after inserting " << val;
    }
    
    EXPECT_EQ(avl->size(), values.size());
    EXPECT_LE(avl->getHeight(), 3); // AVL tree should have logarithmic height
    
    auto inorder = avl->inorderTraversal();
    std::vector<int> expected = {10, 20, 25, 30, 40, 50};
    EXPECT_EQ(inorder, expected);
}

// Insertion with Statistics
TEST_F(AVLTest, InsertionStatistics) {
    auto stats1 = avl->insertWithStats(50);
    EXPECT_TRUE(stats1.inserted);
    EXPECT_EQ(stats1.rotations, 0);
    
    auto stats2 = avl->insertWithStats(30);
    EXPECT_TRUE(stats2.inserted);
    EXPECT_EQ(stats2.rotations, 0);
    
    auto stats3 = avl->insertWithStats(10);
    EXPECT_TRUE(stats3.inserted);
    EXPECT_EQ(stats3.rotations, 1); // Should require one rotation
    
    // Try to insert duplicate
    auto stats4 = avl->insertWithStats(50);
    EXPECT_FALSE(stats4.inserted);
    EXPECT_EQ(stats4.rotations, 0);
}

// Deletion Tests with Balance Maintenance
TEST_F(AVLTest, DeletionMaintainsBalance) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    EXPECT_TRUE(avl->isBalanced());
    
    // Remove various nodes and check balance is maintained
    avl->remove(10);
    EXPECT_TRUE(avl->isBalanced());
    
    avl->remove(25);
    EXPECT_TRUE(avl->isBalanced());
    
    avl->remove(30);
    EXPECT_TRUE(avl->isBalanced());
    
    avl->remove(50); // Remove root
    EXPECT_TRUE(avl->isBalanced());
    
    EXPECT_EQ(avl->size(), values.size() - 4);
}

TEST_F(AVLTest, DeleteLeafNode) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    avl->remove(20);
    
    EXPECT_EQ(avl->size(), 6);
    EXPECT_FALSE(avl->contains(20));
    EXPECT_TRUE(avl->isBalanced());
    
    auto inorder = avl->inorderTraversal();
    std::vector<int> expected = {30, 40, 50, 60, 70, 80};
    EXPECT_EQ(inorder, expected);
}

TEST_F(AVLTest, DeleteNonExistentNode) {
    std::vector<int> values = {50, 30, 70};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    size_t originalSize = avl->size();
    avl->remove(25);
    
    EXPECT_EQ(avl->size(), originalSize);
    EXPECT_TRUE(avl->isBalanced());
}

// Traversal Tests
TEST_F(AVLTest, InorderTraversal) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    auto inorder = avl->inorderTraversal();
    std::vector<int> expected = {20, 30, 40, 50, 60, 70, 80};
    
    EXPECT_EQ(inorder, expected);
}

TEST_F(AVLTest, PreorderTraversal) {
    // Insert specific values to get predictable preorder
    avl->insert(50);
    avl->insert(30);
    avl->insert(70);
    avl->insert(20);
    avl->insert(40);
    avl->insert(60);
    avl->insert(80);
    
    auto preorder = avl->preorderTraversal();
    
    // The exact preorder depends on the AVL balancing
    // But we can verify it contains all elements
    EXPECT_EQ(preorder.size(), 7);
    std::sort(preorder.begin(), preorder.end());
    std::vector<int> expected = {20, 30, 40, 50, 60, 70, 80};
    EXPECT_EQ(preorder, expected);
}

TEST_F(AVLTest, LevelOrderTraversal) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    auto levelorder = avl->levelOrderTraversal();
    
    // Level order should contain all elements
    EXPECT_EQ(levelorder.size(), values.size());
    
    // Sort both to compare content
    std::sort(levelorder.begin(), levelorder.end());
    std::sort(values.begin(), values.end());
    EXPECT_EQ(levelorder, values);
}

// Range Query Tests
TEST_F(AVLTest, RangeQuery) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80, 10, 35, 65, 90};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    auto range = avl->rangeQuery(30, 70);
    std::vector<int> expected = {30, 35, 40, 50, 60, 65, 70};
    
    std::sort(range.begin(), range.end());
    EXPECT_EQ(range, expected);
}

TEST_F(AVLTest, RangeQueryEmpty) {
    std::vector<int> values = {50, 30, 70};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    auto range = avl->rangeQuery(80, 90);
    EXPECT_TRUE(range.empty());
}

TEST_F(AVLTest, RangeQuerySingleElement) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    auto range = avl->rangeQuery(50, 50);
    std::vector<int> expected = {50};
    
    EXPECT_EQ(range, expected);
}

// Copy Constructor and Assignment Tests
TEST_F(AVLTest, CopyConstructor) {
    std::vector<int> values = {50, 30, 70, 20, 40};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    AVLTree<int> copy(*avl);
    
    EXPECT_EQ(copy.size(), avl->size());
    EXPECT_EQ(copy.getHeight(), avl->getHeight());
    EXPECT_TRUE(copy.isBalanced());
    
    auto originalInorder = avl->inorderTraversal();
    auto copyInorder = copy.inorderTraversal();
    EXPECT_EQ(originalInorder, copyInorder);
    
    // Modify original, copy should remain unchanged
    avl->insert(90);
    EXPECT_NE(copy.size(), avl->size());
}

TEST_F(AVLTest, AssignmentOperator) {
    std::vector<int> values = {50, 30, 70, 20, 40};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    AVLTree<int> assigned;
    assigned.insert(100);
    
    assigned = *avl;
    
    EXPECT_EQ(assigned.size(), avl->size());
    EXPECT_EQ(assigned.getHeight(), avl->getHeight());
    EXPECT_TRUE(assigned.isBalanced());
    
    auto originalInorder = avl->inorderTraversal();
    auto assignedInorder = assigned.inorderTraversal();
    EXPECT_EQ(originalInorder, assignedInorder);
}

// Performance and Stress Tests
TEST_F(AVLTest, SequentialInsertionStressTest) {
    const int NUM_ELEMENTS = 100;
    
    // Insert elements in ascending order (worst case for unbalanced BST)
    for (int i = 1; i <= NUM_ELEMENTS; i++) {
        avl->insert(i);
        EXPECT_TRUE(avl->isBalanced()) << "Tree became unbalanced at element " << i;
    }
    
    EXPECT_EQ(avl->size(), NUM_ELEMENTS);
    
    // AVL tree should maintain logarithmic height even with sequential insertion
    int expectedMaxHeight = static_cast<int>(1.44 * std::log2(NUM_ELEMENTS + 2) - 0.328);
    EXPECT_LE(avl->getHeight(), expectedMaxHeight + 1); // Allow some tolerance
    
    // Verify all elements are present and in order
    auto inorder = avl->inorderTraversal();
    EXPECT_EQ(inorder.size(), NUM_ELEMENTS);
    EXPECT_TRUE(std::is_sorted(inorder.begin(), inorder.end()));
    
    for (int i = 1; i <= NUM_ELEMENTS; i++) {
        EXPECT_EQ(inorder[i-1], i);
    }
}

TEST_F(AVLTest, RandomInsertionStressTest) {
    const int NUM_ELEMENTS = 500;
    std::vector<int> values;
    
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        values.push_back(i);
    }
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);
    
    for (int val : values) {
        avl->insert(val);
        EXPECT_TRUE(avl->isBalanced());
    }
    
    EXPECT_EQ(avl->size(), NUM_ELEMENTS);
    
    // Verify all values are present
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        EXPECT_TRUE(avl->contains(i));
    }
    
    // Verify inorder traversal is sorted
    auto inorder = avl->inorderTraversal();
    EXPECT_TRUE(std::is_sorted(inorder.begin(), inorder.end()));
    EXPECT_EQ(inorder.size(), NUM_ELEMENTS);
}

TEST_F(AVLTest, MixedOperationsStressTest) {
    const int NUM_OPERATIONS = 200;
    
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        int operation = i % 3;
        int value = rand() % 100;
        
        switch (operation) {
            case 0: // Insert
                avl->insert(value);
                break;
            case 1: // Remove
                if (!avl->isEmpty()) {
                    avl->remove(value);
                }
                break;
            case 2: // Search
                avl->contains(value);
                break;
        }
        
        EXPECT_TRUE(avl->isBalanced()) << "Tree became unbalanced at operation " << i;
    }
}

// Edge Cases
TEST_F(AVLTest, MakeEmpty) {
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values) {
        avl->insert(val);
    }
    
    EXPECT_FALSE(avl->isEmpty());
    
    avl->makeEmpty();
    
    EXPECT_TRUE(avl->isEmpty());
    EXPECT_EQ(avl->size(), 0);
    EXPECT_EQ(avl->getHeight(), -1);
    EXPECT_TRUE(avl->isBalanced());
}

TEST_F(AVLTest, DuplicateInsertions) {
    avl->insert(50);
    avl->insert(50);
    avl->insert(50);
    
    EXPECT_EQ(avl->size(), 1);
    EXPECT_TRUE(avl->contains(50));
    EXPECT_TRUE(avl->isBalanced());
}

// Template Tests with Different Types
TEST(AVLTemplateTest, StringAVL) {
    AVLTree<std::string> stringAVL;
    
    std::vector<std::string> words = {"hello", "world", "apple", "banana", "zebra"};
    
    for (const auto& word : words) {
        stringAVL.insert(word);
        EXPECT_TRUE(stringAVL.isBalanced());
    }
    
    EXPECT_EQ(stringAVL.size(), words.size());
    EXPECT_TRUE(stringAVL.contains("hello"));
    EXPECT_FALSE(stringAVL.contains("missing"));
    
    auto inorder = stringAVL.inorderTraversal();
    std::vector<std::string> expected = {"apple", "banana", "hello", "world", "zebra"};
    EXPECT_EQ(inorder, expected);
}

TEST(AVLTemplateTest, DoubleAVL) {
    AVLTree<double> doubleAVL;
    
    std::vector<double> values = {3.14, 2.71, 1.41, 0.57, 4.47};
    
    for (double val : values) {
        doubleAVL.insert(val);
        EXPECT_TRUE(doubleAVL.isBalanced());
    }
    
    EXPECT_EQ(doubleAVL.size(), values.size());
    EXPECT_DOUBLE_EQ(doubleAVL.findMin(), 0.57);
    EXPECT_DOUBLE_EQ(doubleAVL.findMax(), 4.47);
}

// Performance Comparison Test
TEST(AVLPerformanceTest, HeightComparison) {
    const int NUM_ELEMENTS = 127; // 2^7 - 1, perfect for comparison
    
    // Create AVL tree with sequential insertion
    AVLTree<int> avl;
    for (int i = 1; i <= NUM_ELEMENTS; i++) {
        avl.insert(i);
    }
    
    // AVL tree should have much better height than unbalanced BST
    int avlHeight = avl.getHeight();
    int expectedWorstHeight = NUM_ELEMENTS - 1; // Height of completely unbalanced BST
    int expectedBestHeight = static_cast<int>(std::log2(NUM_ELEMENTS)); // Height of perfect binary tree
    
    EXPECT_LE(avlHeight, expectedBestHeight + 2); // AVL height should be close to optimal
    EXPECT_LT(avlHeight, expectedWorstHeight / 2); // Much better than worst case
    
    std::cout << "AVL height: " << avlHeight 
              << ", Optimal height: " << expectedBestHeight
              << ", Worst height: " << expectedWorstHeight << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}