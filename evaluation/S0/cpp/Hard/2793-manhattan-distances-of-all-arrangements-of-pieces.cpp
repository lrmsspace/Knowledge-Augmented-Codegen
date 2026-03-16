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
public:
    int distanceSum(int m, int n, int k) {
        const int MOD = 1e9 + 7;
        
        // Precompute factorials and inverse factorials for combinations
        long long fact[100005], invFact[100005];
        fact[0] = 1;
        for (int i = 1; i <= m * n; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        
        invFact[m * n] = modInverse(fact[m * n], MOD);
        for (int i = m * n - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }
        
        auto comb = [&](int a, int b) {
            if (b > a || b < 0) return 0LL;
            return fact[a] * invFact[b] % MOD * invFact[a - b] % MOD;
        };
        
        long long totalWays = comb(m * n, k);
        long long result = 0;
        
        // Calculate contribution from row distances
        for (int d = 1; d < m; d++) {
            long long pairs = (long long)(m - d) * n % MOD * n % MOD;
            long long ways = comb(m * n - 2, k - 2);
            result = (result + pairs * d % MOD * ways % MOD) % MOD;
        }
        
        // Calculate contribution from column distances
        for (int d = 1; d < n; d++) {
            long long pairs = (long long)(n - d) * m % MOD * m % MOD;
            long long ways = comb(m * n - 2, k - 2);
            result = (result + pairs * d % MOD * ways % MOD) % MOD;
        }
        
        return result;          
    }
};
