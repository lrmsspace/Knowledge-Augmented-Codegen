// Source: https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s1 and s2, both of length n, consisting of lowercase English letters.
//
// You can apply the following operation on any of the two strings any number of times:
//
//
// 	Choose any two indices i and j such that i < j and the difference j - i is even, then swap the two characters at those indices in the string.
//
//
// Return true if you can make the strings s1 and s2 equal, and false otherwise.
//
// Example:
// Input: s1 = "abcdba", s2 = "cabdab"
// Output: true
// Explanation: We can apply the following operations on s1:
// - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbadba".
// - Choose the indices i = 2, j = 4. The resulting string is s1 = "cbbdaa".
// - Choose the indices i = 1, j = 5. The resulting string is s1 = "cabdab" = s2.
//
// Constraints:
// n == s1.length == s2.length
// 	1 <= n <= 105
// 	s1 and s2 consist only of lowercase English letters.
//

/**
 * @param {string} s1
 * @param {string} s2
 * @return {boolean}
 */
var checkStrings = function(s1, s2) {
    const count1 = Array.from({ length: 26 }, () => [0, 0]);
    const count2 = Array.from({ length: 26 }, () => [0, 0]);
    const n = s1.length;
    for (let i = 0; i < n; i++) {
        count1[s1.charCodeAt(i) - 97][i % 2]++;
        count2[s2.charCodeAt(i) - 97][i % 2]++;
    }
    for (let i = 0; i < 26; i++) {
        if (count1[i][0] !== count2[i][0] || count1[i][1] !== count2[i][1]) {
            return false;
        }
    }
    return true;
};