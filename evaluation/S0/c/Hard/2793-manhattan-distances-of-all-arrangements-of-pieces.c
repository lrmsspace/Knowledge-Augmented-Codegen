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

int distanceSum(int m, int n, int k) {
    const int MOD = 1000000007;
    long long total = 0;
    for (int d = 1; d < m; d++) {
        long long count = (long long)(m - d) * n * n % MOD;
        total = (total + count * d) % MOD;
    }
    for (int d = 1; d < n; d++) {
        long long count = (long long)(n - d) * m * m % MOD;
        total = (total + count * d) % MOD;
    }
    // total now holds the sum of distances for all pairs of cells
    // Now we need to multiply by the number of ways to choose the remaining k-2 pieces
    // from the remaining m*n - 2 cells
    long long ways = 1;
    for (int i = 0; i < k - 2; i++) {
        ways = ways * (m * n - 2 - i) % MOD;
        ways = ways * modInverse(i + 1, MOD) % MOD; // modular inverse for division
    }
    return (int)(total * ways % MOD);       
}
