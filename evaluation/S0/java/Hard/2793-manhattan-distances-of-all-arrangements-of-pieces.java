// Source: https://leetcode.com/problems/manhattan-distances-of-all-arrangements-of-pieces/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers m, n, and k.
//
// There is a rectangular grid of size m × n containing k identical pieces. Return the sum of Manhattan distances between every pair of pieces over all valid arrangements of pieces.
//
// A valid arrangement is a placement of all k pieces on the grid with at most one piece per cell.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
//
// Example:
// Input: m = 2, n = 2, k = 2
//
// Output: 8
//
// Explanation:
//
// The valid arrangements of pieces on the board are:
//
//
//
//
// 	In the first 4 arrangements, the Manhattan distance between the two pieces is 1.
// 	In the last 2 arrangements, the Manhattan distance between the two pieces is 2.
//
//
// Thus, the total Manhattan distance across all valid arrangements is 1 + 1 + 1 + 1 + 2 + 2 = 8.
//
// Constraints:
// 1 <= m, n <= 105
// 	2 <= m * n <= 105
// 	2 <= k <= m * n
//

class Solution {
    public int distanceSum(int m, int n, int k) {
        long mod = 1_000_000_007;
        long totalCells = (long) m * n;

        // Calculate the number of ways to choose k pieces from totalCells
        long totalWays = nCr(totalCells, k, mod);

        // Calculate the sum of Manhattan distances between all pairs of cells
        long distanceSum = 0;

        // Sum of distances in rows
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                distanceSum += (j - i) * n * n;
                distanceSum %= mod;
            }
        }

        // Sum of distances in columns
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                distanceSum += (j - i) * m * m;
                distanceSum %= mod;
            }
        }

        // Each pair of pieces contributes to the total arrangements
        long arrangementsPerPair = nCr(totalCells - 2, k - 2, mod);
        long result = (distanceSum * arrangementsPerPair) % mod;

        return (int) result;            
    }
}
