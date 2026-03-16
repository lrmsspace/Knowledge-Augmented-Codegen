// Source: https://leetcode.com/problems/restore-the-array/   |   Difficulty: Hard
//
// Problem Description:
// A program was supposed to print an array of integers. The program forgot to print whitespaces and the array is printed as a string of digits s and all we know is that all integers in the array were in the range [1, k] and there are no leading zeros in the array.
//
// Given the string s and the integer k, return the number of the possible arrays that can be printed as s using the mentioned program. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "1000", k = 10000
// Output: 1
// Explanation: The only possible array is [1000]
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only digits and does not contain leading zeros.
// 	1 <= k <= 109
//

class Solution {
    public int numberOfArrays(String s, int k) {
        int n = s.length();
        int mod = 1_000_000_007;
        int[] dp = new int[n + 1];
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (s.charAt(j) == '0') {
                    continue; // Skip leading zeros
                }
                String numStr = s.substring(j, i);
                long num = Long.parseLong(numStr);
                if (num > k) {
                    break; // No need to check further as numbers will only get larger
                }
                dp[i] = (dp[i] + dp[j]) % mod;
            }
        }

        return dp[n];                   
    }
}
