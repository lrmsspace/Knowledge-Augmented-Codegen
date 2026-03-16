// Source: https://leetcode.com/problems/count-the-number-of-ideal-arrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers n and maxValue, which are used to describe an ideal array.
//
// A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:
//
//
// 	Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
// 	Every arr[i] is divisible by arr[i - 1], for 0 < i < n.
//
//
// Return the number of distinct ideal arrays of length n. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 2, maxValue = 5
// Output: 10
// Explanation: The following are the possible ideal arrays:
// - Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
// - Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
// - Arrays starting with the value 3 (1 array): [3,3]
// - Arrays starting with the value 4 (1 array): [4,4]
// - Arrays starting with the value 5 (1 array): [5,5]
// There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays.
//
// Constraints:
// 2 <= n <= 104
// 	1 <= maxValue <= 104
//

class Solution {
public:
    int idealArrays(int n, int maxValue) {
        const int MOD = 1e9 + 7;
        vector<long long> comb(n + 1, 0);
        comb[0] = 1;
        for (int i = 1; i <= n; i++) {
            comb[i] = comb[i - 1] * (n - i + 1) % MOD * modInverse(i, MOD) % MOD;
        }

        vector<int> dp(maxValue + 1, 0);
        for (int i = 1; i <= maxValue; i++) {
            dp[i] = 1;
        }

        long long result = 0;
        for (int length = 1; length <= n; length++) {
            long long currentCount = 0;
            for (int value = 1; value <= maxValue; value++) {
                currentCount = (currentCount + dp[value]) % MOD;
                for (int multiple = value * 2; multiple <= maxValue; multiple += value) {
                    dp[multiple] = (dp[multiple] + dp[value]) % MOD;
                }
            }
            result = (result + currentCount * comb[length - 1]) % MOD;
        }

        return (int)result;         
    }
};
