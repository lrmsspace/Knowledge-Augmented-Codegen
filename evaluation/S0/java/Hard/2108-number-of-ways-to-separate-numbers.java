// Source: https://leetcode.com/problems/number-of-ways-to-separate-numbers/   |   Difficulty: Hard
//
// Problem Description:
// You wrote down many positive integers in a string called num. However, you realized that you forgot to add commas to seperate the different numbers. You remember that the list of integers was non-decreasing and that no integer had leading zeros.
//
// Return the number of possible lists of integers that you could have written down to get the string num. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: num = "327"
// Output: 2
// Explanation: You could have written down the numbers:
// 3, 27
// 327
//
// Constraints:
// 1 <= num.length <= 3500
//  num consists of digits '0' through '9'.
//

class Solution {
    public int numberOfCombinations(String num) {
        int mod = 1_000_000_007;
        int n = num.length();
        int[][] lcp = new int[n + 1][n + 1];
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (num.charAt(i) == num.charAt(j)) {
                    lcp[i][j] = lcp[i + 1][j + 1] + 1;
                }
            }
        }

        int[] dp = new int[n + 1];
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            if (num.charAt(i - 1) == '0') continue;
            for (int length = 1; length <= i; length++) {
                int j = i - length;
                if (j == 0) {
                    dp[i] = (dp[i] + dp[j]) % mod;
                } else {
                    int k = j - length;
                    if (k < 0) {
                        dp[i] = (dp[i] + dp[j]) % mod;
                    } else {
                        int common = lcp[k][j];
                        if (common >= length || num.charAt(k + common) <= num.charAt(j + common)) {
                            dp[i] = (dp[i] + dp[j]) % mod;
                        }
                    }
                }
            }
        }
        return dp[n];           
    }
}
