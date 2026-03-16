// Source: https://leetcode.com/problems/count-k-reducible-numbers-less-than-n/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s representing a number n in its binary form.
//
// You are also given an integer k.
//
// An integer x is called k-reducible if performing the following operation at most k times reduces it to 1:
//
//
// 	Replace x with the count of set bits in its binary representation.
//
//
// For example, the binary representation of 6 is "110". Applying the operation once reduces it to 2 (since "110" has two set bits). Applying the operation again to 2 (binary "10") reduces it to 1 (since "10" has one set bit).
//
// Return an integer denoting the number of positive integers less than n that are k-reducible.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "111", k = 1
//
// Output: 3
//
// Explanation: 
//
// n = 7. The 1-reducible integers less than 7 are 1, 2, and 4.
//
// Constraints:
// 1 <= s.length <= 800
// 	s has no leading zeros.
// 	s consists only of the characters '0' and '1'.
// 	1 <= k <= 5
//

class Solution {
public:
    int countKReducibleNumbers(string s, int k) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        
        // Precompute the number of steps to reduce to 1 for counts up to n
        vector<int> steps(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            steps[i] = steps[__builtin_popcount(i)] + 1;
        }
        
        // Count valid numbers using DP
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        dp[0][0] = 1; // empty prefix
        
        for (int i = 0; i < n; i++) {
            for (int smaller = 0; smaller <= 1; smaller++) {
                int limit = smaller ? 1 : (s[i] - '0');
                for (int bit = 0; bit <= limit; bit++) {
                    int newSmaller = smaller || (bit < limit);
                    dp[i + 1][newSmaller] = (dp[i + 1][newSmaller] + dp[i][smaller]) % MOD;
                }
            }
        }
        
        // Count valid numbers with exactly j set bits
        vector<int> countSetBits(n + 1, 0);
        for (int bits = 1; bits <= n; bits++) {
            if (steps[bits] == k - 1) {
                countSetBits[bits] = 1;
            }
        }
        
        // Calculate final result
        int result = 0;
        for (int bits = 1; bits <= n; bits++) {
            if (countSetBits[bits]) {
                int ways = 0;
                for (int smaller = 0; smaller <= 1; smaller++) {
                    ways = (ways + dp[n][smaller]) % MOD;
                }
                result = (result + ways) % MOD;
            }
        }
        
        // Adjust for the case when k == 1 and we counted '1' which is not less than n
        if (k == 1) {
            result = (result - 1 + MOD) % MOD;
        }
        
        return result;          
    }
};
