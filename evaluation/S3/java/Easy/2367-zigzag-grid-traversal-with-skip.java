// Source: https://leetcode.com/problems/zigzag-grid-traversal-with-skip/   |   Difficulty: Easy
//
// Problem Description:
// You are given an m x n 2D array grid of positive integers.
//
// Your task is to traverse grid in a zigzag pattern while skipping every alternate cell.
//
// Zigzag pattern traversal is defined as following the below actions:
//
//
// 	Start at the top-left cell (0, 0).
// 	Move right within a row until the end of the row is reached.
// 	Drop down to the next row, then traverse left until the beginning of the row is reached.
// 	Continue alternating between right and left traversal until every row has been traversed.
//
//
// Note that you must skip every alternate cell during the traversal.
//
// Return an array of integers result containing, in order, the value of the cells visited during the zigzag traversal with skips.
//
// Example:
// Input: grid = [[1,2],[3,4]]
//
// Output: [1,4]
//
// Explanation:
//
// Constraints:
// 2 <= n == grid.length <= 50
// 	2 <= m == grid[i].length <= 50
// 	1 <= grid[i][j] <= 2500
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> zigzagTraversal(int[][] grid) {
        List<Integer> result = new ArrayList<>();
        int m = grid.length, n = grid[0].length;
        boolean leftToRight = true;

        for (int i = 0; i < m; i++) {
            if (leftToRight) {
                for (int j = 0; j < n; j += 2) {
                    result.add(grid[i][j]);
                }
            } else {
                for (int j = n - 1; j >= 0; j -= 2) {
                    result.add(grid[i][j]);
                }
            }
            leftToRight = !leftToRight;
        }

        return result;          
    }
}
