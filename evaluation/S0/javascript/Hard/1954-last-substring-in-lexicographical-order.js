// Source: https://leetcode.com/problems/last-substring-in-lexicographical-order/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, return the last substring of s in lexicographical order.
//
// Example:
// Input: s = "abab"
// Output: "bab"
// Explanation: The substrings are ["a", "ab", "aba", "abab", "b", "ba", "bab"]. The lexicographically maximum substring is "bab".
//
// Constraints:
// 1 <= s.length <= 4 * 105
// 	s contains only lowercase English letters.
//

/**
 * @param {string} s
 * @return {string}
 */
var lastSubstring = function(s) {
    const n = s.length;
    let i = 0, j = 1, k = 0;
    while (j + k < n) {
        if (s[i + k] === s[j + k]) {
            k++;
        } else if (s[i + k] > s[j + k]) {
            j = j + k + 1;
            k = 0;
        } else {
            i = Math.max(i + k + 1, j);
            j = i + 1;
            k = 0;
        }
    }
    return s.substring(i);
};
