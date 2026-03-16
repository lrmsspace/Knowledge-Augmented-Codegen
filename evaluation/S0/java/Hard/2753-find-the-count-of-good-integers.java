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
    public long countGoodIntegers(int n, int k) {
        long[][] dp = new long[n + 1][k];
        for (int d = 1; d <= 9; d++) {
            if (n == 1) {
                if (d % k == 0) {
                    dp[1][0]++;
                }
            } else {
                dp[2][(d * 2) % k]++;
            }
        }

        for (int len = 3; len <= n; len++) {
            for (int mod = 0; mod < k; mod++) {
                for (int d = 0; d <= 9; d++) {
                    int newMod = (mod + (len % 2 == 0 ? d * 2 : d)) % k;
                    dp[len][newMod] += dp[len - 1][mod];
                }
            }
        }

        return dp[n][0];            
    }
}
