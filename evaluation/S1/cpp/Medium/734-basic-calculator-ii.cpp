// Source: https://leetcode.com/problems/basic-calculator-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s which represents an expression, evaluate this expression and return its value. 
//
// The integer division should truncate toward zero.
//
// You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].
//
// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().
//
// Example:
// Input: s = "3+2*2"
// Output: 7
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
// 	s represents a valid expression.
// 	All the integers in the expression are non-negative integers in the range [0, 231 - 1].
// 	The answer is guaranteed to fit in a 32-bit integer.
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int calculate(string s) {
        long long result = 0;
        long long currentNumber = 0;
        char operation = '+';
        std::vector<long long> stack;

        for (size_t i = 0; i < s.length(); ++i) {
            char currentChar = s[i];

            if (isdigit(currentChar)) {
                currentNumber = (currentNumber * 10) + (currentChar - '0');
            }

            if ((!isdigit(currentChar) && !isspace(currentChar)) || i == s.length() - 1) {
                if (operation == '+') {
                    stack.push_back(currentNumber);
                } else if (operation == '-') {
                    stack.push_back(-currentNumber);
                } else if (operation == '*') {
                    long long top = stack.back();
                    stack.pop_back();
                    stack.push_back(top * currentNumber);
                } else if (operation == '/') {
                    long long top = stack.back();
                    stack.pop_back();
                    stack.push_back(top / currentNumber);
                }
                operation = currentChar;
                currentNumber = 0;
            }
        }

        for (long long num : stack) {
            result += num;
        }

        return static_cast<int>(result);            
    }
};
