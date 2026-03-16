// Source: https://leetcode.com/problems/find-the-count-of-good-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers n and k.
//
// An integer x is called k-palindromic if:
//
//
// 	x is a palindrome.
// 	x is divisible by k.
//
//
// An integer is called good if its digits can be rearranged to form a k-palindromic integer. For example, for k = 2, 2020 can be rearranged to form the k-palindromic integer 2002, whereas 1010 cannot be rearranged to form a k-palindromic integer.
//
// Return the count of good integers containing n digits.
//
// Note that any integer must not have leading zeros, neither before nor after rearrangement. For example, 1010 cannot be rearranged to form 101.
//
// Example:
// Input: n = 3, k = 5
//
// Output: 27
//
// Explanation:
//
// Some of the good integers are:
//
//
// 	551 because it can be rearranged to form 515.
// 	525 because it is already k-palindromic.
//
// Constraints:
// 1 <= n <= 10
// 	1 <= k <= 9
//

class Solution {
public:
    long long countGoodIntegers(int n, int k) {
        const int MOD = 1e9 + 7;
        long long dp[11][10][2]; // dp[length][mod k][has odd count]
        memset(dp, 0, sizeof(dp));
        
        // Initialize for length 1
        for (int digit = 1; digit <= 9; digit++) {
            int mod = digit % k;
            dp[1][mod][1]++; // single digit has odd count
        }
        
        for (int length = 1; length < n; length++) {
            for (int mod = 0; mod < k; mod++) {
                for (int odd = 0; odd <= 1; odd++) {
                    for (int digit = 0; digit <= 9; digit++) {
                        int newMod = (mod * 10 + digit) % k;
                        int newOdd = odd ^ 1; // toggle odd/even count
                        dp[length + 1][newMod][newOdd] = (dp[length + 1][newMod][newOdd] + dp[length][mod][odd]) % MOD;
                    }
                }
            }
        }
        
        return dp[n][0][0]; // length n, mod k == 0, all counts even            
    }
};
