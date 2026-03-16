// Source: https://leetcode.com/problems/count-numbers-with-non-decreasing-digits/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers, l and r, represented as strings, and an integer b. Return the count of integers in the inclusive range [l, r] whose digits are in non-decreasing order when represented in base b.
//
// An integer is considered to have non-decreasing digits if, when read from left to right (from the most significant digit to the least significant digit), each digit is greater than or equal to the previous one.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: l = "23", r = "28", b = 8
//
// Output: 3
//
// Explanation:
//
//
// 	The numbers from 23 to 28 in base 8 are: 27, 30, 31, 32, 33, and 34.
// 	Out of these, 27, 33, and 34 have non-decreasing digits. Hence, the output is 3.
//
// Constraints:
// 1 <= l.length <= r.length <= 100
// 	2 <= b <= 10
// 	l and r consist only of digits.
// 	The value represented by l is less than or equal to the value represented by r.
// 	l and r do not contain leading zeros.
//

class Solution {
public:
    int countNumbers(string l, string r, int b) {
        const int MOD = 1e9 + 7;
        int n = r.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(b, vector<int>(2, 0)));
        
        // Count numbers <= r
        dp[0][0][1] = 1;
        for (int i = 0; i < n; ++i) {
            int limit = r[i] - '0';
            for (int d = 0; d < b; ++d) {
                for (int tight = 0; tight <= 1; ++tight) {
                    int up = tight ? limit : b - 1;
                    for (int nd = d; nd <= up; ++nd) {
                        int ntight = (tight && nd == limit) ? 1 : 0;
                        dp[i + 1][nd][ntight] = (dp[i + 1][nd][ntight] + dp[i][d][tight]) % MOD;
                    }
                }
            }
        }
        
        int countR = 0;
        for (int d = 0; d < b; ++d) {
            for (int tight = 0; tight <= 1; ++tight) {
                countR = (countR + dp[n][d][tight]) % MOD;
            }
        }
        
        // Reset dp for counting numbers < l
        dp.assign(n + 1, vector<vector<int>>(b, vector<int>(2, 0)));
        
        // Count numbers < l
        dp[0][0][1] = 1;
        for (int i = 0; i < n; ++i) {
            int limit = l[i] - '0';
            for (int d = 0; d < b; ++d) {
                for (int tight = 0; tight <= 1; ++tight) {
                    int up = tight ? limit - 1 : b - 1;
                    for (int nd = d; nd <= up; ++nd) {
                        int ntight = (tight && nd == limit - 1) ? 1 : 0;
                        dp[i + 1][nd][ntight] = (dp[i + 1][nd][ntight] + dp[i][d][tight]) % MOD;
                    }
                }           
                
            }
        }
        
        int countL = 0;
        for (int d = 0; d < b; ++d) {
            for (int tight = 0; tight <= 1; ++tight) {
                countL = (countL + dp[n][d][tight]) % MOD;
            }
        }
        
        return (countR - countL + MOD) % MOD;
    }
};
