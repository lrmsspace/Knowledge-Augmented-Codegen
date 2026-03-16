// Source: https://leetcode.com/problems/count-stepping-numbers-in-range/   |   Difficulty: Hard
//
// Problem Description:
// Given two positive integers low and high represented as strings, find the count of stepping numbers in the inclusive range [low, high].
//
// A stepping number is an integer such that all of its adjacent digits have an absolute difference of exactly 1.
//
// Return an integer denoting the count of stepping numbers in the inclusive range [low, high]. 
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Note: A stepping number should not have a leading zero.
//
// Example:
// Input: low = "1", high = "11"
// Output: 10
// Explanation: The stepping numbers in the range [1,11] are 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10. There are a total of 10 stepping numbers in the range. Hence, the output is 10.
//
// Constraints:
// 1 <= int(low) <= int(high) < 10100
// 	1 <= low.length, high.length <= 100
// 	low and high consist of only digits.
// 	low and high don't have any leading zeros.
//

class Solution {
public:
    int countSteppingNumbers(string low, string high) {
        const int MOD = 1e9 + 7;
        int n = high.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(10, vector<int>(2, 0)));
        
        // Initialize for length 1
        for (int d = 1; d <= 9; d++) {
            dp[1][d][d < (high[0] - '0' ? 1 : 0)] = 1;
        }
        
        // Fill DP table
        for (int len = 2; len <= n; len++) {
            for (int d = 0; d <= 9; d++) {
                for (int smaller = 0; smaller <= 1; smaller++) {
                    int limit = smaller ? 9 : (high[len - 1] - '0');
                    for (int nd = max(0, d - 1); nd <= min(9, d + 1); nd += 2) {
                        if (nd <= limit) {
                            dp[len][nd][smaller || (nd < limit)] = (dp[len][nd][smaller || (nd < limit)] + dp[len - 1][d][smaller]) % MOD;
                        }
                    }
                }
            }
        }
        
        // Count valid numbers
        int result = 0;
        for (int d = 0; d <= 9; d++) {
            result = (result + dp[n][d][1]) % MOD;
            if (d <= (high[0] - '0')) {
                result = (result + dp[n][d][0]) % MOD;
            }
        }
        
        // Subtract numbers less than low
        n = low.size();
        vector<vector<vector<int>>> dpLow(n + 1, vector<vector<int>>(10, vector<int>(2, 0)));
        
        // Initialize for length 1
        for (int d = 1; d <= 9; d++) {
            dpLow[1][d][d < (low[0] - '0' ? 1 : 0)] = 1;
        }
        
        // Fill DP table for low
        for (int len = 2; len <= n; len++) {
            for (int d = 0; d <= 9; d++) {
                for (int smaller = 0; smaller <= 1; smaller++) {
                    int limit = smaller ? 9 : (low[len - 1] - '0');
                    for (int nd = max(0, d - 1); nd <= min(9, d + 1); nd += 2) {
                        if (nd <= limit) {
                            dpLow[len][nd][smaller || (nd < limit)] = (dpLow[len][nd][smaller || (nd < limit)] + dpLow[len - 1][d][smaller]) % MOD;
                        }
                    }
                }
            }
        }
        
        // Count valid numbers for low
        int resultLow = 0;
        for (int d = 0; d <= 9; d++) {
            resultLow = (resultLow + dpLow[n][d][1]) % MOD;
            if (d <= (low[0] - '0')) {
                resultLow = (resultLow + dpLow[n][d][0]) % MOD;
            }
        }
        
        return (result - resultLow + MOD) % MOD;
    }
};
