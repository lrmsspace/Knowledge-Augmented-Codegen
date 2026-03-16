// Source: https://leetcode.com/problems/count-paths-with-the-given-xor-value/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array grid with size m x n. You are also given an integer k.
//
// Your task is to calculate the number of paths you can take from the top-left cell (0, 0) to the bottom-right cell (m - 1, n - 1) satisfying the following constraints:
//
//
// 	You can either move to the right or down. Formally, from the cell (i, j) you may move to the cell (i, j + 1) or to the cell (i + 1, j) if the target cell exists.
// 	The XOR of all the numbers on the path must be equal to k.
//
//
// Return the total number of such paths.
//
// Since the answer can be very large, return the result modulo 109 + 7.
//
// Example:
// Input: grid = [[2, 1, 5], [7, 10, 0], [12, 6, 4]], k = 11
//
// Output: 3
//
// Explanation: 
//
// The 3 paths are:
//
//
// 	(0, 0) → (1, 0) → (2, 0) → (2, 1) → (2, 2)
// 	(0, 0) → (1, 0) → (1, 1) → (1, 2) → (2, 2)
// 	(0, 0) → (0, 1) → (1, 1) → (2, 1) → (2, 2)
//
// Constraints:
// 1 <= m == grid.length <= 300
// 	1 <= n == grid[r].length <= 300
// 	0 <= grid[r][c] < 16
// 	0 <= k < 16
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countPathsWithXorValue(int[][] grid, int k) {
        int m = grid.length;
        int n = grid[0].length;
        int MOD = 1_000_000_007;

        // dp[i][j] will store a map of XOR values to their counts for paths ending at (i, j)
        Map<Integer, Integer>[][] dp = new HashMap[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = new HashMap<>();
                int val = grid[i][j];

                if (i == 0 && j == 0) {
                    dp[i][j].put(val, 1);
                } else {
                    if (i > 0) {
                        for (Map.Entry<Integer, Integer> entry : dp[i - 1][j].entrySet()) {
                            int newXor = entry.getKey() ^ val;
                            dp[i][j].put(newXor, (dp[i][j].getOrDefault(newXor, 0) + entry.getValue()) % MOD);
                        }
                    }
                    if (j > 0) {
                        for (Map.Entry<Integer, Integer> entry : dp[i][j - 1].entrySet()) {
                            int newXor = entry.getKey() ^ val;
                            dp[i][j].put(newXor, (dp[i][j].getOrDefault(newXor, 0) + entry.getValue()) % MOD);
                        }
                    }
                }
            }
        }

        return dp[m - 1][n - 1].getOrDefault(k, 0);         
    }
}
