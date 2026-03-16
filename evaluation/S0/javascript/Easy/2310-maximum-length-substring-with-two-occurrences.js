// Source: https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the maximum length of a substring such that it contains at most two occurrences of each character.
//
// Example:
// Input: s = "bcbbbcba"
//
// Output: 4
//
// Explanation:
// The following substring has a length of 4 and contains at most two occurrences of each character: "bcbbbcba".
//
// Constraints:
// 2 <= s.length <= 100
// 	s consists only of lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var maximumLengthSubstring = function(s) {
    const n = s.length;
    let maxLength = 0;
    for (let i = 0; i < n; i++) {
        const charCount = new Map();    
        for (let j = i; j < n; j++) {
            const char = s[j];
            charCount.set(char, (charCount.get(char) || 0) + 1);
            if (charCount.get(char) > 2) {
                break;
            }
            const currentLength = j - i + 1;
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
        }
    }
    return maxLength;
};
