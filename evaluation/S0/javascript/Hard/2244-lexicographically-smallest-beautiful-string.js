// Source: https://leetcode.com/problems/lexicographically-smallest-beautiful-string/   |   Difficulty: Hard
//
// Problem Description:
// A string is beautiful if:
//
//
// 	It consists of the first k letters of the English lowercase alphabet.
// 	It does not contain any substring of length 2 or more which is a palindrome.
//
//
// You are given a beautiful string s of length n and a positive integer k.
//
// Return the lexicographically smallest string of length n, which is larger than s and is beautiful. If there is no such string, return an empty string.
//
// A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b.
//
//
// 	For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.
//
// Example:
// Input: s = "abcz", k = 26
// Output: "abda"
// Explanation: The string "abda" is beautiful and lexicographically larger than the string "abcz".
// It can be proven that there is no string that is lexicographically larger than the string "abcz", beautiful, and lexicographically smaller than the string "abda".
//
// Constraints:
// 1 <= n == s.length <= 105
// 	4 <= k <= 26
// 	s is a beautiful string.
//

/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
var smallestBeautifulString = function(s, k) {
    const n = s.length;
    const chars = s.split('');
    for (let i = n - 1; i >= 0; i--) {
        for (let j = chars[i].charCodeAt(0) - 96 + 1; j <= k; j++) {
            const nextChar = String.fromCharCode(j + 96);
            if ((i > 0 && chars[i - 1] === nextChar) || (i > 1 && chars[i - 2] === nextChar)) {
                continue;
            }
            chars[i] = nextChar;
            for (let m = i + 1; m < n; m++) {
                for (let l = 1; l <= k; l++) {
                    const candidateChar = String.fromCharCode(l + 96);
                    if ((m > 0 && chars[m - 1] === candidateChar) || (m > 1 && chars[m - 2] === candidateChar)) {
                        continue;
                    }
                    chars[m] = candidateChar;
                    break;
                }
            }
            return chars.join('');
        }
    }
    return '';
};
