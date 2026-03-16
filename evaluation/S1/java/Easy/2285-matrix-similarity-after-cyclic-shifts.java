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
// - Gauss method for solving system of linea (bitset, matrix, simulation)
//   • When to use: Use when determining the number of solutions (zero, one, or infinite) for a system of linear equations, or to find the unique solution if it exists. It is suitable for solving systems represented as an augmented matrix.
//   • Idea: Gaussian elimination systematically transforms an augmented matrix into row echelon form using elementary row operations to solve a system of linear equations. It determines the existence and values of solutions in O(N^3) time for an N x N system.
//   • Invariants: The submatrix formed by rows 0 to current_row - 1 is in row echelon form.; For the current column, all elements below the pivot in previous columns are zero.
//   • Tips: Use a small epsilon for floating-point comparisons to handle precision issues.; Implement partial pivoting to enhance numerical stability by selecting the largest absolute value.
//   • Pitfalls: Failing to account for floating-point precision errors can lead to incorrect results.; Improper handling of free variables can misrepresent infinite solution sets.
// - Burnside's lemma / Pólya enumeration theorem (array, number, enumeration, simulation)
//   • When to use: Use when counting the number of distinct configurations or arrangements of objects under a set of symmetry operations, where configurations are considered identical if one can be transformed into another by a group action.
//   • Idea: Burnside's Lemma and Pólya Enumeration Theorem are combinatorial tools used to count the number of distinct objects under a group of symmetries. Both typically involve iterating through group elements and analyzing permutation cycle structures, often resulting in polynomial time complexity depending on group size and element analysis.
//   • Invariants: The set of group elements considered remains consistent throughout the summation.; Each group element's cycle decomposition is correctly identified.
//   • Tips: Identify the group of symmetry operations acting on the objects.; For each group element, determine its permutation cycle structure.
//   • Pitfalls: Incorrectly identifying the full set of distinct group operations.; Errors in determining the cycle structure of permutations.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean areSimilar(int[][] mat, int k) {
        int m = mat.length;
        int n = mat[0].length;

        // Effective shifts needed
        int leftShifts = k % n;  // For even-indexed rows
        int rightShifts = k % n; // For odd-indexed rows

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int shiftedIndex;
                if (i % 2 == 0) {
                    // Even-indexed row: left shift
                    shiftedIndex = (j + leftShifts) % n;
                } else {
                    // Odd-indexed row: right shift
                    shiftedIndex = (j - rightShifts + n) % n;
                }
                if (mat[i][j] != mat[i][shiftedIndex]) {
                    return false;
                }
            }
        }
        return true;            
    }
}
