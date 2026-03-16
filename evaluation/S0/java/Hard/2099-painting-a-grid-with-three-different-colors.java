// Source: https://leetcode.com/problems/painting-a-grid-with-three-different-colors/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers m and n. Consider an m x n grid where each cell is initially white. You can paint each cell red, green, or blue. All cells must be painted.
//
// Return the number of ways to color the grid with no two adjacent cells having the same color. Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: m = 1, n = 1
// Output: 3
// Explanation: The three possible colorings are shown in the image above.
//
// Constraints:
// 1 <= m <= 5
// 	1 <= n <= 1000
//

class Solution {
    public int colorTheGrid(int m, int n) {
        int MOD = 1_000_000_007;

        // Generate all valid column colorings
        List<Integer> validColumns = new ArrayList<>();
        generateValidColumns(m, 0, 0, validColumns);

        // Build adjacency list for valid columns
        Map<Integer, List<Integer>> adj = new HashMap<>();
        for (int col1 : validColumns) {
            for (int col2 : validColumns) {
                if (areCompatible(col1, col2, m)) {
                    adj.computeIfAbsent(col1, k -> new ArrayList<>()).add(col2);
                }
            }
        }

        // DP array to count ways to color the grid
        Map<Integer, Integer> dp = new HashMap<>();
        for (int col : validColumns) {
            dp.put(col, 1);
        }

        // Fill DP table for n columns
        for (int i = 1; i < n; i++) {
            Map<Integer, Integer> newDp = new HashMap<>();
            for (int col : validColumns) {
                int count = dp.get(col);
                for (int neighbor : adj.get(col)) {
                    newDp.put(neighbor, (newDp.getOrDefault(neighbor, 0) + count) % MOD);
                }
            }
            dp = newDp;
        }

        // Sum up all ways to color the last column
        int result = 0;
        for (int count : dp.values()) {
            result = (result + count) % MOD;
        }

        return result;          
    }
}
