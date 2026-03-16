// Source: https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or '.', return the number of submatrices that contain:
//
//
// 	grid[0][0]
// 	an equal frequency of 'X' and 'Y'.
// 	at least one 'X'.
//
// Example:
// Input: grid = [["X","Y","."],["Y",".","."]]
//
// Output: 3
//
// Explanation:
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 1000
// 	grid[i][j] is either 'X', 'Y', or '.'.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {character[][]} grid
 * @return {number}
 */
var numberOfSubmatrices = function(grid) {
    const rows = grid.length;
    const cols = grid[0].length;
    let count = 0;

    // Precompute the prefix sums for 'X' and 'Y'
    const prefixX = Array.from({ length: rows + 1 }, () => Array(cols + 1).fill(0));
    const prefixY = Array.from({ length: rows + 1 }, () => Array(cols + 1).fill(0));

    for (let i = 1; i <= rows; i++) {
        for (let j = 1; j <= cols; j++) {
            prefixX[i][j] = prefixX[i - 1][j] + prefixX[i][j - 1] - prefixX[i - 1][j - 1] + (grid[i - 1][j - 1] === 'X' ? 1 : 0);
            prefixY[i][j] = prefixY[i - 1][j] + prefixY[i][j - 1] - prefixY[i - 1][j - 1] + (grid[i - 1][j - 1] === 'Y' ? 1 : 0);
        }
    }

    // Iterate over all possible submatrices
    for (let r1 = 1; r1 <= rows; r1++) {
        for (let r2 = r1; r2 <= rows; r2++) {
            for (let c1 = 1; c1 <= cols; c1++) {
                for (let c2 = c1; c2 <= cols; c2++) {
                    const countX = prefixX[r2][c2] - prefixX[r2][c1 - 1] - prefixX[r1 - 1][c2] + prefixX[r1 - 1][c1 - 1];
                    const countY = prefixY[r2][c2] - prefixY[r2][c1 - 1] - prefixY[r1 - 1][c2] + prefixY[r1 - 1][c1 - 1];
                    if (countX > 0 && countX === countY) {
                        count++;
                    }
                }
            }
        }
    }

    return count;
};
