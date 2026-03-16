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

class Solution {
    public boolean areSimilar(int[][] mat, int k) {
        int m = mat.length;
        int n = mat[0].length;

        for (int i = 0; i < m; i++) {
            int shift = k % n;
            for (int j = 0; j < n; j++) {
                int originalIndex;
                if (i % 2 == 0) { // even-indexed row
                    originalIndex = (j + shift) % n;
                } else { // odd-indexed row
                    originalIndex = (j - shift + n) % n;
                }
                if (mat[i][j] != mat[i][originalIndex]) {
                    return false;
                }
            }
        }
        return true;            
    }
}
