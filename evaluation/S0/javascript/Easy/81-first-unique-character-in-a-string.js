// Source: https://leetcode.com/problems/first-unique-character-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.
//
// Example:
// Input: s = "leetcode"
//
// Output: 0
//
// Explanation:
//
// The character 'l' at index 0 is the first character that does not occur at any other index.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var firstUniqChar = function(s) {
    const charCount = new Array(26).fill(0);
    for (const char of s) {
        charCount[char.charCodeAt(0) - 97]++;
    }
    for (let i = 0; i < s.length; i++) {
        if (charCount[s.charCodeAt(i) - 97] === 1) {
            return i;
        }
    }
    return -1;
};