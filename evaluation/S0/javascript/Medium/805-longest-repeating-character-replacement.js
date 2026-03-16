// Source: https://leetcode.com/problems/longest-repeating-character-replacement/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
//
// Return the length of the longest substring containing the same letter you can get after performing the above operations.
//
// Example:
// Input: s = "ABAB", k = 2
// Output: 4
// Explanation: Replace the two 'A's with two 'B's or vice versa.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only uppercase English letters.
// 	0 <= k <= s.length
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var characterReplacement = function(s, k) {
    const count = new Array(26).fill(0);
    let maxCount = 0;
    let left = 0;
    let result = 0;
    for (let right = 0; right < s.length; right++) {
        count[s.charCodeAt(right) - 65]++;
        maxCount = Math.max(maxCount, count[s.charCodeAt(right) - 65]);
        while (right - left + 1 - maxCount > k) {
            count[s.charCodeAt(left) - 65]--;
            left++;
        }
        result = Math.max(result, right - left + 1);
    }
    return result;
};