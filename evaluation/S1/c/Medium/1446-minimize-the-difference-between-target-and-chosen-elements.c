// Source: https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix mat and an integer target.
//
// Choose one integer from each row in the matrix such that the absolute difference between target and the sum of the chosen elements is minimized.
//
// Return the minimum absolute difference.
//
// The absolute difference between two numbers a and b is the absolute value of a - b.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], target = 13
// Output: 0
// Explanation: One possible choice is to:
// - Choose 1 from the first row.
// - Choose 5 from the second row.
// - Choose 7 from the third row.
// The sum of the chosen elements is 13, which equals the target, so the absolute difference is 0.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 70
// 	1 <= mat[i][j] <= 70
// 	1 <= target <= 800
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimizeTheDifference(int** mat, int matSize, int* matColSize, int target) {
    // Dynamic Programming approach
    // dp[i][j] will be true if a sum of j can be formed using elements from the first i rows
    int maxSum = 70 * matSize; // Maximum possible sum given constraints
    int dp[matSize + 1][maxSum + 1];
    
    // Initialize dp array
    for (int i = 0; i <= matSize; i++) {
        for (int j = 0; j <= maxSum; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1; // Base case: sum of 0 with 0 rows

    // Fill the dp table
    for (int i = 1; i <= matSize; i++) {
        for (int j = 0; j <= maxSum; j++) {
            for (int k = 0; k < matColSize[i - 1]; k++) {
                int val = mat[i - 1][k];
                if (j >= val && dp[i - 1][j - val]) {
                    dp[i][j] = 1;
                    break; // No need to check further if we found a valid sum
                }
            }
        }
    }

    // Find the minimum absolute difference
    int minDiff = target; // Start with the maximum possible difference
    for (int j = 0; j <= maxSum; j++) {
        if (dp[matSize][j]) {
            int diff = j > target ? j - target : target - j;
            if (diff < minDiff) {
                minDiff = diff;
            }
        }
    }

    return minDiff;     
}
