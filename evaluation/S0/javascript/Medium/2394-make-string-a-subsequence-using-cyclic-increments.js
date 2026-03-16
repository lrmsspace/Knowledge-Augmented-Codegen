// Source: https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed strings str1 and str2.
//
// In an operation, you select a set of indices in str1, and for each index i in the set, increment str1[i] to the next character cyclically. That is 'a' becomes 'b', 'b' becomes 'c', and so on, and 'z' becomes 'a'.
//
// Return true if it is possible to make str2 a subsequence of str1 by performing the operation at most once, and false otherwise.
//
// Note: A subsequence of a string is a new string that is formed from the original string by deleting some (possibly none) of the characters without disturbing the relative positions of the remaining characters.
//
// Example:
// Input: str1 = "abc", str2 = "ad"
// Output: true
// Explanation: Select index 2 in str1.
// Increment str1[2] to become 'd'. 
// Hence, str1 becomes "abd" and str2 is now a subsequence. Therefore, true is returned.
//
// Constraints:
// 1 <= str1.length <= 105
// 	1 <= str2.length <= 105
// 	str1 and str2 consist of only lowercase English letters.
//

/**
 * @param {string} str1
 * @param {string} str2
 * @return {boolean}
 */
var canMakeSubsequence = function(str1, str2) {
    const n = str1.length;
    const m = str2.length;
    const nextChar = (c) => String.fromCharCode(((c.charCodeAt(0) - 97 + 1) % 26) + 97);
    let i = 0; 
    let j = 0; 
    let incrementUsed = false;
    while (i < n && j < m) {
        if (str1[i] === str2[j]) {
            i++;
            j++;
        } else if (!incrementUsed && nextChar(str1[i]) === str2[j]) {
            incrementUsed = true;
            i++;
            j++;
        } else {
            i++;
        }
    }
    return j === m;
};