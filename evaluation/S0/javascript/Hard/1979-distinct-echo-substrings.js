// Source: https://leetcode.com/problems/distinct-echo-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Return the number of distinct non-empty substrings of text that can be written as the concatenation of some string with itself (i.e. it can be written as a + a where a is some string).
//
// Example:
// Input: text = "abcabcabc"
// Output: 3
// Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".
//
// Constraints:
// 1 <= text.length <= 2000
// 	text has only lowercase English letters.
//

/**
 * @param {string} text
 * @return {number}
 */
var distinctEchoSubstrings = function(text) {
    const n = text.length;
    const seen = new Set();
    for (let length = 1; length <= Math.floor(n / 2); length++) {
        for (let i = 0; i <= n - 2 * length; i++) {
            const a = text.substring(i, i + length);
            const b = text.substring(i + length, i + 2 * length);
            if (a === b) {
                seen.add(a + b);
            }
        }
    }
    return seen.size;   
};
