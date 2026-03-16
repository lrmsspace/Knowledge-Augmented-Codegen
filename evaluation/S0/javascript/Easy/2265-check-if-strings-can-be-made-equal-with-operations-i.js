// Source: https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings s1 and s2, both of length 4, consisting of lowercase English letters.
//
// You can apply the following operation on any of the two strings any number of times:
//
//
// 	Choose any two indices i and j such that j - i = 2, then swap the two characters at those indices in the string.
//
//
// Return true if you can make the strings s1 and s2 equal, and false otherwise.
//
// Example:
// Input: s1 = "abcd", s2 = "cdab"
// Output: true
// Explanation: We can do the following operations on s1:
// - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbad".
// - Choose the indices i = 1, j = 3. The resulting string is s1 = "cdab" = s2.
//
// Constraints:
// s1.length == s2.length == 4
// 	s1 and s2 consist only of lowercase English letters.
//

/**
 * @param {string} s1
 * @param {string} s2
 * @return {boolean}
 */
var caneEqual = function(s1, s2) {
    const s1Even = [s1[0], s1[2]].sort().join('');
    const s1Odd = [s1[1], s1[3]].sort().join('');
    const s2Even = [s2[0], s2[2]].sort().join('');
    const s2Odd = [s2[1], s2[3]].sort().join('');
    return s1Even === s2Even && s1Odd === s2Odd;    
};
