#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>

/**
 * Stack Implementation using Dynamic Array
 * LIFO (Last In, First Out) data structure
 */

template<typename T>
class Stack {
private:
    T* stackArray;
    int capacity;
    int topIndex;
    static const int DEFAULT_CAPACITY = 10;
    
    void resize() {
        capacity *= 2;
        T* newArray = new T[capacity];
        for (int i = 0; i <= topIndex; i++) {
            newArray[i] = stackArray[i];
        }
        delete[] stackArray;
        stackArray = newArray;
    }

public:
    /**
     * Constructor - Initialize empty stack
     * Time Complexity: O(1)
     * Space Complexity: O(capacity)
     */
    Stack(int initialCapacity = DEFAULT_CAPACITY) 
        : capacity(initialCapacity), topIndex(-1) {
        if (initialCapacity <= 0) {
            throw std::invalid_argument("Capacity must be positive");
        }
        stackArray = new T[capacity];
    }

    /**
     * Copy Constructor
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    Stack(const Stack& other) 
        : capacity(other.capacity), topIndex(other.topIndex) {
        stackArray = new T[capacity];
        for (int i = 0; i <= topIndex; i++) {
            stackArray[i] = other.stackArray[i];
        }
    }

    /**
     * Assignment Operator
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] stackArray;
            capacity = other.capacity;
            topIndex = other.topIndex;
            stackArray = new T[capacity];
            for (int i = 0; i <= topIndex; i++) {
                stackArray[i] = other.stackArray[i];
            }
        }
        return *this;
    }

    /**
     * Destructor - Clean up memory
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    ~Stack() {
        delete[] stackArray;
    }

    /**
     * Push element onto stack
     * Time Complexity: O(1) amortized, O(n) worst case for resize
     * Space Complexity: O(1)
     */
    void push(const T& element) {
        if (topIndex == capacity - 1) {
            resize();
        }
        stackArray[++topIndex] = element;
    }

