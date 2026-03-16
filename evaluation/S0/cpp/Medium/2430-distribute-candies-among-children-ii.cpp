// Source: https://leetcode.com/problems/distribute-candies-among-children-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers n and limit.
//
// Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.
//
// Example:
// Input: n = 5, limit = 2
// Output: 3
// Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).
//
// Constraints:
// 1 <= n <= 106
// 	1 <= limit <= 106
//

class Solution {
public:
    long long distributeCandies(int n, int limit) {
        const int MOD = 1e9 + 7;

        auto modInverse = [&](long long a, long long m) {
            long long m0 = m, t, q;
            long long x0 = 0, x1 = 1;

            if (m == 1)
                return 0;

            while (a > 1) {
                q = a / m;
                t = m;

                m = a % m, a = t;
                t = x0;

                x0 = x1 - q * x0;
                x1 = t;
            }

            if (x1 < 0)
                x1 += m0;

            return x1;
        };

        auto nCrMod = [&](long long n, long long r, long long p) {
            if (r > n)
                return 0LL;
            if (r == 0 || r == n)
                return 1LL;

            long long numerator = 1;
            for (long long i = 0; i < r; i++) {
                numerator = (numerator * (n - i)) % p;
            }

            long long denominator = 1;
            for (long long i = 1; i <= r; i++) {
                denominator = (denominator * i) % p;
            }

            return (numerator * modInverse(denominator, p)) % p;
        };

        long long totalWays = nCrMod(n + 3 - 1, 3 - 1, MOD);
        long long invalidWays = 0;

        for (int i = 1; i <= 3; ++i) {
            long long ways = nCrMod(n - i * (limit + 1) + 3 - 1, 3 - 1, MOD);
            if (ways == 0)
                continue;

            if (i % 2 == 1) {
                invalidWays = (invalidWays + (3C(i) * ways) % MOD) % MOD;
            } else {
                invalidWays = (invalidWays - (3C(i) * ways) % MOD + MOD) % MOD;
            }
        }

        return (totalWays - invalidWays + MOD) % MOD;           
    }
};
