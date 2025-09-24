#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

// Mock Stack class for testing (replace with actual implementation)
template<typename T>
class Stack {
public:
    Stack() {}
    ~Stack() {}
    
    void push(const T& element);
    T pop();
    T peek() const;
    bool isEmpty() const;
    int size() const;
    void clear();
    void display() const;
};

// Forward declare application functions
bool isBalanced(const std::string& expression);
std::string infixToPostfix(const std::string& infix);
int evaluatePostfix(const std::string& postfix);
bool isPalindrome(const std::string& str);
std::vector<int> nextGreaterElement(const std::vector<int>& nums);

class StackTest : public ::testing::Test {
protected:
    Stack<int> stack;
    
    void SetUp() override {
        // Start with empty stack for each test
    }
    
    void TearDown() override {
        // Cleanup handled by destructor
    }
};

// Basic Stack Operations Tests
TEST_F(StackTest, PushSingleElement) {
    stack.push(10);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.peek(), 10);
}

TEST_F(StackTest, PushMultipleElements) {
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.peek(), 30);
}

TEST_F(StackTest, PopSingleElement) {
    stack.push(42);
    int popped = stack.pop();
    
    EXPECT_EQ(popped, 42);
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.isEmpty());
}

TEST_F(StackTest, PopMultipleElements) {
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    EXPECT_EQ(stack.pop(), 30);
    EXPECT_EQ(stack.pop(), 20);
    EXPECT_EQ(stack.pop(), 10);
    EXPECT_TRUE(stack.isEmpty());
}

TEST_F(StackTest, PopFromEmptyStack) {
    EXPECT_THROW(stack.pop(), std::underflow_error);
}

TEST_F(StackTest, PeekAtEmptyStack) {
    EXPECT_THROW(stack.peek(), std::underflow_error);
}

TEST_F(StackTest, PeekDoesNotRemoveElement) {
    stack.push(100);
    
    EXPECT_EQ(stack.peek(), 100);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.peek(), 100); // Should still be there
}

TEST_F(StackTest, IsEmptyOnNewStack) {
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
}

TEST_F(StackTest, IsEmptyAfterOperations) {
    stack.push(1);
    EXPECT_FALSE(stack.isEmpty());
    
    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
}

TEST_F(StackTest, ClearStack) {
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
}

TEST_F(StackTest, LIFOBehavior) {
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    
    EXPECT_EQ(stack.pop(), 4);
    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.pop(), 2);
    EXPECT_EQ(stack.pop(), 1);
}

// Dynamic Resizing Tests
TEST_F(StackTest, DynamicResizing) {
    // Push many elements to test resizing
    for (int i = 0; i < 100; i++) {
        stack.push(i);
    }
    
    EXPECT_EQ(stack.size(), 100);
    EXPECT_EQ(stack.peek(), 99);
    
    // Pop all elements
    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(stack.pop(), i);
    }
    
    EXPECT_TRUE(stack.isEmpty());
}

// String Stack Tests
class StringStackTest : public ::testing::Test {
protected:
    Stack<std::string> stringStack;
};

TEST_F(StringStackTest, StringOperations) {
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.push("!");
    
    EXPECT_EQ(stringStack.pop(), "!");
    EXPECT_EQ(stringStack.pop(), "World");
    EXPECT_EQ(stringStack.pop(), "Hello");
}

// Stack Applications Tests
class StackApplicationsTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(StackApplicationsTest, BalancedParenthesesValid) {
    EXPECT_TRUE(isBalanced("()"));
    EXPECT_TRUE(isBalanced("()[]{}"));
    EXPECT_TRUE(isBalanced("{[()]}"));
    EXPECT_TRUE(isBalanced("((()))"));
    EXPECT_TRUE(isBalanced(""));
}

TEST_F(StackApplicationsTest, BalancedParenthesesInvalid) {
    EXPECT_FALSE(isBalanced("("));
    EXPECT_FALSE(isBalanced(")"));
    EXPECT_FALSE(isBalanced("([)]"));
    EXPECT_FALSE(isBalanced("((())"));
    EXPECT_FALSE(isBalanced("()())"));
}

TEST_F(StackApplicationsTest, BalancedParenthesesWithOtherChars) {
    EXPECT_TRUE(isBalanced("a(b)c[d]e{f}g"));
    EXPECT_FALSE(isBalanced("a(b]c"));
    EXPECT_TRUE(isBalanced("if (condition) { return array[index]; }"));
}

TEST_F(StackApplicationsTest, InfixToPostfixBasic) {
    EXPECT_EQ(infixToPostfix("a+b"), "ab+");
    EXPECT_EQ(infixToPostfix("a+b*c"), "abc*+");
    EXPECT_EQ(infixToPostfix("a*b+c"), "ab*c+");
    EXPECT_EQ(infixToPostfix("a+b*c-d"), "abc*+d-");
}

