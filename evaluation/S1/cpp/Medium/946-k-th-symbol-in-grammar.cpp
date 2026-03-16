// Source: https://leetcode.com/problems/k-th-symbol-in-grammar/   |   Difficulty: Medium
//
// Problem Description:
// We build a table of n rows (1-indexed). We start by writing 0 in the 1st row. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.
//
//
// 	For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110.
//
//
// Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.
//
// Example:
// Input: n = 1, k = 1
// Output: 0
// Explanation: row 1: 0
//
// Constraints:
// 1 <= n <= 30
// 	1 <= k <= 2n - 1
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int kthGrammar(int n, int k) {
        if (n == 1 && k == 1) return 0;
        int parent = kthGrammar(n - 1, (k + 1) / 2);
        if (k % 2 == 1) {
            return parent;
        } else {
            return 1 - parent;
        }           
    }
};
