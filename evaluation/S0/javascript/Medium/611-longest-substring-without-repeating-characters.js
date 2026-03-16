// Source: https://leetcode.com/problems/longest-substring-without-repeating-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find the length of the longest substring without duplicate characters.
//
// Example:
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
//
// Constraints:
// 0 <= s.length <= 5 * 104
// 	s consists of English letters, digits, symbols and spaces.
//

/**
 * @param {string} s
 * @return {number}
 */
var lengthOfLongestSubstring = function(s) {
    let charIndexMap = new Map();
    let left = 0;
    let maxLength = 0;

    for (let right = 0; right < s.length; right++) {
        let currentChar = s[right];

        if (charIndexMap.has(currentChar) && charIndexMap.get(currentChar) >= left) {
            left = charIndexMap.get(currentChar) + 1;
        }

        charIndexMap.set(currentChar, right);
        maxLength = Math.max(maxLength, right - left + 1);
    }

    return maxLength;   
};
