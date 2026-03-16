// Source: https://leetcode.com/problems/difference-of-number-of-distinct-values-on-diagonals/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D grid of size m x n, you should find the matrix answer of size m x n.
//
// The cell answer[r][c] is calculated by looking at the diagonal values of the cell grid[r][c]:
//
//
// 	Let leftAbove[r][c] be the number of distinct values on the diagonal to the left and above the cell grid[r][c] not including the cell grid[r][c] itself.
// 	Let rightBelow[r][c] be the number of distinct values on the diagonal to the right and below the cell grid[r][c], not including the cell grid[r][c] itself.
// 	Then answer[r][c] = |leftAbove[r][c] - rightBelow[r][c]|.
//
//
// A matrix diagonal is a diagonal line of cells starting from some cell in either the topmost row or leftmost column and going in the bottom-right direction until the end of the matrix is reached.
//
//
// 	For example, in the below diagram the diagonal is highlighted using the cell with indices (2, 3) colored gray:
//
// 	
// 		Red-colored cells are left and above the cell.
// 		Blue-colored cells are right and below the cell.
// 	
// 	
//
//
//
//
// Return the matrix answer.
//
// Example:
// Input: grid = [[1,2,3],[3,1,5],[3,2,1]]
//
// Output: Output: [[1,1,0],[1,0,1],[0,1,1]]
//
// Explanation:
//
// To calculate the answer cells:
//
//
// 	
// 		
// 			answer
// 			left-above elements
// 			leftAbove
// 			right-below elements
// 			rightBelow
// 			|leftAbove - rightBelow|
// 		
// 	
// 	
// 		
// 			[0][0]
// 			[]
// 			0
// 			[grid[1][1], grid[2][2]]
// 			|{1, 1}| = 1
// 			1
// 		
// 		
// 			[0][1]
// 			[]
// 			0
// 			[grid[1][2]]
// 			|{5}| = 1
// 			1
// 		
// 		
// 			[0][2]
// 			[]
// 			0
// 			[]
// 			0
// 			0
// 		
// 		
// 			[1][0]
// 			[]
// 			0
// 			[grid[2][1]]
// 			|{2}| = 1
// 			1
// 		
// 		
// 			[1][1]
// 			[grid[0][0]]
// 			|{1}| = 1
// 			[grid[2][2]]
// 			|{1}| = 1
// 			0
// 		
// 		
// 			[1][2]
// 			[grid[0][1]]
// 			|{2}| = 1
// 			[]
// 			0
// 			1
// 		
// 		
// 			[2][0]
// 			[]
// 			0
// 			[]
// 			0
// 			0
// 		
// 		
// 			[2][1]
// 			[grid[1][0]]
// 			|{3}| = 1
// 			[]
// 			0
// 			1
// 		
// 		
// 			[2][2]
// 			[grid[0][0], grid[1][1]]
// 			|{1, 1}| = 1
// 			[]
// 			0
// 			1
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n, grid[i][j] <= 50
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (ds, enumeration)
//   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
//   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
//   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
//   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
//   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[][] differenceOfDistinctValues(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] answer = new int[m][n];

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                Set<Integer> leftAbove = new HashSet<>();
                Set<Integer> rightBelow = new HashSet<>();

                for (int i = 1; r - i >= 0 && c - i >= 0; i++) {
                    leftAbove.add(grid[r - i][c - i]);
                }

                for (int i = 1; r + i < m && c + i < n; i++) {
                    rightBelow.add(grid[r + i][c + i]);
                }

                answer[r][c] = Math.abs(leftAbove.size() - rightBelow.size());
            }
        }

        return answer;          
    }
}
