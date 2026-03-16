// Source: https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/   |   Difficulty: Easy
//
// Problem Description:
// You are given an m x n integer matrix mat and an integer k. The matrix rows are 0-indexed.
//
// The following proccess happens k times:
//
//
// 	Even-indexed rows (0, 2, 4, ...) are cyclically shifted to the left.
//
//
//
//
//
// 	Odd-indexed rows (1, 3, 5, ...) are cyclically shifted to the right.
//
//
//
//
// Return true if the final modified matrix after k steps is identical to the original matrix, and false otherwise.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 4
//
// Output: false
//
// Explanation:
//
// In each step left shift is applied to rows 0 and 2 (even indices), and right shift to row 1 (odd index).
//
// Constraints:
// 1 <= mat.length <= 25
// 	1 <= mat[i].length <= 25
// 	1 <= mat[i][j] <= 25
// 	1 <= k <= 50
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

bool areSimilar(int** mat, int matSize, int* matColSize, int k) {
    int m = matSize;
    int n = matColSize[0];
    
    // Calculate the effective shifts for even and odd indexed rows
    int evenShift = k % n; // Left shift for even indexed rows
    int oddShift = k % n;  // Right shift for odd indexed rows
    
    // Check each row against the original configuration
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int expectedValue;
            if (i % 2 == 0) { // Even indexed row
                expectedValue = mat[i][(j + evenShift) % n];
            } else { // Odd indexed row
                expectedValue = mat[i][(j - oddShift + n) % n];
            }
            if (mat[i][j] != expectedValue) {
                return false; // If any element does not match, return false
            }
        }
    }
    
    return true; // All elements match, return true     
}
