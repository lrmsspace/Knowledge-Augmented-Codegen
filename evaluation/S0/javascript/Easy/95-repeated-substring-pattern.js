// Source: https://leetcode.com/problems/repeated-substring-pattern/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.
//
// Example:
// Input: s = "abab"
// Output: true
// Explanation: It is the substring "ab" twice.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @return {boolean}
 */
var repeatedSubstringPattern = function(s) {
    const n = s.length;
    for (let len = 1; len <= Math.floor(n / 2); len++) {
        if (n % len === 0) {
            const substring = s.slice(0, len);
            let repeated = '';
            for (let i = 0; i < n / len; i++) {
                repeated += substring;
            }
            if (repeated === s) {
                return true;
            }
        }
    }
    return false;   
};
