// Source: https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t, transform string s into string t using the following operation any number of times:
//
//
// 	Choose a non-empty substring in s and sort it in place so the characters are in ascending order.
//
// 	
// 		For example, applying the operation on the underlined substring in "14234" results in "12344".
// 	
// 	
//
//
// Return true if it is possible to transform s into t. Otherwise, return false.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "84532", t = "34852"
// Output: true
// Explanation: You can transform s into t using the following sort operations:
// "84532" (from index 2 to 3) -> "84352"
// "84352" (from index 0 to 2) -> "34852"
//
// Constraints:
// s.length == t.length
// 	1 <= s.length <= 105
// 	s and t consist of only digits.
//

/**
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
var isTransformable = function(s, t) {
    const charIndices = new Array(10).fill(0).map(() => []);
    for (let i = 0; i < s.length; i++) {
        charIndices[s.charCodeAt(i) - '0'.charCodeAt(0)].push(i);
    }
    const pointers = new Array(10).fill(0);
    for (let i = 0; i < t.length; i++) {
        const digit = t.charCodeAt(i) - '0'.charCodeAt(0);
        if (pointers[digit] >= charIndices[digit].length) return false;
        const pos = charIndices[digit][pointers[digit]];
        for (let smallerDigit = 0; smallerDigit < digit; smallerDigit++) {
            if (pointers[smallerDigit] < charIndices[smallerDigit].length && charIndices[smallerDigit][pointers[smallerDigit]] < pos) {
                return false;
            }
        }
        pointers[digit]++;
    }
    return true;
};
