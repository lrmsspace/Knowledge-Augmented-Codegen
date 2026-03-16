// Source: https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/   |   Difficulty: Easy
//
// Problem Description:
// No-Zero integer is a positive integer that does not contain any 0 in its decimal representation.
//
// Given an integer n, return a list of two integers [a, b] where:
//
//
// 	a and b are No-Zero integers.
// 	a + b = n
//
//
// The test cases are generated so that there is at least one valid solution. If there are many valid solutions, you can return any of them.
//
// Example:
// Input: n = 2
// Output: [1,1]
// Explanation: Let a = 1 and b = 1.
// Both a and b are no-zero integers, and a + b = 2 = n.
//
// Constraints:
// 2 <= n <= 104
//
// Helpful references (internal KB):
// - N/A
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
int* getNoZeroIntegers(int n, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 1; i < n; i++) {
        int a = i;
        int b = n - i;

        // Check if 'a' and 'b' are no-zero integers
        if (!hasZero(a) && !hasZero(b)) {
            result[0] = a;
            result[1] = b;
            return result;
        }
    }

    // This line should never be reached due to problem constraints
    free(result);
    return NULL;        
}
