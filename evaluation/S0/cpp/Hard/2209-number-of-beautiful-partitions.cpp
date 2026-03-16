// Source: https://leetcode.com/problems/number-of-beautiful-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s that consists of the digits '1' to '9' and two integers k and minLength.
//
// A partition of s is called beautiful if:
//
//
// 	s is partitioned into k non-intersecting substrings.
// 	Each substring has a length of at least minLength.
// 	Each substring starts with a prime digit and ends with a non-prime digit. Prime digits are '2', '3', '5', and '7', and the rest of the digits are non-prime.
//
//
// Return the number of beautiful partitions of s. Since the answer may be very large, return it modulo 109 + 7.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "23542185131", k = 3, minLength = 2
// Output: 3
// Explanation: There exists three ways to create a beautiful partition:
// "2354 | 218 | 5131"
// "2354 | 21851 | 31"
// "2354218 | 51 | 31"
//
// Constraints:
// 1 <= k, minLength <= s.length <= 1000
// 	s consists of the digits '1' to '9'.
//

class Solution {
public:
    int beautifulPartitions(string s, int k, int minLength) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<int> primeDigits = {2, 3, 5, 7};
        auto isPrime = [&](char c) {
            for (int pd : primeDigits) {
                if (c - '0' == pd) return true;
            }
            return false;
        };
        
        if (!isPrime(s[0]) || isPrime(s[n - 1])) {
            return 0;
        }
        
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        vector<int> prefixSum(n + 1, 0);
        dp[0][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            prefixSum[i] = (prefixSum[i - 1] + dp[i - 1][0]) % MOD;
            for (int j = 1; j <= k; j++) {
                if (i >= minLength && isPrime(s[i - minLength]) && !isPrime(s[i - 1])) {
                    dp[i][j] = (dp[i][j] + prefixSum[i - minLength + 1]) % MOD;
                }
                prefixSum[i] = (prefixSum[i] + dp[i][j]) % MOD;
            }
        }
        
        return dp[n][k];            
    }
};
