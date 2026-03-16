// Source: https://leetcode.com/problems/total-characters-in-string-after-transformations-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer t, representing the number of transformations to perform. In one transformation, every character in s is replaced according to the following rules:
//
//
// 	If the character is 'z', replace it with the string "ab".
// 	Otherwise, replace it with the next character in the alphabet. For example, 'a' is replaced with 'b', 'b' is replaced with 'c', and so on.
//
//
// Return the length of the resulting string after exactly t transformations.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "abcyy", t = 2
//
// Output: 7
//
// Explanation:
//
//
// 	First Transformation (t = 1):
//
// 	
// 		'a' becomes 'b'
// 		'b' becomes 'c'
// 		'c' becomes 'd'
// 		'y' becomes 'z'
// 		'y' becomes 'z'
// 		String after the first transformation: "bcdzz"
// 	
// 	
// 	Second Transformation (t = 2):
// 	
// 		'b' becomes 'c'
// 		'c' becomes 'd'
// 		'd' becomes 'e'
// 		'z' becomes "ab"
// 		'z' becomes "ab"
// 		String after the second transformation: "cdeabab"
// 	
// 	
// 	Final Length of the string: The string is "cdeabab", which has 7 characters.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
// 	1 <= t <= 105
//

class Solution {
    public int lengthAfterTransformations(String s, int t) {
        int MOD = 1_000_000_007;
        int[] dp = new int[t + 1];
        dp[0] = 1;

        for (int i = 1; i <= t; i++) {
            dp[i] = (2 * dp[i - 1]) % MOD;
            if (i >= 26) {
                dp[i] = (dp[i] - dp[i - 26] + MOD) % MOD;
            }
        }

        long result = 0;
        for (char c : s.toCharArray()) {
            int index = t;
            if (c != 'z') {
                index -= (25 - (c - 'a'));
                if (index < 0) {
                    index = 0;
                }
            }
            result = (result + dp[index]) % MOD;
        }

        return (int) result;            
    }
}
