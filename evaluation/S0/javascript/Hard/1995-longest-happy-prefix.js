// Source: https://leetcode.com/problems/longest-happy-prefix/   |   Difficulty: Hard
//
// Problem Description:
// A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).
//
// Given a string s, return the longest happy prefix of s. Return an empty string "" if no such prefix exists.
//
// Example:
// Input: s = "level"
// Output: "l"
// Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//

/**
 * @param {string} s
 * @return {string}
 */
var longestPrefix = function(s) {
    const n = s.length;
    const prefixFunction = new Array(n).fill(0);
    for (let i = 1; i < n; i++) {
        let j = prefixFunction[i - 1];
        while (j > 0 && s[i] !== s[j]) {
            j = prefixFunction[j - 1];
        }
        if (s[i] === s[j]) {
            j++;
        }
        prefixFunction[i] = j;
    }
    return s.substring(0, prefixFunction[n - 1]);
};
