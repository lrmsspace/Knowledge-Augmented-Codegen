// Source: https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/   |   Difficulty: Medium
//
// Problem Description:
// Given two positive integers n and x.
//
// Return the number of ways n can be expressed as the sum of the xth power of unique positive integers, in other words, the number of sets of unique integers [n1, n2, ..., nk] where n = n1x + n2x + ... + nkx.
//
// Since the result can be very large, return it modulo 109 + 7.
//
// For example, if n = 160 and x = 3, one way to express n is n = 23 + 33 + 53.
//
// Example:
// Input: n = 10, x = 2
// Output: 1
// Explanation: We can express n as the following: n = 32 + 12 = 10.
// It can be shown that it is the only way to express 10 as the sum of the 2nd power of unique integers.
//
// Constraints:
// 1 <= n <= 300
// 	1 <= x <= 5
//

class Solution {
public:
    int numberOfWays(int n, int x) {
        const int MOD = 1e9 + 7;
        vector<int> powers;
        for (int i = 1; ; ++i) {
            int power = pow(i, x);
            if (power > n) break;
            powers.push_back(power);
        }

        vector<int> dp(n + 1, 0);
        dp[0] = 1; // Base case: one way to make sum 0

        for (const int& power : powers) {
            for (int j = n; j >= power; --j) {
                dp[j] = (dp[j] + dp[j - power]) % MOD;
            }
        }

        return dp[n];           
    }
};
