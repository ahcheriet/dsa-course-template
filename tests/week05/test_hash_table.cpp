/**
 * Test suite for Hash Table with Chaining
 * Week 5: Hash Tables Assignment Tests
 */

#include <gtest/gtest.h>
#include "../../assignments/week05-hash-tables/hash_table_chaining.cpp"

class HashTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        hashTable = new HashTableChaining<std::string, int>();
    }
    
    void TearDown() override {
        delete hashTable;
    }
    
    HashTableChaining<std::string, int>* hashTable;
};

TEST_F(HashTableTest, EmptyTableOperations) {
    EXPECT_EQ(hashTable->size(), 0);
    EXPECT_TRUE(hashTable->empty());
    EXPECT_DOUBLE_EQ(hashTable->loadFactor(), 0.0);
}

TEST_F(HashTableTest, BasicInsertAndFind) {
    hashTable->insert("apple", 100);
    hashTable->insert("banana", 200);
    hashTable->insert("cherry", 300);
    
    EXPECT_EQ(hashTable->size(), 3);
    EXPECT_FALSE(hashTable->empty());
    
    int value;
    EXPECT_TRUE(hashTable->find("apple", value));
    EXPECT_EQ(value, 100);
    
    EXPECT_TRUE(hashTable->find("banana", value));
    EXPECT_EQ(value, 200);
    
    EXPECT_TRUE(hashTable->find("cherry", value));
    EXPECT_EQ(value, 300);
}

TEST_F(HashTableTest, UpdateExistingKey) {
    hashTable->insert("key", 100);
    hashTable->insert("key", 200); // Update
    
    EXPECT_EQ(hashTable->size(), 1);
    
    int value;
    EXPECT_TRUE(hashTable->find("key", value));
    EXPECT_EQ(value, 200);
}

TEST_F(HashTableTest, RemoveOperations) {
    hashTable->insert("remove_me", 100);
    hashTable->insert("keep_me", 200);
    
    EXPECT_TRUE(hashTable->remove("remove_me"));
    EXPECT_FALSE(hashTable->remove("non_existent"));
    
    EXPECT_EQ(hashTable->size(), 1);
    
    int value;
    EXPECT_FALSE(hashTable->find("remove_me", value));
    EXPECT_TRUE(hashTable->find("keep_me", value));
}

TEST_F(HashTableTest, LoadFactorAndRehashing) {
    // Insert many elements to trigger rehashing
    for (int i = 0; i < 20; i++) {
        hashTable->insert("key" + std::to_string(i), i);
    }
    
    EXPECT_EQ(hashTable->size(), 20);
    EXPECT_LT(hashTable->loadFactor(), 0.75); // Should have rehashed
    
    // Verify all elements are still accessible
    for (int i = 0; i < 20; i++) {
        int value;
        EXPECT_TRUE(hashTable->find("key" + std::to_string(i), value));
        EXPECT_EQ(value, i);
    }
}

TEST_F(HashTableTest, CollisionHandling) {
    // Create a small table to force collisions
    HashTableChaining<int, std::string> smallTable(4);
    
    // Insert keys that will likely collide
    smallTable.insert(1, "one");
    smallTable.insert(5, "five");   // 5 % 4 = 1, likely collision with key 1
    smallTable.insert(9, "nine");   // 9 % 4 = 1, likely collision
    
    std::string value;
    EXPECT_TRUE(smallTable.find(1, value));
    EXPECT_EQ(value, "one");
    EXPECT_TRUE(smallTable.find(5, value));
    EXPECT_EQ(value, "five");
    EXPECT_TRUE(smallTable.find(9, value));
    EXPECT_EQ(value, "nine");
}

TEST_F(HashTableTest, NonExistentKeys) {
    hashTable->insert("exists", 100);
    
    int value;
    EXPECT_FALSE(hashTable->find("does_not_exist", value));
    EXPECT_FALSE(hashTable->remove("does_not_exist"));
}

TEST_F(HashTableTest, IntegerKeys) {
    HashTableChaining<int, std::string> intTable;
    
    intTable.insert(42, "answer");
    intTable.insert(123, "number");
    
    std::string value;
    EXPECT_TRUE(intTable.find(42, value));
    EXPECT_EQ(value, "answer");
    EXPECT_TRUE(intTable.find(123, value));
    EXPECT_EQ(value, "number");
}

TEST_F(HashTableTest, LargeDataSet) {
    const int numElements = 1000;
    
    // Insert many elements
    for (int i = 0; i < numElements; i++) {
        hashTable->insert("key" + std::to_string(i), i * 2);
    }
    
    EXPECT_EQ(hashTable->size(), numElements);
    
    // Verify random access
    for (int i = 0; i < numElements; i += 100) {
        int value;
        EXPECT_TRUE(hashTable->find("key" + std::to_string(i), value));
        EXPECT_EQ(value, i * 2);
    }
    
    // Remove some elements
    for (int i = 0; i < numElements; i += 200) {
        EXPECT_TRUE(hashTable->remove("key" + std::to_string(i)));
    }
    
    // Verify removals
    for (int i = 0; i < numElements; i += 200) {
        int value;
        EXPECT_FALSE(hashTable->find("key" + std::to_string(i), value));
    }
}

// Performance and edge case tests
TEST_F(HashTableTest, EmptyStringKeys) {
    hashTable->insert("", 100);
    hashTable->insert("non_empty", 200);
    
    int value;
    EXPECT_TRUE(hashTable->find("", value));
    EXPECT_EQ(value, 100);
}

TEST_F(HashTableTest, DuplicateValues) {
    hashTable->insert("key1", 100);
    hashTable->insert("key2", 100);  // Same value, different key
    
    int value;
    EXPECT_TRUE(hashTable->find("key1", value));
    EXPECT_EQ(value, 100);
    EXPECT_TRUE(hashTable->find("key2", value));
    EXPECT_EQ(value, 100);
}