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

/**
 * @param {string} s
 * @param {number} t
 * @return {number}
 */
var lengthAfterTransformations = function(s, t) {
    const mod = 1e9 + 7;
    const dp = Array.from({ length: t + 1 }, () => Array(26).fill(0));
    for (let i = 0; i < s.length; i++) {
        dp[0][s.charCodeAt(i) - 97]++;
    }
    for (let i = 1; i <= t; i++) {
        for (let j = 0; j < 26; j++) {
            if (j === 25) {
                dp[i][0] = (dp[i][0] + dp[i - 1][j]) % mod;
                dp[i][1] = (dp[i][1] + dp[i - 1][j]) % mod;
            } else {
                dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j]) % mod;
            }
        }
    }
    let result = 0;
    for (let j = 0; j < 26; j++) {
        result = (result + dp[t][j]) % mod;
    }
    return result;
};
