// Source: https://leetcode.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s, an integer k, a letter letter, and an integer repetition.
//
// Return the lexicographically smallest subsequence of s of length k that has the letter letter appear at least repetition times. The test cases are generated so that the letter appears in s at least repetition times.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// A string a is lexicographically smaller than a string b if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
//
// Example:
// Input: s = "leet", k = 3, letter = "e", repetition = 1
// Output: "eet"
// Explanation: There are four subsequences of length 3 that have the letter 'e' appear at least 1 time:
// - "lee" (from "leet")
// - "let" (from "leet")
// - "let" (from "leet")
// - "eet" (from "leet")
// The lexicographically smallest subsequence among them is "eet".
//
// Constraints:
// 1 <= repetition <= k <= s.length <= 5 * 104
// 	s consists of lowercase English letters.
// 	letter is a lowercase English letter, and appears in s at least repetition times.
//

/**
 * @param {string} s
 * @param {number} k
 * @param {character} letter
 * @param {number} repetition
 * @return {string}
 */
var smallestSubsequence = function(s, k, letter, repetition) {
    const n = s.length;
    const countLetter = new Array(n).fill(0);
    countLetter[0] = s[0] === letter ? 1 : 0;
    for (let i = 1; i < n; i++) {
        countLetter[i] = countLetter[i - 1] + (s[i] === letter ? 1 : 0);
    }
    const stack = [];
    for (let i = 0; i < n; i++) {
        while (stack.length > 0 && stack[stack.length - 1] > s[i] && stack.length + n - i > k && countLetter[n - 1] - countLetter[i] >= repetition) {
            const top = stack.pop();
            if (top === letter) {
                repetition += 1;
            }
        }
        if (stack.length < k) {
            stack.push(s[i]);
            if (s[i] === letter) {
                repetition -= 1;
            }
        }
    }
    return stack.join("");  
};
