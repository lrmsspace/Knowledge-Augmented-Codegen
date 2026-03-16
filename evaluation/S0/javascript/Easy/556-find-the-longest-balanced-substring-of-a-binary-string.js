// Source: https://leetcode.com/problems/find-the-longest-balanced-substring-of-a-binary-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a binary string s consisting only of zeroes and ones.
//
// A substring of s is considered balanced if all zeroes are before ones and the number of zeroes is equal to the number of ones inside the substring. Notice that the empty substring is considered a balanced substring.
//
// Return the length of the longest balanced substring of s.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "01000111"
// Output: 6
// Explanation: The longest balanced substring is "000111", which has length 6.
//
// Constraints:
// 1 <= s.length <= 50
// 	'0' <= s[i] <= '1'
//

/**
 * @param {string} s
 * @return {number}
 */
var findTheLongestBalancedSubstring = function(s) {
    let maxLength = 0;
    let i = 0;
    const n = s.length;
    while (i < n) {
        let count0 = 0;
        let count1 = 0;
        while (i < n && s[i] === '0') {
            count0++;
            i++;
        }
        while (i < n && s[i] === '1') {
            count1++;
            i++;
        }
        const balancedLength = 2 * Math.min(count0, count1);
        maxLength = Math.max(maxLength, balancedLength);
    }
    return maxLength;
    };
