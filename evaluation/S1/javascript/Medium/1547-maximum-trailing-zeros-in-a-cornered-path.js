// Source: https://leetcode.com/problems/maximum-trailing-zeros-in-a-cornered-path/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array grid of size m x n, where each cell contains a positive integer.
//
// A cornered path is defined as a set of adjacent cells with at most one turn. More specifically, the path should exclusively move either horizontally or vertically up to the turn (if there is one), without returning to a previously visited cell. After the turn, the path will then move exclusively in the alternate direction: move vertically if it moved horizontally, and vice versa, also without returning to a previously visited cell.
//
// The product of a path is defined as the product of all the values in the path.
//
// Return the maximum number of trailing zeros in the product of a cornered path found in grid.
//
// Note:
//
//
// 	Horizontal movement means moving in either the left or right direction.
// 	Vertical movement means moving in either the up or down direction.
//
// Example:
// Input: grid = [[23,17,15,3,20],[8,1,20,27,11],[9,4,6,2,21],[40,9,1,10,6],[22,7,4,5,3]]
// Output: 3
// Explanation: The grid on the left shows a valid cornered path.
// It has a product of 15 * 20 * 6 * 1 * 10 = 18000 which has 3 trailing zeros.
// It can be shown that this is the maximum trailing zeros in the product of a cornered path.
//
// The grid in the middle is not a cornered path as it has more than one turn.
// The grid on the right is not a cornered path as it requires a return to a previously visited cell.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= grid[i][j] <= 1000
//
// Helpful references (internal KB):
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} grid
 * @return {number}
 */
var maxTrailingZeros = function(grid) {
    const m = grid.length;
    const n = grid[0].length;

    const countFactors = (num, factor) => {
        let count = 0;
        while (num % factor === 0) {
            count++;
            num /= factor;
        }
        return count;
    };

    const factorCounts = Array.from({ length: m }, () => Array(n).fill([0, 0]));
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            const count2 = countFactors(grid[i][j], 2);
            const count5 = countFactors(grid[i][j], 5);
            factorCounts[i][j] = [count2, count5];
        }
    }

    const prefixRow = Array.from({ length: m }, () => Array(n + 1).fill([0, 0]));
    const prefixCol = Array.from({ length: m + 1 }, () => Array(n).fill([0, 0]));

    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            prefixRow[i][j + 1] = [
                prefixRow[i][j][0] + factorCounts[i][j][0],
                prefixRow[i][j][1] + factorCounts[i][j][1]
            ];
            prefixCol[i + 1][j] = [
                prefixCol[i][j][0] + factorCounts[i][j][0],
                prefixCol[i][j][1] + factorCounts[i][j][1]
            ];
        }
    }

    let maxZeros = 0;

    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            const [up2, up5] = prefixCol[i][j];
            const [down2, down5] = [
                prefixCol[m][j][0] - prefixCol[i + 1][j][0],
                prefixCol[m][j][1] - prefixCol[i + 1][j][1]
            ];
            const [left2, left5] = prefixRow[i][j];
            const [right2, right5] = [
                prefixRow[i][n][0] - prefixRow[i][j + 1][0],
                prefixRow[i][n][1] - prefixRow[i][j + 1][1]
            ];
            const [curr2, curr5] = factorCounts[i][j];
            const paths = [
                [up2 + left2 + curr2, up5 + left5 + curr5],
                [up2 + right2 + curr2, up5 + right5 + curr5],
                [down2 + left2 + curr2, down5 + left5 + curr5],
                [down2 + right2 + curr2, down5 + right5 + curr5]
            ];
            for (const [total2, total5] of paths) {
                maxZeros = Math.max(maxZeros, Math.min(total2, total5));
            }
        }
    }
    return maxZeros;
                
};
