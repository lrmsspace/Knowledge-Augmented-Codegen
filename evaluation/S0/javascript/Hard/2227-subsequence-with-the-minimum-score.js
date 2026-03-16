// Source: https://leetcode.com/problems/subsequence-with-the-minimum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and t.
//
// You are allowed to remove any number of characters from the string t.
//
// The score of the string is 0 if no characters are removed from the string t, otherwise:
//
//
// 	Let left be the minimum index among all removed characters.
// 	Let right be the maximum index among all removed characters.
//
//
// Then the score of the string is right - left + 1.
//
// Return the minimum possible score to make t a subsequence of s.
//
// A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
//
// Example:
// Input: s = "abacaba", t = "bzaa"
// Output: 1
// Explanation: In this example, we remove the character "z" at index 1 (0-indexed).
// The string t becomes "baa" which is a subsequence of the string "abacaba" and the score is 1 - 1 + 1 = 1.
// It can be proven that 1 is the minimum score that we can achieve.
//
// Constraints:
// 1 <= s.length, t.length <= 105
// 	s and t consist of only lowercase English letters.
//

/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
var minimumScore = function(s, t) {
    const n = s.length;
    const m = t.length;
    const left = new Array(m).fill(-1);
    const right = new Array(m).fill(-1);
    let j = 0;  

    for (let i = 0; i < n && j < m; i++) {
        if (s[i] === t[j]) {
            left[j] = i;
            j++;
        }
    }

    j = m - 1;
    for (let i = n - 1; i >= 0 && j >= 0; i--) {
        if (s[i] === t[j]) {
            right[j] = i;
            j--;
        }
    }

    let minScore = m;
    for (let i = 0; i < m; i++) {
        if (left[i] === -1) {
            minScore = Math.min(minScore, m - i);
        } else if (right[i] === -1) {
            minScore = Math.min(minScore, i + 1);
        } else {
            minScore = Math.min(minScore, right[i] - left[i] + 1);
        }
    }
    return minScore;
};
