// Source: https://leetcode.com/problems/largest-substring-between-two-equal-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. If there is no such substring return -1.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "aa"
// Output: 0
// Explanation: The optimal substring here is an empty substring between the two 'a's.
//
// Constraints:
// 1 <= s.length <= 300
// 	s contains only lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var maxLengthBetweenEqualCharacters = function(s) {
    const charIndexMap = {};
    let maxLength = -1;
    for (let i = 0; i < s.length; i++) {
        const char = s[i];
        if (char in charIndexMap) {
            const length = i - charIndexMap[char] - 1;
            if (length > maxLength) {
                maxLength = length;
            }
        } else {
            charIndexMap[char] = i;
        }
    }
    return maxLength;
};