TEST_F(StackApplicationsTest, InfixToPostfixWithParentheses) {
    EXPECT_EQ(infixToPostfix("(a+b)*c"), "ab+c*");
    EXPECT_EQ(infixToPostfix("a*(b+c)"), "abc+*");
    EXPECT_EQ(infixToPostfix("(a+b)*(c-d)"), "ab+cd-*");
}

TEST_F(StackApplicationsTest, InfixToPostfixComplexExpressions) {
    EXPECT_EQ(infixToPostfix("a+b*c-d/e"), "abc*+de/-");
    EXPECT_EQ(infixToPostfix("a^b^c"), "abc^^"); // Right associative
    EXPECT_EQ(infixToPostfix("(a+b)^(c-d)"), "ab+cd-^");
}

TEST_F(StackApplicationsTest, EvaluatePostfixBasic) {
    EXPECT_EQ(evaluatePostfix("23+"), 5);
    EXPECT_EQ(evaluatePostfix("23*"), 6);
    EXPECT_EQ(evaluatePostfix("23-"), -1);
    EXPECT_EQ(evaluatePostfix("84/"), 2);
}

TEST_F(StackApplicationsTest, EvaluatePostfixComplex) {
    EXPECT_EQ(evaluatePostfix("234*+"), 14); // 2 + (3 * 4)
    EXPECT_EQ(evaluatePostfix("23+4*"), 20); // (2 + 3) * 4
    EXPECT_EQ(evaluatePostfix("562/-"), 2); // 5 - (6 / 2)
}

TEST_F(StackApplicationsTest, EvaluatePostfixInvalidExpressions) {
    EXPECT_THROW(evaluatePostfix("2+"), std::invalid_argument);
    EXPECT_THROW(evaluatePostfix("22"), std::invalid_argument);
    EXPECT_THROW(evaluatePostfix("2/0"), std::runtime_error); // Division by zero
}

TEST_F(StackApplicationsTest, PalindromeCheck) {
    EXPECT_TRUE(isPalindrome(""));
    EXPECT_TRUE(isPalindrome("a"));
    EXPECT_TRUE(isPalindrome("aba"));
    EXPECT_TRUE(isPalindrome("racecar"));
    EXPECT_TRUE(isPalindrome("A man a plan a canal Panama")); // Ignore case and spaces
    
    EXPECT_FALSE(isPalindrome("abc"));
    EXPECT_FALSE(isPalindrome("race a car"));
}

TEST_F(StackApplicationsTest, NextGreaterElementBasic) {
    std::vector<int> nums1 = {4, 5, 2, 25};
    std::vector<int> expected1 = {5, 25, 25, -1};
    EXPECT_EQ(nextGreaterElement(nums1), expected1);
    
    std::vector<int> nums2 = {13, 7, 6, 12};
    std::vector<int> expected2 = {-1, 12, 12, -1};
    EXPECT_EQ(nextGreaterElement(nums2), expected2);
}

TEST_F(StackApplicationsTest, NextGreaterElementEdgeCases) {
    std::vector<int> empty = {};
    EXPECT_EQ(nextGreaterElement(empty), std::vector<int>{});
    
    std::vector<int> single = {5};
    std::vector<int> expectedSingle = {-1};
    EXPECT_EQ(nextGreaterElement(single), expectedSingle);
    
    std::vector<int> descending = {5, 4, 3, 2, 1};
    std::vector<int> expectedDescending = {-1, -1, -1, -1, -1};
    EXPECT_EQ(nextGreaterElement(descending), expectedDescending);
    
    std::vector<int> ascending = {1, 2, 3, 4, 5};
    std::vector<int> expectedAscending = {2, 3, 4, 5, -1};
    EXPECT_EQ(nextGreaterElement(ascending), expectedAscending);
}

// Performance Tests
TEST_F(StackTest, PerformanceTest) {
    const int LARGE_SIZE = 10000;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Push operations
    for (int i = 0; i < LARGE_SIZE; i++) {
        stack.push(i);
    }
    
    // Pop operations
    for (int i = 0; i < LARGE_SIZE; i++) {
        stack.pop();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Should complete reasonably quickly (less than 100ms)
    EXPECT_LT(duration.count(), 100);
}

// Memory Safety Tests
TEST_F(StackTest, CopyConstructor) {
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    Stack<int> copied(stack);
    
    EXPECT_EQ(copied.size(), 3);
    EXPECT_EQ(copied.pop(), 3);
    EXPECT_EQ(copied.pop(), 2);
    EXPECT_EQ(copied.pop(), 1);
    
    // Original should be unchanged
    EXPECT_EQ(stack.size(), 3);
}

TEST_F(StackTest, AssignmentOperator) {
    stack.push(10);
    stack.push(20);
    
    Stack<int> assigned;
    assigned = stack;
    
    EXPECT_EQ(assigned.size(), 2);
    EXPECT_EQ(assigned.pop(), 20);
    EXPECT_EQ(assigned.pop(), 10);
    
    // Original should be unchanged
    EXPECT_EQ(stack.size(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}