// Source: https://leetcode.com/problems/count-substrings-with-k-frequency-characters-i/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return the total number of substrings of s where at least one character appears at least k times.
//
// Example:
// Input: s = "abacb", k = 2
//
// Output: 4
//
// Explanation:
//
// The valid substrings are:
//
//
// 	"aba" (character 'a' appears 2 times).
// 	"abac" (character 'a' appears 2 times).
// 	"abacb" (character 'a' appears 2 times).
// 	"bacb" (character 'b' appears 2 times).
//
// Constraints:
// 1 <= s.length <= 3000
// 	1 <= k <= s.length
// 	s consists only of lowercase English letters.
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var numberOfSubstrings = function(s, k) {
    let count = 0;
    for (let i = 0; i < s.length; i++) {
        const charCount = {};
        for (let j = i; j < s.length; j++) {
            const char = s[j];
            charCount[char] = (charCount[char] || 0) + 1;
            if (charCount[char] >= k) {
                count++;
            }
        }
    }    return count;  
};
