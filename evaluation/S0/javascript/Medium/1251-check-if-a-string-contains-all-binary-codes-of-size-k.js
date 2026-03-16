// Source: https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s and an integer k, return true if every binary code of length k is a substring of s. Otherwise, return false.
//
// Example:
// Input: s = "00110110", k = 2
// Output: true
// Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.
//
// Constraints:
// 1 <= s.length <= 5 * 105
// 	s[i] is either '0' or '1'.
// 	1 <= k <= 20
//

/**
 * @param {string} s
 * @param {number} k
 * @return {boolean}
 */
var hasAllCodes = function(s, k) {
    const needed = 1 << k; // Total number of binary codes of length k
    const found = new Set();
    for (let i = 0; i <= s.length - k; i++) {
        const substring = s.substring(i, i + k);
        found.add(substring);
        if (found.size === needed) {
            return true;
        }
    }
    return found.size === needed;   
                
};
