// Source: https://leetcode.com/problems/select-k-disjoint-special-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s of length n and an integer k, determine whether it is possible to select k disjoint special substrings.
//
// A special substring is a substring where:
//
//
// 	Any character present inside the substring should not appear outside it in the string.
// 	The substring is not the entire string s.
//
//
// Note that all k substrings must be disjoint, meaning they cannot overlap.
//
// Return true if it is possible to select k such disjoint special substrings; otherwise, return false.
//
// Example:
// Input: s = "abcdbaefab", k = 2
//
// Output: true
//
// Explanation:
//
//
// 	We can select two disjoint special substrings: "cd" and "ef".
// 	"cd" contains the characters 'c' and 'd', which do not appear elsewhere in s.
// 	"ef" contains the characters 'e' and 'f', which do not appear elsewhere in s.
//
// Constraints:
// 2 <= n == s.length <= 5 * 104
// 	0 <= k <= 26
// 	s consists only of lowercase English letters.
//

/**
 * @param {string} s
 * @param {number} k
 * @return {boolean}
 */
var maxSubstringLength = function(s, k) {
    const charCount = new Map();
    for (const char of s) {
        charCount.set(char, (charCount.get(char) || 0) + 1);
    }
    let specialCount = 0;
    for (const count of charCount.values()) {
        if (count === 1) {
            specialCount++;
        }
    }
    return specialCount >= k;   
};
