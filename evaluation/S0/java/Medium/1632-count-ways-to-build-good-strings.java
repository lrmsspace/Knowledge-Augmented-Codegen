// Source: https://leetcode.com/problems/count-ways-to-build-good-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given the integers zero, one, low, and high, we can construct a string by starting with an empty string, and then at each step perform either of the following:
//
//
// 	Append the character '0' zero times.
// 	Append the character '1' one times.
//
//
// This can be performed any number of times.
//
// A good string is a string constructed by the above process having a length between low and high (inclusive).
//
// Return the number of different good strings that can be constructed satisfying these properties. Since the answer can be large, return it modulo 109 + 7.
//
// Example:
// Input: low = 3, high = 3, zero = 1, one = 1
// Output: 8
// Explanation: 
// One possible valid good string is "011". 
// It can be constructed as follows: "" -> "0" -> "01" -> "011". 
// All binary strings from "000" to "111" are good strings in this example.
//
// Constraints:
// 1 <= low <= high <= 105
// 	1 <= zero, one <= low
//

class Solution {
    public int countGoodStrings(int low, int high, int zero, int one) {
        int mod = 1_000_000_007;
        int[] dp = new int[high + 1];
        dp[0] = 1; // base case: one way to make an empty string

        for (int length = 1; length <= high; length++) {
            if (length - zero >= 0) {
                dp[length] = (dp[length] + dp[length - zero]) % mod;
            }
            if (length - one >= 0) {
                dp[length] = (dp[length] + dp[length - one]) % mod;
            }
        }

        int result = 0;
        for (int length = low; length <= high; length++) {
            result = (result + dp[length]) % mod;
        }

        return result;          
    }
}
