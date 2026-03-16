// Source: https://leetcode.com/problems/maximum-rows-covered-by-columns/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix matrix and an integer numSelect.
//
// Your goal is to select exactly numSelect distinct columns from matrix such that you cover as many rows as possible.
//
// A row is considered covered if all the 1's in that row are also part of a column that you have selected. If a row does not have any 1s, it is also considered covered.
//
// More formally, let us consider selected = {c1, c2, ...., cnumSelect} as the set of columns selected by you. A row i is covered by selected if:
//
//
// 	For each cell where matrix[i][j] == 1, the column j is in selected.
// 	Or, no cell in row i has a value of 1.
//
//
// Return the maximum number of rows that can be covered by a set of numSelect columns.
//
// Example:
// Input: matrix = [[0,0,0],[1,0,1],[0,1,1],[0,0,1]], numSelect = 2
//
// Output: 3
//
// Explanation:
//
// One possible way to cover 3 rows is shown in the diagram above.
// We choose s = {0, 2}.
// - Row 0 is covered because it has no occurrences of 1.
// - Row 1 is covered because the columns with value 1, i.e. 0 and 2 are present in s.
// - Row 2 is not covered because matrix[2][1] == 1 but 1 is not present in s.
// - Row 3 is covered because matrix[2][2] == 1 and 2 is present in s.
// Thus, we can cover three rows.
// Note that s = {1, 2} will also cover 3 rows, but it can be shown that no more than three rows can be covered.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 12
// 	matrix[i][j] is either 0 or 1.
// 	1 <= numSelect <= n
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} matrix
 * @param {number} numSelect
 * @return {number}
 */
var maximumRows = function(matrix, numSelect) {
    const m = matrix.length;
    const n = matrix[0].length;
    let maxCovered = 0;
    
    // Iterate through all combinations of columns
    for (let mask = 0; mask < (1 << n); mask++) {
        if (countBits(mask) === numSelect) {
            let covered = 0;
            for (let i = 0; i < m; i++) {
                let rowCovered = true;
                for (let j = 0; j < n; j++) {
                    if (matrix[i][j] === 1 && ((mask & (1 << j)) === 0)) {
                        rowCovered = false;
                        break;
                    }
                }
                if (rowCovered) covered++;
            }
            maxCovered = Math.max(maxCovered, covered);
        }
    }
    
    return maxCovered;
};
