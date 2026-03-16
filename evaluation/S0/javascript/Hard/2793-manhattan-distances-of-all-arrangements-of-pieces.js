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

/**
 * @param {number} m
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var distanceSum = function(m, n, k) {
    const MOD = 1e9 + 7;

    function modInverse(a, mod) {   
        let m0 = mod, t, q;
        let x0 = 0, x1 = 1;
        if (mod === 1) return 0;
        while (a > 1) {
            q = Math.floor(a / mod);
            t = mod;
            mod = a % mod; a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        if (x1 < 0) x1 += m0;
        return x1;
    }
    const totalCells = m * n;
    let totalDistance = 0;
    for (let d = 1; d < n; d++) {
        const pairs = (m * (n - d)) % MOD;
        totalDistance = (totalDistance + (pairs * d) % MOD) % MOD;
    }
    for (let d = 1; d < m; d++) {
        const pairs = (n * (m - d)) % MOD;
        totalDistance = (totalDistance + (pairs * d) % MOD) % MOD;
    }
    let arrangements = 1;
    for (let i = 0; i < k; i++) {
        arrangements = (arrangements * (totalCells - i)) % MOD;
        arrangements = (arrangements * modInverse(i + 1, MOD)) % MOD;
    }
    arrangements = (arrangements * modInverse(((totalCells * (totalCells - 1)) / 2) % MOD, MOD)) % MOD;
    const result = (totalDistance * arrangements) % MOD;
    return result;  
};
