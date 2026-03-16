// Source: https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given a 1-indexed m x n integer matrix mat, you can select any cell in the matrix as your starting cell.
//
// From the starting cell, you can move to any other cell in the same row or column, but only if the value of the destination cell is strictly greater than the value of the current cell. You can repeat this process as many times as possible, moving from cell to cell until you can no longer make any moves.
//
// Your task is to find the maximum number of cells that you can visit in the matrix by starting from some cell.
//
// Return an integer denoting the maximum number of cells that can be visited.
//
// Example:
// Input: mat = [[3,1],[3,4]]
// Output: 2
// Explanation: The image shows how we can visit 2 cells starting from row 1, column 2. It can be shown that we cannot visit more than 2 cells no matter where we start from, so the answer is 2.
//
// Constraints:
// m == mat.length 
// 	n == mat[i].length 
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	-105 <= mat[i][j] <= 105
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxIncreasingCells(int[][] mat) {
        int m = mat.length;
        int n = mat[0].length;

        int[][] cells = new int[m * n][3];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cells[i * n + j] = new int[]{mat[i][j], i, j};
            }
        }
        Arrays.sort(cells, (a, b) -> Integer.compare(a[0], b[0]));

        int[] rowMax = new int[m];
        int[] colMax = new int[n];
        int maxLen = 1;

        for (int i = 0; i < m * n; ) {
            int j = i;
            List<int[]> updates = new ArrayList<>();
            while (j < m * n && cells[j][0] == cells[i][0]) {
                int r = cells[j][1];
                int c = cells[j][2];
                int len = Math.max(rowMax[r], colMax[c]) + 1;
                updates.add(new int[]{r, c, len});
                maxLen = Math.max(maxLen, len);
                j++;
            }
            for (int[] upd : updates) {
                int r = upd[0];
                int c = upd[1];
                int len = upd[2];
                rowMax[r] = Math.max(rowMax[r], len);
                colMax[c] = Math.max(colMax[c], len);
            }
            i = j;
        }

        return maxLen;          
    }
}
