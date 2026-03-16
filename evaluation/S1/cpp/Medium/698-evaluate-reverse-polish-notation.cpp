// Source: https://leetcode.com/problems/evaluate-reverse-polish-notation/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.
//
// Evaluate the expression. Return an integer that represents the value of the expression.
//
// Note that:
//
//
// 	The valid operators are '+', '-', '*', and '/'.
// 	Each operand may be an integer or another expression.
// 	The division between two integers always truncates toward zero.
// 	There will not be any division by zero.
// 	The input represents a valid arithmetic expression in a reverse polish notation.
// 	The answer and all the intermediate calculations can be represented in a 32-bit integer.
//
// Example:
// Input: tokens = ["2","1","+","3","*"]
// Output: 9
// Explanation: ((2 + 1) * 3) = 9
//
// Constraints:
// 1 <= tokens.length <= 104
// 	tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        vector<int> stack;
        for (const string &token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = stack.back(); stack.pop_back();
                int a = stack.back(); stack.pop_back();
                int res = 0;
                if (token == "+") {
                    res = a + b;
                } else if (token == "-") {
                    res = a - b;
                } else if (token == "*") {
                    res = a * b;
                } else if (token == "/") {
                    res = a / b;
                }
                stack.push_back(res);
            } else {
                stack.push_back(stoi(token));
            }
        }
        return stack.back();            
    }
};
