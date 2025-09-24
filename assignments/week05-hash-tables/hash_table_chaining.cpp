// Hash Table with Separate Chaining Implementation
// Week 5: Hash Tables Assignment

#include <iostream>
#include <vector>
#include <list>
#include <functional>

/**
 * Hash Table implementation using separate chaining for collision resolution
 * Time Complexity: Average O(1) for insert/search/delete, Worst O(n)
 * Space Complexity: O(n)
 */

template<typename K, typename V>
class HashTableChaining {
protected:
    struct KeyValuePair {
        K key;
        V value;
        KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
    };
    
    std::vector<std::list<KeyValuePair>> table;
    size_t tableSize;
    size_t numElements;
    double maxLoadFactor;
    
    // Hash function
    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % tableSize;
    }
    
    // Resize and rehash when load factor exceeds threshold
    void rehash() {
        if (loadFactor() <= maxLoadFactor) return;
        
        auto oldTable = std::move(table);
        tableSize *= 2;
        table = std::vector<std::list<KeyValuePair>>(tableSize);
        numElements = 0;
        
        for (const auto& bucket : oldTable) {
            for (const auto& pair : bucket) {
                insert(pair.key, pair.value);
            }
        }
    }

public:
    // Constructor
    explicit HashTableChaining(size_t initialSize = 16, double maxLoad = 0.75) 
        : tableSize(initialSize), numElements(0), maxLoadFactor(maxLoad) {
        table.resize(tableSize);
    }
    
    // Insert key-value pair
    void insert(const K& key, const V& value) {
        size_t index = hash(key);
        
        // Check if key already exists
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                pair.value = value; // Update existing
                return;
            }
        }
        
        // Add new pair
        table[index].emplace_back(key, value);
        numElements++;
        rehash();
    }
    
    // Search for key
    bool find(const K& key, V& value) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.key == key) {
                value = pair.value;
                return true;
            }
        }
        return false;
    }
    
    // Remove key
    bool remove(const K& key) {
        size_t index = hash(key);
        auto& bucket = table[index];
        
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                numElements--;
                return true;
            }
        }
        return false;
    }
    
    // Get current load factor
    double loadFactor() const {
        return static_cast<double>(numElements) / tableSize;
    }
    
    size_t size() const { return numElements; }
    bool empty() const { return numElements == 0; }
};

// Demonstration function
void demonstrateHashTableChaining() {
    std::cout << "=== Hash Table with Chaining Demo ===" << std::endl;
    
    HashTableChaining<std::string, int> hashtable;
    
    // Insert some key-value pairs
    hashtable.insert("apple", 100);
    hashtable.insert("banana", 200);
    hashtable.insert("cherry", 300);
    
    int value;
    if (hashtable.find("apple", value)) {
        std::cout << "Found apple: " << value << std::endl;
    }
    
    std::cout << "Load factor: " << hashtable.loadFactor() << std::endl;
}

// Additional Methods and Functionality

template<typename K, typename V>
class HashTableChainingAdvanced : public HashTableChaining<K, V> {
private:
    size_t collisions;
    
public:
    explicit HashTableChainingAdvanced(size_t initialSize = 16, double maxLoad = 0.75) 
        : HashTableChaining<K, V>(initialSize, maxLoad), collisions(0) {}
    
    // Track collisions for performance analysis
    void insert(const K& key, const V& value) {
        size_t index = this->hash(key);
        if (!this->table[index].empty()) {
            collisions++;
        }
        HashTableChaining<K, V>::insert(key, value);
    }
    
    // Get all keys
    std::vector<K> getAllKeys() const {
        std::vector<K> keys;
        for (const auto& bucket : this->table) {
            for (const auto& pair : bucket) {
                keys.push_back(pair.key);
            }
        }
        return keys;
    }
    
    // Performance statistics
    void printStatistics() const {
        std::cout << "Hash Table Statistics:" << std::endl;
        std::cout << "Size: " << this->size() << std::endl;
        std::cout << "Table Size: " << this->tableSize << std::endl;
        std::cout << "Load Factor: " << this->loadFactor() << std::endl;
        std::cout << "Collisions: " << collisions << std::endl;
        
        // Calculate average chain length
        size_t totalChainLength = 0;
        size_t nonEmptyBuckets = 0;
        for (const auto& bucket : this->table) {
            if (!bucket.empty()) {
                totalChainLength += bucket.size();
                nonEmptyBuckets++;
            }
        }
        if (nonEmptyBuckets > 0) {
            std::cout << "Average Chain Length: " 
                      << static_cast<double>(totalChainLength) / nonEmptyBuckets << std::endl;
        }
    }
};

int main() {
    demonstrateHashTableChaining();
    
    std::cout << "\n=== Advanced Hash Table Demo ===" << std::endl;
    HashTableChainingAdvanced<std::string, int> advancedTable(8);
    
    // Test with potential collisions
    std::vector<std::string> testKeys = {
        "key1", "key2", "key3", "key4", "key5",
        "collision1", "collision2", "test", "demo", "hash"
    };
    
    for (size_t i = 0; i < testKeys.size(); ++i) {
        advancedTable.insert(testKeys[i], static_cast<int>(i * 10));
    }
    
    advancedTable.printStatistics();
    
    return 0;
}

// TODO: Students implement:
// - Template specializations for different key types
// - Iterator support  
// - Copy constructor and assignment operator
// - Additional hash functions (e.g., custom hash for user-defined types)
// - Resize strategies (linear vs exponential growth)
// - Open addressing collision resolution
// - Robin Hood hashing optimization