// Source: https://leetcode.com/problems/repeated-string-match/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings a and b, return the minimum number of times you should repeat string a so that string b is a substring of it. If it is impossible for b​​​​​​ to be a substring of a after repeating it, return -1.
//
// Notice: string "abc" repeated 0 times is "", repeated 1 time is "abc" and repeated 2 times is "abcabc".
//
// Example:
// Input: a = "abcd", b = "cdabcdab"
// Output: 3
// Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.
//
// Constraints:
// 1 <= a.length, b.length <= 104
// 	a and b consist of lowercase English letters.
//

/**
 * @param {string} a
 * @param {string} b
 * @return {number}
 */
var repeatedStringMatch = function(a, b) {
    const repeatCount = Math.ceil(b.length / a.length);
    let repeatedA = a.repeat(repeatCount);
    if (repeatedA.includes(b)) {
        return repeatCount;
    }
    repeatedA += a;
    if (repeatedA.includes(b)) {
        return repeatCount + 1;
    }
    return -1;
};