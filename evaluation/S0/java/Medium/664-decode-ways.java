// Source: https://leetcode.com/problems/decode-ways/   |   Difficulty: Medium
//
// Problem Description:
// You have intercepted a secret message encoded as a string of numbers. The message is decoded via the following mapping:
//
// "1" -> 'A'
// "2" -> 'B'
// ...
// "25" -> 'Y'
// "26" -> 'Z'
//
// However, while decoding the message, you realize that there are many different ways you can decode the message because some codes are contained in other codes ("2" and "5" vs "25").
//
// For example, "11106" can be decoded into:
//
//
// 	"AAJF" with the grouping (1, 1, 10, 6)
// 	"KJF" with the grouping (11, 10, 6)
// 	The grouping (1, 11, 06) is invalid because "06" is not a valid code (only "6" is valid).
//
//
// Note: there may be strings that are impossible to decode.
//
// Given a string s containing only digits, return the number of ways to decode it. If the entire string cannot be decoded in any valid way, return 0.
//
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: s = "12"
//
// Output: 2
//
// Explanation:
//
// "12" could be decoded as "AB" (1 2) or "L" (12).
//
// Constraints:
// 1 <= s.length <= 100
// 	s contains only digits and may contain leading zero(s).
//

class Solution {
    public int numDecodings(String s) {
        if (s == null || s.length() == 0 || s.charAt(0) == '0') {
            return 0;
        }

        int n = s.length();
        int[] dp = new int[n + 1];
        dp[0] = 1; // Base case: empty string
        dp[1] = 1; // Base case: first character is guaranteed to be non-zero here

        for (int i = 2; i <= n; i++) {
            char currentChar = s.charAt(i - 1);
            char previousChar = s.charAt(i - 2);

            // Check for single digit decode
            if (currentChar != '0') {
                dp[i] += dp[i - 1];
            }

            // Check for two digit decode
            int twoDigit = (previousChar - '0') * 10 + (currentChar - '0');
            if (twoDigit >= 10 && twoDigit <= 26) {
                dp[i] += dp[i - 2];
            }
        }

        return dp[n];           
    }
}
