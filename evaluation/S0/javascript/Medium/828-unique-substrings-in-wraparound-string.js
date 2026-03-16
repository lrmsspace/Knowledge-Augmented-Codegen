// Source: https://leetcode.com/problems/unique-substrings-in-wraparound-string/   |   Difficulty: Medium
//
// Problem Description:
// We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
//
//
// 	"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
//
//
// Given a string s, return the number of unique non-empty substrings of s are present in base.
//
// Example:
// Input: s = "a"
// Output: 1
// Explanation: Only the substring "a" of s is in base.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var findSubstringInWraproundString = function(s) {
    const dp = new Array(26).fill(0);
    let maxLength = 0;
    for (let i = 0; i < s.length; i++) {
        if (i > 0 && (s.charCodeAt(i) - s.charCodeAt(i - 1) + 26) % 26 === 1) {
            maxLength += 1;
        } else {
            maxLength = 1;
        }
        const index = s.charCodeAt(i) - 'a'.charCodeAt(0);
        dp[index] = Math.max(dp[index], maxLength);
    }
    return dp.reduce((a, b) => a + b, 0);
};
