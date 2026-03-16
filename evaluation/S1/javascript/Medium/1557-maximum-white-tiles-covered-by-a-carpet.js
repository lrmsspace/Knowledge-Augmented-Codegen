// Source: https://leetcode.com/problems/maximum-white-tiles-covered-by-a-carpet/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array tiles where tiles[i] = [li, ri] represents that every tile j in the range li <= j <= ri is colored white.
//
// You are also given an integer carpetLen, the length of a single carpet that can be placed anywhere.
//
// Return the maximum number of white tiles that can be covered by the carpet.
//
// Example:
// Input: tiles = [[1,5],[10,11],[12,18],[20,25],[30,32]], carpetLen = 10
// Output: 9
// Explanation: Place the carpet starting on tile 10. 
// It covers 9 white tiles, so we return 9.
// Note that there may be other places where the carpet covers 9 white tiles.
// It can be shown that the carpet cannot cover more than 9 white tiles.
//
// Constraints:
// 1 <= tiles.length <= 5 * 104
// 	tiles[i].length == 2
// 	1 <= li <= ri <= 109
// 	1 <= carpetLen <= 109
// 	The tiles are non-overlapping.
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} tiles
 * @param {number} carpetLen
 * @return {number}
 */
var maximumWhiteTiles = function(tiles, carpetLen) {
    tiles.sort((a, b) => a[0] - b[0]);
    const n = tiles.length;
    const prefixSums = new Array(n + 1).fill(0);

    for (let i = 0; i < n; i++) {
        prefixSums[i + 1] = prefixSums[i] + (tiles[i][1] - tiles[i][0] + 1);
    }

    let maxCovered = 0;
    let right = 0;

    for (let left = 0; left < n; left++) {
        const carpetStart = tiles[left][0];
        const carpetEnd = carpetStart + carpetLen - 1;

        while (right < n && tiles[right][1] <= carpetEnd) {
            right++;
        }

        let totalCovered = prefixSums[right] - prefixSums[left];

        if (right < n && tiles[right][0] <= carpetEnd) {
            totalCovered += carpetEnd - tiles[right][0] + 1;
        }

        maxCovered = Math.max(maxCovered, totalCovered);
    }

    return maxCovered;
};
