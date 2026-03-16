// Source: https://leetcode.com/problems/build-an-array-with-stack-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array target and an integer n.
//
// You have an empty stack with the two following operations:
//
//
// 	"Push": pushes an integer to the top of the stack.
// 	"Pop": removes the integer on the top of the stack.
//
//
// You also have a stream of the integers in the range [1, n].
//
// Use the two stack operations to make the numbers in the stack (from the bottom to the top) equal to target. You should follow the following rules:
//
//
// 	If the stream of the integers is not empty, pick the next integer from the stream and push it to the top of the stack.
// 	If the stack is not empty, pop the integer at the top of the stack.
// 	If, at any moment, the elements in the stack (from the bottom to the top) are equal to target, do not read new integers from the stream and do not do more operations on the stack.
//
//
// Return the stack operations needed to build target following the mentioned rules. If there are multiple valid answers, return any of them.
//
// Example:
// Input: target = [1,3], n = 3
// Output: ["Push","Push","Pop","Push"]
// Explanation: Initially the stack s is empty. The last element is the top of the stack.
// Read 1 from the stream and push it to the stack. s = [1].
// Read 2 from the stream and push it to the stack. s = [1,2].
// Pop the integer on the top of the stack. s = [1].
// Read 3 from the stream and push it to the stack. s = [1,3].
//
// Constraints:
// 1 <= target.length <= 100
// 	1 <= n <= 100
// 	1 <= target[i] <= n
// 	target is strictly increasing.
//
// Helpful references (internal KB):
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** buildArray(int* target, int targetSize, int n, int* returnSize) {
    // Maximum possible operations is 2*n (Push and Pop for each number)
    char** operations = (char**)malloc(2 * n * sizeof(char*));
    int opIndex = 0; // Index for operations array
    int targetIndex = 0; // Index for target array

    for (int num = 1; num <= n && targetIndex < targetSize; num++) {
        // Always push the current number
        operations[opIndex] = (char*)malloc(5 * sizeof(char)); // "Push" + null terminator
        strcpy(operations[opIndex], "Push");
        opIndex++;

        // If the current number is not in target, pop it
        if (num != target[targetIndex]) {
            operations[opIndex] = (char*)malloc(4 * sizeof(char)); // "Pop" + null terminator
            strcpy(operations[opIndex], "Pop");
            opIndex++;
        } else {
            // Move to the next target number
            targetIndex++;
        }
    }

    *returnSize = opIndex;
    return operations;      
}
