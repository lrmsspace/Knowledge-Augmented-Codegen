// Source: https://leetcode.com/problems/make-three-strings-equal/   |   Difficulty: Easy
//
// Problem Description:
// You are given three strings: s1, s2, and s3. In one operation you can choose one of these strings and delete its rightmost character. Note that you cannot completely empty a string.
//
// Return the minimum number of operations required to make the strings equal. If it is impossible to make them equal, return -1.
//
// Example:
// Input: s1 = "abc", s2 = "abb", s3 = "ab"
//
// Output: 2
//
// Explanation: Deleting the rightmost character from both s1 and s2 will result in three equal strings.
//
// Constraints:
// 1 <= s1.length, s2.length, s3.length <= 100
// 	s1, s2 and s3 consist only of lowercase English letters.
//

/**
 * @param {string} s1
 * @param {string} s2
 * @param {string} s3
 * @return {number}
 */
var findMinimumOperations = function(s1, s2, s3) {
    let ops = 0;
    while (s1 !== s2 || s2 !== s3) {
        const maxLength = Math.max(s1.length, s2.length, s3.length);
        if (s1.length === maxLength) {
            s1 = s1.slice(0, -1);
            ops++;
        }
        if (s2.length === maxLength) {
            s2 = s2.slice(0, -1);
            ops++;
        }
        if (s3.length === maxLength) {
            s3 = s3.slice(0, -1);
            ops++;
        }
    }
    return ops;
};