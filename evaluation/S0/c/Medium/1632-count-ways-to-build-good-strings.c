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

int countGoodStrings(int low, int high, int zero, int one) {
    const int MOD = 1e9 + 7;
    int dp[high + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1; // Base case: one way to create an empty string

    for (int length = 1; length <= high; length++) {
        if (length - zero >= 0) {
            dp[length] = (dp[length] + dp[length - zero]) % MOD;
        }
        if (length - one >= 0) {
            dp[length] = (dp[length] + dp[length - one]) % MOD;
        }
    }

    int result = 0;
    for (int length = low; length <= high; length++) {
        result = (result + dp[length]) % MOD;
    }

    return result;      
}
