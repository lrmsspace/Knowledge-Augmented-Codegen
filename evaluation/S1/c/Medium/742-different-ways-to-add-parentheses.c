// Source: https://leetcode.com/problems/different-ways-to-add-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.
//
// The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.
//
// Example:
// Input: expression = "2-1-1"
// Output: [0,2]
// Explanation:
// ((2-1)-1) = 0 
// (2-(1-1)) = 2
//
// Constraints:
// 1 <= expression.length <= 20
// 	expression consists of digits and the operator '+', '-', and '*'.
// 	All the integer values in the input expression are in the range [0, 99].
// 	The integer values in the input expression do not have a leading '-' or '+' denoting the sign.
//
// Helpful references (internal KB):
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
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
int* diffWaysToCompute(char* expression, int* returnSize) {
    // Helper function to perform the arithmetic operation
    int compute(int a, int b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            default: return 0; // Should not reach here
        }
    }

    // Base case: if the expression is a number, return it as the only result
    int isNumber = 1;
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] < '0' || expression[i] > '9') {
            isNumber = 0;
            break;
        }
    }
    if (isNumber) {
        int num = atoi(expression);
        int* result = (int*)malloc(sizeof(int));
        result[0] = num;
        *returnSize = 1;
        return result;
    }

    // Recursive case: split the expression at each operator
    int* results = NULL;
    int resultsSize = 0;

    for (int i = 0; expression[i] != '\0'; i++) {
        char op = expression[i];
        if (op == '+' || op == '-' || op == '*') {
            // Split the expression into left and right parts
            char left[21], right[21];
            strncpy(left, expression, i);
            left[i] = '\0';
            strcpy(right, expression + i + 1);

            // Recursively compute results for left and right parts
            int leftSize, rightSize;
            int* leftResults = diffWaysToCompute(left, &leftSize);
            int* rightResults = diffWaysToCompute(right, &rightSize);

            // Combine results from left and right parts using the operator
            for (int l = 0; l < leftSize; l++) {
                for (int r = 0; r < rightSize; r++) {
                    int res = compute(leftResults[l], rightResults[r], op);
                    results = (int*)realloc(results, sizeof(int) * (resultsSize + 1));
                    results[resultsSize++] = res;
                }
            }

            // Free temporary results
            free(leftResults);
            free(rightResults);
        }
    }

    *returnSize = resultsSize;
    return results;     
}
