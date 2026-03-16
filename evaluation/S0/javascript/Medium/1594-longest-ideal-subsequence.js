// Source: https://leetcode.com/problems/longest-ideal-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s consisting of lowercase letters and an integer k. We call a string t ideal if the following conditions are satisfied:
//
//
// 	t is a subsequence of the string s.
// 	The absolute difference in the alphabet order of every two adjacent letters in t is less than or equal to k.
//
//
// Return the length of the longest ideal string.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Note that the alphabet order is not cyclic. For example, the absolute difference in the alphabet order of 'a' and 'z' is 25, not 1.
//
// Example:
// Input: s = "acfgbd", k = 2
// Output: 4
// Explanation: The longest ideal string is "acbd". The length of this string is 4, so 4 is returned.
// Note that "acfgbd" is not ideal because 'c' and 'f' have a difference of 3 in alphabet order.
//
// Constraints:
// 1 <= s.length <= 105
// 	0 <= k <= 25
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var longestIdealString = function(s, k) {
    const dp = new Array(26).fill(0);

    for (const char of s) {
        const index = char.charCodeAt(0) - 'a'.charCodeAt(0);
        let maxLength = 0;
        for (let j = Math.max(0, index - k); j <= Math.min(25, index + k); j++) {
            maxLength = Math.max(maxLength, dp[j]);
        }
        dp[index] = maxLength + 1;
    }   
    return Math.max(...dp);
};
