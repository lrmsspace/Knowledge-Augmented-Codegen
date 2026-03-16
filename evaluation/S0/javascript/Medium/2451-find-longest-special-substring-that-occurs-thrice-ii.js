// Source: https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s that consists of lowercase English letters.
//
// A string is called special if it is made up of only a single character. For example, the string "abc" is not special, whereas the strings "ddd", "zz", and "f" are special.
//
// Return the length of the longest special substring of s which occurs at least thrice, or -1 if no special substring occurs at least thrice.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "aaaa"
// Output: 2
// Explanation: The longest special substring which occurs thrice is "aa": substrings "aaaa", "aaaa", and "aaaa".
// It can be shown that the maximum length achievable is 2.
//
// Constraints:
// 3 <= s.length <= 5 * 105
// 	s consists of only lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var maximumLength = function(s) {
    const n = s.length;
    let maxLength = -1;
    let count = 1;
    for (let i = 1; i < n; i++) {
        if (s[i] === s[i - 1]) {
            count++;
        } else {
            if (count >= 3) {
                maxLength = Math.max(maxLength, count);
            }
            count = 1;
        }
    }
    if (count >= 3) {
        maxLength = Math.max(maxLength, count);
    }
    return maxLength;   
};
