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

int numberOfWays(int n, int x) {
    const int MOD = 1e9 + 7;
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1; // There's one way to make sum 0: use no numbers

    // Precompute all powers less than or equal to n
    int powers[20]; // Since x <= 5 and n <= 300, we won't have more than 20 such powers
    int count = 0;
    for (int i = 1; ; i++) {
        int power = 1;
        for (int j = 0; j < x; j++) {
            power *= i;
        }
        if (power > n) break;
        powers[count++] = power;
    }

    // Dynamic programming to count ways
    for (int i = 0; i < count; i++) {
        for (int j = n; j >= powers[i]; j--) {
            dp[j] = (dp[j] + dp[j - powers[i]]) % MOD;
        }
    }

    return dp[n];       
}
