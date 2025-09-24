#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include "binary_search_tree.cpp"
#include "avl_tree.cpp"
#include "tree_applications.cpp"

int main() {
    std::cout << "======================================" << std::endl;
    std::cout << " DSA Week 4: Binary Trees Demonstration" << std::endl;
    std::cout << "======================================" << std::endl;
    
    // Demonstrate Binary Search Tree
    std::cout << "\n1. Binary Search Tree Implementation:" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    demonstrateBST();
    
    std::cout << "\n\n";
    
    // Demonstrate AVL Tree
    std::cout << "2. AVL Tree Implementation:" << std::endl;
    std::cout << "---------------------------" << std::endl;
    demonstrateAVL();
    
    std::cout << "\n\n";
    
    // Demonstrate Tree Applications
    std::cout << "3. Advanced Tree Applications:" << std::endl;
    std::cout << "------------------------------" << std::endl;
    demonstrateTreeApplications();
    
    std::cout << "\n\n";
    
    // Performance Comparison
    std::cout << "4. Performance Comparison:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    const int NUM_ELEMENTS = 100;
    
    // BST with sequential insertion (worst case)
    BinarySearchTree<int> bst;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= NUM_ELEMENTS; i++) {
        bst.insert(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto bstTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    // AVL with sequential insertion (balanced)
    AVLTree<int> avl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= NUM_ELEMENTS; i++) {
        avl.insert(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto avlTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "Sequential insertion of " << NUM_ELEMENTS << " elements:" << std::endl;
    std::cout << "BST height: " << bst.getHeight() << " (worst case: " << NUM_ELEMENTS - 1 << ")" << std::endl;
    std::cout << "AVL height: " << avl.getHeight() << " (optimal: ~" << static_cast<int>(log2(NUM_ELEMENTS)) << ")" << std::endl;
    std::cout << "BST insertion time: " << bstTime << " microseconds" << std::endl;
    std::cout << "AVL insertion time: " << avlTime << " microseconds" << std::endl;
    
    // Search performance comparison
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= NUM_ELEMENTS; i++) {
        bst.contains(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto bstSearchTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= NUM_ELEMENTS; i++) {
        avl.contains(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto avlSearchTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "Search time for all elements:" << std::endl;
    std::cout << "BST search time: " << bstSearchTime << " microseconds" << std::endl;
    std::cout << "AVL search time: " << avlSearchTime << " microseconds" << std::endl;
    
    if (avlSearchTime > 0) {
        std::cout << "BST is " << (bstSearchTime / (double)avlSearchTime) << "x slower than AVL" << std::endl;
    }
    
    std::cout << "\n======================================" << std::endl;
    std::cout << " Week 4 Demonstration Complete!" << std::endl;
    std::cout << "======================================" << std::endl;
    
    return 0;
}