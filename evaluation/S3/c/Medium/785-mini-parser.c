// Source: https://leetcode.com/problems/mini-parser/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s represents the serialization of a nested list, implement a parser to deserialize it and return the deserialized NestedInteger.
//
// Each element is either an integer or a list whose elements may also be integers or other lists.
//
// Example:
// Input: s = "324"
// Output: 324
// Explanation: You should return a NestedInteger object which contains a single integer 324.
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	s consists of digits, square brackets "[]", negative sign '-', and commas ','.
// 	s is the serialization of valid NestedInteger.
// 	All the values in the input are in the range [-106, 106].
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * *********************************************************************
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * // Initializes an empty nested list and return a reference to the nested integer.
 * struct NestedInteger *NestedIntegerInit();
 *
 * // Return true if this NestedInteger holds a single integer, rather than a nested list.
 * bool NestedIntegerIsInteger(struct NestedInteger *);
 *
 * // Return the single integer that this NestedInteger holds, if it holds a single integer
 * // The result is undefined if this NestedInteger holds a nested list
 * int NestedIntegerGetInteger(struct NestedInteger *);
 *
 * // Set this NestedInteger to hold a single integer.
 * void NestedIntegerSetInteger(struct NestedInteger *ni, int value);
 *
 * // Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
 * void NestedIntegerAdd(struct NestedInteger *ni, struct NestedInteger *elem);
 *
 * // Return the nested list that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * struct NestedInteger **NestedIntegerGetList(struct NestedInteger *);
 *
 * // Return the nested list's size that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * int NestedIntegerGetListSize(struct NestedInteger *);
 * };
 */
struct NestedInteger* deserialize(char* s) {
    // Create a stack to hold NestedInteger pointers
    struct NestedInteger* stack[1000]; // Assuming max depth of nesting is 1000
    int top = -1; // Stack pointer

    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == '[') {
            // Start of a new list, push a new NestedInteger onto the stack
            struct NestedInteger* ni = NestedIntegerInit();
            stack[++top] = ni;
            i++;
        } else if (s[i] == ']') {
            // End of a list, pop from the stack and add to the previous list if exists
            struct NestedInteger* ni = stack[top--];
            if (top >= 0) {
                NestedIntegerAdd(stack[top], ni);
            } else {
                // This is the outermost list, return it
                return ni;
            }
            i++;
        } else if (s[i] == ',') {
            // Separator between elements, just skip it
            i++;
        } else {
            // It's a number, parse it
            int sign = 1;
            if (s[i] == '-') {
                sign = -1;
                i++;
            }
            int num = 0;
            while (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            num *= sign;

            // Create a new NestedInteger for this number and add it to the current list
            struct NestedInteger* ni = NestedIntegerInit();
            NestedIntegerSetInteger(ni, num);
            if (top >= 0) {
                NestedIntegerAdd(stack[top], ni);
            } else {
                // This is a single integer without any list, return it
                return ni;
            }
        }
    }

    // If we finish parsing and there's still something on the stack, return it
    return top >= 0 ? stack[0] : NULL; // Return the outermost list or NULL if input was empty
}
