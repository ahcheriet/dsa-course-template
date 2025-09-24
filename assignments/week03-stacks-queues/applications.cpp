#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <deque>

/**
 * Advanced Stack and Queue Applications
 * This file contains more complex applications and algorithms
 */

// Forward declarations for stack and queue classes
template<typename T> class Stack;
template<typename T> class Queue;

/**
 * Sliding Window Maximum using Deque
 * Time Complexity: O(n)
 * Space Complexity: O(k)
 */
std::vector<int> slidingWindowMaximum(const std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::deque<int> dq; // Store indices
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove elements outside current window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove smaller elements from rear
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // Add maximum to result (after first window is complete)
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

/**
 * Next Greater Element using Stack
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
std::vector<int> nextGreaterElement(const std::vector<int>& nums) {
    std::vector<int> result(nums.size(), -1);
    std::stack<int> stack; // Store indices
    
    for (int i = 0; i < nums.size(); i++) {
        while (!stack.empty() && nums[stack.top()] < nums[i]) {
            result[stack.top()] = nums[i];
            stack.pop();
        }
        stack.push(i);
    }
    
    return result;
}

/**
 * Largest Rectangle in Histogram using Stack
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
int largestRectangleArea(const std::vector<int>& heights) {
    std::stack<int> stack;
    int maxArea = 0;
    int index = 0;
    
    while (index < heights.size()) {
        if (stack.empty() || heights[index] >= heights[stack.top()]) {
            stack.push(index++);
        } else {
            int top = stack.top();
            stack.pop();
            
            int area = heights[top] * (stack.empty() ? index : index - stack.top() - 1);
            maxArea = std::max(maxArea, area);
        }
    }
    
    while (!stack.empty()) {
        int top = stack.top();
        stack.pop();
        
        int area = heights[top] * (stack.empty() ? index : index - stack.top() - 1);
        maxArea = std::max(maxArea, area);
    }
    
    return maxArea;
}

/**
 * Implement Stack using Two Queues
 * Push: O(n), Pop: O(1)
 */
class StackUsingQueues {
private:
    std::queue<int> q1, q2;

public:
    void push(int x) {
        q2.push(x);
        
        // Move all elements from q1 to q2
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        
        // Swap q1 and q2
        std::swap(q1, q2);
    }
    
    int pop() {
        if (q1.empty()) {
            throw std::underflow_error("Stack is empty");
        }
        
        int top = q1.front();
        q1.pop();
        return top;
    }
    
    int top() {
        if (q1.empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

/**
 * Implement Queue using Two Stacks
 * Enqueue: O(1), Dequeue: O(n) worst case, O(1) amortized
 */
class QueueUsingStacks {
private:
    std::stack<int> stack1, stack2;

public:
    void enqueue(int x) {
        stack1.push(x);
    }
    
    int dequeue() {
        if (stack2.empty()) {
            // Move all elements from stack1 to stack2
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        
        if (stack2.empty()) {
            throw std::underflow_error("Queue is empty");
        }
        
        int front = stack2.top();
        stack2.pop();
        return front;
    }
    
    int front() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        
        if (stack2.empty()) {
            throw std::underflow_error("Queue is empty");
        }
        
        return stack2.top();
    }
    
    bool empty() {
        return stack1.empty() && stack2.empty();
    }
};

/**
 * Min Stack - Stack with O(1) min operation
 */
class MinStack {
private:
    std::stack<int> dataStack;
    std::stack<int> minStack;

public:
    void push(int val) {
        dataStack.push(val);
        
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        if (dataStack.empty()) {
            throw std::underflow_error("Stack is empty");
        }
        
        if (dataStack.top() == minStack.top()) {
            minStack.pop();
        }
        dataStack.pop();
    }
    
    int top() {
        if (dataStack.empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return dataStack.top();
    }
    
    int getMin() {
        if (minStack.empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return minStack.top();
    }
};

/**
 * Circular Queue implementation
 */
class CircularQueue {
private:
    std::vector<int> data;
    int head;
    int tail;
    int size;

public:
    CircularQueue(int k) : data(k), head(-1), tail(-1), size(0) {}
    
    bool enqueue(int value) {
        if (isFull()) {
            return false;
        }
        
        if (isEmpty()) {
            head = 0;
        }
        
        tail = (tail + 1) % data.size();
        data[tail] = value;
        size++;
        return true;
    }
    
    bool dequeue() {
        if (isEmpty()) {
            return false;
        }
        
        if (head == tail) {
            head = -1;
            tail = -1;
        } else {
            head = (head + 1) % data.size();
        }
        
        size--;
        return true;
    }
    
    int front() {
        if (isEmpty()) {
            return -1;
        }
        return data[head];
    }
    
    int rear() {
        if (isEmpty()) {
            return -1;
        }
        return data[tail];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == data.size();
    }
};

/**
 * Expression evaluation with support for nested parentheses
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
int evaluateExpression(const std::string& expression) {
    std::stack<int> operands;
    std::stack<char> operators;
    
    auto precedence = [](char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    };
    
    auto calculate = [](int a, int b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            default: return 0;
        }
    };
    
    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        
        if (c == ' ') continue;
        
        if (std::isdigit(c)) {
            int num = 0;
            while (i < expression.length() && std::isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--; // Adjust for the extra increment
            operands.push(num);
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                int b = operands.top(); operands.pop();
                int a = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                operands.push(calculate(a, b, op));
            }
            operators.pop(); // Remove '('
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operators.empty() && operators.top() != '(' &&
                   precedence(operators.top()) >= precedence(c)) {
                int b = operands.top(); operands.pop();
                int a = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                operands.push(calculate(a, b, op));
            }
            operators.push(c);
        }
    }
    
    while (!operators.empty()) {
        int b = operands.top(); operands.pop();
        int a = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        operands.push(calculate(a, b, op));
    }
    
    return operands.top();
}

/**
 * Check if sequence can be obtained by push/pop operations
 */
bool validateStackSequence(std::vector<int>& pushed, std::vector<int>& popped) {
    std::stack<int> stack;
    int popIndex = 0;
    
    for (int num : pushed) {
        stack.push(num);
        
        while (!stack.empty() && stack.top() == popped[popIndex]) {
            stack.pop();
            popIndex++;
        }
    }
    
    return popIndex == popped.size();
}

// Demonstration function
void demonstrateAdvancedApplications() {
    std::cout << "=== Advanced Stack/Queue Applications ===" << std::endl;
    
    // Sliding Window Maximum
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    std::vector<int> maxInWindow = slidingWindowMaximum(nums, 3);
    std::cout << "Sliding window maximum (k=3): ";
    for (int max : maxInWindow) {
        std::cout << max << " ";
    }
    std::cout << std::endl;
    
    // Next Greater Element
    std::vector<int> elements = {4, 5, 2, 25};
    std::vector<int> nextGreater = nextGreaterElement(elements);
    std::cout << "Next greater elements: ";
    for (int ng : nextGreater) {
        std::cout << ng << " ";
    }
    std::cout << std::endl;
    
    // Largest Rectangle in Histogram
    std::vector<int> heights = {2, 1, 5, 6, 2, 3};
    int maxArea = largestRectangleArea(heights);
    std::cout << "Largest rectangle area: " << maxArea << std::endl;
    
    // Min Stack
    MinStack minStack;
    minStack.push(3);
    minStack.push(5);
    minStack.push(2);
    minStack.push(1);
    std::cout << "Min stack minimum: " << minStack.getMin() << std::endl;
    
    // Expression Evaluation
    std::string expr = "3 + 5 * 2 - 1";
    int result = evaluateExpression(expr);
    std::cout << "Expression '" << expr << "' = " << result << std::endl;
}