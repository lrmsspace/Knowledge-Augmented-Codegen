// Source: https://leetcode.com/problems/get-equal-substrings-within-budget/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t of the same length and an integer maxCost.
//
// You want to change s to t. Changing the ith character of s to ith character of t costs |s[i] - t[i]| (i.e., the absolute difference between the ASCII values of the characters).
//
// Return the maximum length of a substring of s that can be changed to be the same as the corresponding substring of t with a cost less than or equal to maxCost. If there is no substring from s that can be changed to its corresponding substring from t, return 0.
//
// Example:
// Input: s = "abcd", t = "bcdf", maxCost = 3
// Output: 3
// Explanation: "abc" of s can change to "bcd".
// That costs 3, so the maximum length is 3.
//
// Constraints:
// 1 <= s.length <= 105
// 	t.length == s.length
// 	0 <= maxCost <= 106
// 	s and t consist of only lowercase English letters.
//

/**
 * @param {string} s
 * @param {string} t
 * @param {number} maxCost
 * @return {number}
 */
var equalSubstring = function(s, t, maxCost) {
    let left = 0;
    let currentCost = 0;
    let maxLength = 0;
    for (let right = 0; right < s.length; right++) {
        currentCost += Math.abs(s.charCodeAt(right) - t.charCodeAt(right));
        while (currentCost > maxCost) {
            currentCost -= Math.abs(s.charCodeAt(left) - t.charCodeAt(left));
            left++;
        }
        maxLength = Math.max(maxLength, right - left + 1);
    }
    return maxLength;
        
};
