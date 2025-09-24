# CMakeLists.txt for DSA Course Template

cmake_minimum_required(VERSION 3.16)
project(DSA_Course)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Function to create test executables
function(create_assignment_test week_name assignment_name)
    set(TEST_NAME test_${week_name}_${assignment_name})
    set(SOURCE_FILE assignments/${week_name}/${assignment_name}.cpp)
    set(TEST_FILE tests/${week_name}/test_${assignment_name}.cpp)
    
    if(EXISTS ${CMAKE_SOURCE_DIR}/${SOURCE_FILE} AND EXISTS ${CMAKE_SOURCE_DIR}/${TEST_FILE})
        add_executable(${TEST_NAME} ${SOURCE_FILE} ${TEST_FILE})
        target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES} pthread)
        
        # Add to test suite
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endif()
endfunction()

# Enable testing
enable_testing()

# Create test executables for Week 1
create_assignment_test(week01 array_operations)
create_assignment_test(week01 search_algorithms)
create_assignment_test(week01 array_manipulation)

# Create test executables for Week 2
create_assignment_test(week02 linked_list)

# Create test executables for Week 3
create_assignment_test(week03 stack)
create_assignment_test(week03 queue)

# Week 4 - Trees (special handling for multiple files in one test)
if(EXISTS ${CMAKE_SOURCE_DIR}/tests/week04/test_binary_search_tree.cpp)
    add_executable(test_week04_binary_search_tree 
        tests/week04/test_binary_search_tree.cpp)
    target_link_libraries(test_week04_binary_search_tree ${GTEST_LIBRARIES} pthread)
    add_test(NAME test_week04_binary_search_tree COMMAND test_week04_binary_search_tree)
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/tests/week04/test_avl_tree.cpp)
    add_executable(test_week04_avl_tree 
        tests/week04/test_avl_tree.cpp)
    target_link_libraries(test_week04_avl_tree ${GTEST_LIBRARIES} pthread)
    add_test(NAME test_week04_avl_tree COMMAND test_week04_avl_tree)
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/tests/week04/test_tree_applications.cpp)
    add_executable(test_week04_tree_applications 
        tests/week04/test_tree_applications.cpp)
    target_link_libraries(test_week04_tree_applications ${GTEST_LIBRARIES} pthread)
    add_test(NAME test_week04_tree_applications COMMAND test_week04_tree_applications)
endif()

# Week 5 - Hash Tables
if(EXISTS ${CMAKE_SOURCE_DIR}/tests/week05/test_hash_table.cpp)
    add_executable(test_week05_hash_table 
        tests/week05/test_hash_table.cpp)
    target_link_libraries(test_week05_hash_table ${GTEST_LIBRARIES} pthread)
    add_test(NAME test_week05_hash_table COMMAND test_week05_hash_table)
endif()

# Week 6 - Sorting Algorithms
if(EXISTS ${CMAKE_SOURCE_DIR}/tests/week06/test_basic_sorts.cpp)
    add_executable(test_week06_basic_sorts 
        tests/week06/test_basic_sorts.cpp)
    target_link_libraries(test_week06_basic_sorts ${GTEST_LIBRARIES} pthread)
    add_test(NAME test_week06_basic_sorts COMMAND test_week06_basic_sorts)
endif()

# Week 7 - Graph Algorithms
if(EXISTS ${CMAKE_SOURCE_DIR}/tests/week07/test_graph.cpp)
    add_executable(test_week07_graph 
        tests/week07/test_graph.cpp)
    target_link_libraries(test_week07_graph ${GTEST_LIBRARIES} pthread)
    add_test(NAME test_week07_graph COMMAND test_week07_graph)
endif()

# Custom target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    COMMENT "Running all tests"
)

# Custom target for code formatting
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(format
        COMMAND find assignments -name "*.cpp" -o -name "*.h" -o -name "*.hpp" | xargs clang-format -i
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Formatting code with clang-format"
    )
endif()

# Add memory check target using Valgrind (if available)
find_program(VALGRIND "valgrind")
if(VALGRIND)
    add_custom_target(memcheck
        COMMAND ${CMAKE_CTEST_COMMAND} --verbose -T memcheck
        COMMENT "Running memory checks with Valgrind"
    )
endif()

# Installation rules (optional, for deploying the template)
install(DIRECTORY assignments/ DESTINATION share/dsa-template/assignments)
install(DIRECTORY tests/ DESTINATION share/dsa-template/tests)
install(FILES README.md CONTRIBUTING.md INSTRUCTOR_GUIDE.md DESTINATION share/dsa-template/)