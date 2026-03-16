// Source: https://leetcode.com/problems/right-triangles/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D boolean matrix grid.
//
// A collection of 3 elements of grid is a right triangle if one of its elements is in the same row with another element and in the same column with the third element. The 3 elements may not be next to each other.
//
// Return an integer that is the number of right triangles that can be made with 3 elements of grid such that all of them have a value of 1.
//
// Example:
// 0
// 			1
// 			0
// 		
// 		
// 			0
// 			1
// 			1
// 		
// 		
// 			0
// 			1
// 			0
// 		
// 	
//
//
//
// 	
// 		
// 			0
// 			1
// 			0
// 		
// 		
// 			0
// 			1
// 			1
// 		
// 		
// 			0
// 			1
// 			0
// 		
// 	
//
//
//
// 	
// 		
// 			0
// 			1
// 			0
// 		
// 		
// 			0
// 			1
// 			1
// 		
// 		
// 			0
// 			1
// 			0
// 		
// 	
//
//
//
//
// Input: grid = [[0,1,0],[0,1,1],[0,1,0]]
//
// Output: 2
//
// Explanation:
//
// There are two right triangles with elements of the value 1. Notice that the blue ones do not form a right triangle because the 3 elements are in the same column.
//
// Constraints:
// 1 <= grid.length <= 1000
// 	1 <= grid[i].length <= 1000
// 	0 <= grid[i][j] <= 1
//
// Helpful references (internal KB):
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
//   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
//   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
//   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
//   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
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
var numberOfRightTriangles = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    let count = 0;
    
    // Count right triangles with the right angle at (i, j)
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 1) {
                // Count how many 1s are in the same row and column
                let rowCount = 0;
                let colCount = 0;
                
                // Count in the same row
                for (let k = 0; k < n; k++) {
                    if (k !== j && grid[i][k] === 1) {
                        rowCount++;
                    }
                }
                
                // Count in the same column
                for (let k = 0; k < m; k++) {
                    if (k !== i && grid[k][j] === 1) {
                        colCount++;
                    }
                }
                
                // Each pair of row and column counts forms a right triangle
                count += rowCount * colCount;
            }
        }
    }
    
    return count;
};
