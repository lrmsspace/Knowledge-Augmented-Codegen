// Source: https://leetcode.com/problems/minimum-operations-to-write-the-letter-y-on-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed n x n grid where n is odd, and grid[r][c] is 0, 1, or 2.
//
// We say that a cell belongs to the Letter Y if it belongs to one of the following:
//
//
// 	The diagonal starting at the top-left cell and ending at the center cell of the grid.
// 	The diagonal starting at the top-right cell and ending at the center cell of the grid.
// 	The vertical line starting at the center cell and ending at the bottom border of the grid.
//
//
// The Letter Y is written on the grid if and only if:
//
//
// 	All values at cells belonging to the Y are equal.
// 	All values at cells not belonging to the Y are equal.
// 	The values at cells belonging to the Y are different from the values at cells not belonging to the Y.
//
//
// Return the minimum number of operations needed to write the letter Y on the grid given that in one operation you can change the value at any cell to 0, 1, or 2.
//
// Example:
// Input: grid = [[1,2,2],[1,1,0],[0,1,0]]
// Output: 3
// Explanation: We can write Y on the grid by applying the changes highlighted in blue in the image above. After the operations, all cells that belong to Y, denoted in bold, have the same value of 1 while those that do not belong to Y are equal to 0.
// It can be shown that 3 is the minimum number of operations needed to write Y on the grid.
//
// Constraints:
// 3 <= n <= 49 
// 	n == grid.length == grid[i].length
// 	0 <= grid[i][j] <= 2
// 	n is odd.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Lattice points inside non-lattice polygon (geometry, number, counting, recursion)
//   • When to use: Use this when you need to count integer coordinate points strictly inside a polygon whose vertices are not restricted to integer coordinates. It's suitable for problems requiring precise geometric counting with non-lattice boundaries.
//   • Idea: This algorithm counts lattice points within a polygon with arbitrary vertices by summing signed contributions from each edge. It reduces the problem to evaluating sums of floor functions, sum(floor(kx+b)), which is solved recursively, typically achieving logarithmic complexity per edge.
//   • Invariants: The sum sum(floor(kx+b)) correctly accumulates points below the current edge segment.; After coordinate transformations, the problem reduces to a sum over a non-negative range with non-negative k and b.
//   • Tips: Decompose the polygon into signed areas under each edge, similar to the shoelace formula.; Handle edge cases where k or b are negative by appropriate transformations.
//   • Pitfalls: Floating point precision issues when calculating k and b or during transformations.; Incorrectly handling boundary points (points on edges or vertices).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean isInY(int r, int c, int n) {
        int center = n / 2;
        return (c == center && r >= center) || (r == c && r <= center) || (r + c == n - 1 && r <= center);
    }
    public int minimumOperationsToWriteY(int[][] grid) {
        int n = grid.length;
        int yCount = 4 * (n / 2) + 1;
        int nonYCount = n * n - yCount;

        int[][] yFreq = new int[3][1];
        int[][] nonYFreq = new int[3][1];

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (isInY(r, c, n)) {
                    yFreq[grid[r][c]][0]++;
                } else {
                    nonYFreq[grid[r][c]][0]++;
                }
            }
        }

        int minOperations = Integer.MAX_VALUE;

        for (int yVal = 0; yVal <= 2; yVal++) {
            for (int nonYVal = 0; nonYVal <= 2; nonYVal++) {
                if (yVal != nonYVal) {
                    int operations = (yCount - yFreq[yVal][0]) + (nonYCount - nonYFreq[nonYVal][0]);
                    minOperations = Math.min(minOperations, operations);
                }
            }
        }

        return minOperations;           
    }
}
