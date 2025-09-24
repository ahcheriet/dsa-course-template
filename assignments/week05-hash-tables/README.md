# Week 5: Hash Tables

## Overview
This assignment focuses on implementing and understanding hash table data structures, different collision resolution strategies, and hash table applications.

## Learning Objectives
- Understand hash function design and collision handling
- Implement hash tables with different collision resolution strategies
- Analyze time complexity of hash table operations
- Apply hash tables to solve real-world problems

## Files to Implement
1. `hash_table_chaining.cpp` - Hash table with separate chaining
2. `hash_table_probing.cpp` - Hash table with linear/quadratic probing
3. `hash_applications.cpp` - Real-world applications of hash tables

## Key Concepts
- Hash functions and load factor
- Separate chaining vs. open addressing
- Linear probing, quadratic probing, double hashing
- Rehashing and dynamic resizing
- Hash table applications (caching, frequency counting, etc.)

## Requirements
- Template-based implementation for generic types
- Proper memory management
- Comprehensive error handling
- Time complexity analysis comments
- All operations should handle edge cases

## Testing
Run tests with: `make test_week05_hash_tables`

## Grading Criteria
- Correctness of hash table implementations (40%)
- Efficient collision resolution (30%)
- Code quality and documentation (20%)
- Test coverage and edge cases (10%)