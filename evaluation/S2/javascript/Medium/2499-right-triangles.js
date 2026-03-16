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
// - Calculating the determinant of a matrix by Gauss (matrix, number, simulation, counting)
//   • When to use: When needing to compute the determinant of a square matrix, especially when Gaussian elimination is a familiar or efficient approach. It is suitable for matrices where direct cofactor expansion is computationally too expensive.
//   • Idea: This algorithm computes the determinant of a square matrix by transforming it into an upper triangular form using Gaussian elimination. The determinant is the product of diagonal elements, adjusted by a sign factor from row swaps, with O(N^3) complexity.
//   • Invariants: Before processing column 'k', all elements A[i][j] where i > j and j < k are zero.; The determinant of the current matrix, multiplied by (-1)^swaps, equals the original matrix's determinant.
//   • Tips: Track the number of row swaps to correctly determine the determinant's sign.; Pivot selection can improve numerical stability, especially with floating-point numbers.
//   • Pitfalls: Forgetting to adjust the sign after row exchanges.; Division by zero if a pivot element is zero, requiring a row swap.
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
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
    const rows = grid.length;
    const cols = grid[0].length;
    const rowCounts = new Array(rows).fill(0);
    const colCounts = new Array(cols).fill(0);
    
    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            if (grid[i][j] === 1) {
                rowCounts[i]++;
                colCounts[j]++;
            }
        }
    }
    
    let count = 0;
    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            if (grid[i][j] === 1) {
                count += (rowCounts[i] - 1) * (colCounts[j] - 1);
            }
        }
    }
    
    return count;
};
