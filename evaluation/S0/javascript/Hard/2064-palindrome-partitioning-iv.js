// Source: https://leetcode.com/problems/palindrome-partitioning-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, return true if it is possible to split the string s into three non-empty palindromic substrings. Otherwise, return false.​​​​​
//
// A string is said to be palindrome if it the same string when reversed.
//
// Example:
// Input: s = "abcbdd"
// Output: true
// Explanation: "abcbdd" = "a" + "bcb" + "dd", and all three substrings are palindromes.
//
// Constraints:
// 3 <= s.length <= 2000
// 	s​​​​​​ consists only of lowercase English letters.
//

/**
 * @param {string} s
 * @return {boolean}
 */
var checkPartitioning = function(s) {
    const n = s.length;
    const isPalindrome = new Array(n).fill(0).map(() => new Array(n).fill(false));
    for (let i = 0; i < n; i++) {
        isPalindrome[i][i] = true;
    }
    for (let length = 2; length <= n; length++) {
        for (let start = 0; start <= n - length; start++) {
            const end = start + length - 1;
            if (s[start] === s[end]) {
                if (length === 2) {
                    isPalindrome[start][end] = true;
                } else {
                    isPalindrome[start][end] = isPalindrome[start + 1][end - 1];
                }
            }
        }
    }
    for (let i = 0; i < n - 2; i++) {
        if (isPalindrome[0][i]) {
            for (let j = i + 1; j < n - 1; j++) {
                if (isPalindrome[i + 1][j] && isPalindrome[j + 1][n - 1]) {
                    return true;
                }
            }
        }
    }
    return false;   
};
