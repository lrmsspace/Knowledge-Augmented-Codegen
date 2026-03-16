// Source: https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t. In one step, you can append any character to either s or t.
//
// Return the minimum number of steps to make s and t anagrams of each other.
//
// An anagram of a string is a string that contains the same characters with a different (or the same) ordering.
//
// Example:
// Input: s = "leetcode", t = "coats"
// Output: 7
// Explanation: 
// - In 2 steps, we can append the letters in "as" onto s = "leetcode", forming s = "leetcodeas".
// - In 5 steps, we can append the letters in "leede" onto t = "coats", forming t = "coatsleede".
// "leetcodeas" and "coatsleede" are now anagrams of each other.
// We used a total of 2 + 5 = 7 steps.
// It can be shown that there is no way to make them anagrams of each other with less than 7 steps.
//
// Constraints:
// 1 <= s.length, t.length <= 2 * 105
// 	s and t consist of lowercase English letters.
//

/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
var minSteps = function(s, t) {
    const countS = new Array(26).fill(0);
    const countT = new Array(26).fill(0);
    for (const char of s) {
        countS[char.charCodeAt(0) - 97]++;
    }
    for (const char of t) {
        countT[char.charCodeAt(0) - 97]++;
    }
    let steps = 0;
    for (let i = 0; i < 26; i++) {
        steps += Math.abs(countS[i] - countT[i]);
    }
    return steps;
};  