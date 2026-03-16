// Source: https://leetcode.com/problems/license-key-formatting/   |   Difficulty: Easy
//
// Problem Description:
// You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.
//
// We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.
//
// Return the reformatted license key.
//
// Example:
// Input: s = "5F3Z-2e-9-w", k = 4
// Output: "5F3Z-2E9W"
// Explanation: The string s has been split into two parts, each part has 4 characters.
// Note that the two extra dashes are not needed and can be removed.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of English letters, digits, and dashes '-'.
// 	1 <= k <= 104
//

/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
var licenseKeyFormatting = function(s, k) {
    const cleaned = s.replace(/-/g, '').toUpperCase();
    let result = '';
    let firstGroupLength = cleaned.length % k || k;
    result += cleaned.slice(0, firstGroupLength);
    for (let i = firstGroupLength; i < cleaned.length; i += k) {
        result += '-' + cleaned.slice(i, i + k);
    }
    return result;
};
