// Source: https://leetcode.com/problems/determine-the-minimum-sum-of-a-k-avoiding-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers, n and k.
//
// An array of distinct positive integers is called a k-avoiding array if there does not exist any pair of distinct elements that sum to k.
//
// Return the minimum possible sum of a k-avoiding array of length n.
//
// Example:
// Input: n = 5, k = 4
// Output: 18
// Explanation: Consider the k-avoiding array [1,2,4,5,6], which has a sum of 18.
// It can be proven that there is no k-avoiding array with a sum less than 18.
//
// Constraints:
// 1 <= n, k <= 50
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

int minimumSum(int n, int k) {
    int sum = 0;
    int count = 0;
    for (int i = 1; count < n; i++) {
        if (i >= k) {
            sum += i;
            count++;
        } else if (i < k / 2 || i > k / 2) {
            sum += i;
            count++;
        }
    }
    return sum;     
}
