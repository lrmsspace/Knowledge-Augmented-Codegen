// Source: https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n.
//
// A binary string x is valid if all substrings of x of length 2 contain at least one "1".
//
// Return all valid strings with length n, in any order.
//
// Example:
// Input: n = 3
//
// Output: ["010","011","101","110","111"]
//
// Explanation:
//
// The valid strings of length 3 are: "010", "011", "101", "110", and "111".
//
// Constraints:
// 1 <= n <= 18
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
char** validStrings(int n, int* returnSize) {
    // Calculate the number of valid strings using dynamic programming
    int dp[n + 1];
    dp[0] = 1; // Base case: one valid string of length 0 (the empty string)
    dp[1] = 2; // Base case: two valid strings of length 1 ("0" and "1")

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2]; // The number of valid strings of length i is the sum of the last two lengths
    }

    *returnSize = dp[n]; // Set the return size to the number of valid strings of length n
    char** result = (char**)malloc((*returnSize) * sizeof(char*)); // Allocate memory for the result array

    // Generate all valid strings using backtracking
    void backtrack(char* current, int length) {
        if (length == n) {
            result[(*returnSize) - 1] = strdup(current); // Store a copy of the current valid string
            (*returnSize)--;
            return;
        }
        current[length] = '1'; // Add '1' and continue backtracking
        backtrack(current, length + 1);
        current[length] = '0'; // Add '0' and continue backtracking only if the previous character is not '0'
        if (length == 0 || current[length - 1] != '0') {
            backtrack(current, length + 1);
        }
    }

    char current[n + 1]; // Temporary array to build the current string
    current[n] = '\0'; // Null-terminate the string
    backtrack(current, 0); // Start backtracking from an empty string

    return result; // Return the array of valid strings     
}