    /**
     * Pop element from stack
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return stackArray[topIndex--];
    }

    /**
     * Peek at top element without removing
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return stackArray[topIndex];
    }

    /**
     * Check if stack is empty
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool isEmpty() const {
        return topIndex == -1;
    }

    /**
     * Get number of elements in stack
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int size() const {
        return topIndex + 1;
    }

    /**
     * Get current capacity of stack
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int getCapacity() const {
        return capacity;
    }

    /**
     * Clear all elements from stack
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void clear() {
        topIndex = -1;
    }

    /**
     * Display stack contents (for debugging)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void display() const {
        if (isEmpty()) {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        
        std::cout << "Stack (top to bottom): ";
        for (int i = topIndex; i >= 0; i--) {
            std::cout << stackArray[i];
            if (i > 0) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
};

// Stack Applications

/**
 * Check if parentheses are balanced in an expression
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
bool isBalanced(const std::string& expression) {
    Stack<char> stack;
    
    for (char ch : expression) {
        // Push opening brackets
        if (ch == '(' || ch == '[' || ch == '{') {
            stack.push(ch);
        }
        // Check closing brackets
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack.isEmpty()) {
                return false;
            }
            
            char top = stack.pop();
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                return false;
            }
        }
    }
    
    return stack.isEmpty();
}

/**
 * Get precedence of operators
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

/**
 * Check if character is an operator
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
}

/**
 * Convert infix expression to postfix
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
std::string infixToPostfix(const std::string& infix) {
    Stack<char> operatorStack;
    std::string postfix;
    
    for (char ch : infix) {
        // Skip whitespace
        if (std::isspace(ch)) {
            continue;
        }
        
        // If operand, add to output
        if (std::isalnum(ch)) {
            postfix += ch;
        }
        // If opening parenthesis, push to stack
        else if (ch == '(') {
            operatorStack.push(ch);
        }
        // If closing parenthesis, pop until opening parenthesis
        else if (ch == ')') {
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                postfix += operatorStack.pop();
            }
            if (!operatorStack.isEmpty()) {
                operatorStack.pop(); // Remove opening parenthesis
            }
        }
        // If operator
        else if (isOperator(ch)) {
            while (!operatorStack.isEmpty() && 
                   operatorStack.peek() != '(' &&
                   getPrecedence(operatorStack.peek()) >= getPrecedence(ch)) {
                postfix += operatorStack.pop();
            }
            operatorStack.push(ch);
        }
    }
    
    // Pop remaining operators
    while (!operatorStack.isEmpty()) {
        postfix += operatorStack.pop();
    }
    
    return postfix;
}

/**
 * Evaluate postfix expression
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
int evaluatePostfix(const std::string& postfix) {
    Stack<int> operandStack;
    
    for (char ch : postfix) {
        // Skip whitespace
        if (std::isspace(ch)) {
            continue;
        }
        
        // If operand (digit), push to stack
        if (std::isdigit(ch)) {
            operandStack.push(ch - '0');
        }
        // If operator, pop two operands and evaluate
        else if (isOperator(ch)) {
            if (operandStack.size() < 2) {
                throw std::invalid_argument("Invalid postfix expression");
            }
            
            int operand2 = operandStack.pop();
            int operand1 = operandStack.pop();
            int result;
            
            switch (ch) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    result = operand1 / operand2;
                    break;
                case '%':
                    if (operand2 == 0) {
                        throw std::runtime_error("Modulo by zero");
                    }
                    result = operand1 % operand2;
                    break;
                case '^':
                    result = 1;
                    for (int i = 0; i < operand2; i++) {
                        result *= operand1;
                    }
                    break;
                default:
                    throw std::invalid_argument("Unknown operator");
            }
            
            operandStack.push(result);
        }
    }
    
    if (operandStack.size() != 1) {
        throw std::invalid_argument("Invalid postfix expression");
    }
    
    return operandStack.pop();
}

/**
 * Check if string is palindrome using stack
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
bool isPalindrome(const std::string& str) {
    Stack<char> stack;
    int n = str.length();
    
    // Push first half to stack
    for (int i = 0; i < n / 2; i++) {
        stack.push(std::tolower(str[i]));
    }
    
    // Compare second half with stack
    int start = (n % 2 == 0) ? n / 2 : n / 2 + 1;
    for (int i = start; i < n; i++) {
        if (stack.isEmpty() || stack.pop() != std::tolower(str[i])) {
            return false;
        }
    }
    
    return stack.isEmpty();
}

// Example usage and testing functions
void demonstrateStack() {
    std::cout << "=== Stack Demonstration ===" << std::endl;
    
    Stack<int> stack;
    
    // Test push operations
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    std::cout << "After pushing 10, 20, 30:" << std::endl;
    stack.display();
    
    // Test peek
    std::cout << "Peek: " << stack.peek() << std::endl;
    std::cout << "Size: " << stack.size() << std::endl;
    
    // Test pop operations
    std::cout << "Popped: " << stack.pop() << std::endl;
    std::cout << "Popped: " << stack.pop() << std::endl;
    
    std::cout << "After popping twice:" << std::endl;
    stack.display();
    
    // Test applications
    std::cout << "\n=== Stack Applications ===" << std::endl;
    
    std::string expr1 = "{[()]}";
    std::string expr2 = "{[(])}";
    std::cout << expr1 << " is balanced: " << std::boolalpha << isBalanced(expr1) << std::endl;
    std::cout << expr2 << " is balanced: " << std::boolalpha << isBalanced(expr2) << std::endl;
    
    std::string infix = "a+b*c-d";
    std::string postfix = infixToPostfix(infix);
    std::cout << "Infix: " << infix << " -> Postfix: " << postfix << std::endl;
    
    std::string postfixExpr = "23+4*";
    int result = evaluatePostfix(postfixExpr);
    std::cout << "Postfix " << postfixExpr << " evaluates to: " << result << std::endl;
}