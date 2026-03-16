// Source: https://leetcode.com/problems/numbers-with-same-consecutive-differences/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, return an array of all the integers of length n where the difference between every two consecutive digits is k. You may return the answer in any order.
//
// Note that the integers should not have leading zeros. Integers as 02 and 043 are not allowed.
//
// Example:
// Input: n = 3, k = 7
// Output: [181,292,707,818,929]
// Explanation: Note that 070 is not a valid number, because it has leading zeroes.
//
// Constraints:
// 2 <= n <= 9
// 	0 <= k <= 9
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Generating all K-combinations (bitset, recursion, enumeration)
//   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
//   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
//   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
//   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
//   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
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
int* numsSameConsecDiff(int n, int k, int* returnSize) {
    // Helper function to perform DFS and generate valid numbers
    void dfs(int num, int length, int n, int k, int* result, int* returnSize) {
        if (length == n) {
            result[(*returnSize)++] = num; // Store the valid number and increment returnSize
            return;
        }
        
        int lastDigit = num % 10; // Get the last digit of the current number
        
        // Calculate the next possible digits based on the last digit and k
        int nextDigits[2] = {lastDigit + k, lastDigit - k};
        
        for (int i = 0; i < 2; i++) {
            int nextDigit = nextDigits[i];
            // Check if the next digit is valid (0-9)
            if (nextDigit >= 0 && nextDigit <= 9) {
                dfs(num * 10 + nextDigit, length + 1, n, k, result, returnSize); // Recur with the new number and increased length
            }
        }
    }
    
    // Edge case: If n is 1, return all digits from 0 to 9
    if (n == 1) {
        *returnSize = 10;
        int* result = (int*)malloc(sizeof(int) * (*returnSize));
        for (int i = 0; i < 10; i++) {
            result[i] = i;
        }
        return result;
    }
    
    // Allocate memory for results (worst case: all numbers are valid)
    int maxResults = 10000; // Arbitrary large number to hold results
    int* result = (int*)malloc(sizeof(int) * maxResults);
    *returnSize = 0;
    
    // Start DFS for each digit from 1 to 9 (no leading zeros)
    for (int i = 1; i <= 9; i++) {
        dfs(i, 1, n, k, result, returnSize);
    }
    
    return result; // Return the array of valid numbers     
}
