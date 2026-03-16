// Source: https://leetcode.com/problems/determine-if-string-halves-are-alike/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s of even length. Split this string into two halves of equal lengths, and let a be the first half and b be the second half.
//
// Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). Notice that s contains uppercase and lowercase letters.
//
// Return true if a and b are alike. Otherwise, return false.
//
// Example:
// Input: s = "book"
// Output: true
// Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.
//
// Constraints:
// 2 <= s.length <= 1000
// 	s.length is even.
// 	s consists of uppercase and lowercase letters.
//

/**
 * @param {string} s
 * @return {boolean}
 */
var halvesAreAlike = function(s) {
    const vowels = new Set(['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U']);
    const mid = s.length / 2;
    let countA = 0;
    let countB = 0;
    for (let i = 0; i < mid; i++) {
        if (vowels.has(s[i])) {
            countA++;
        }
    }
    for (let i = mid; i < s.length; i++) {
        if (vowels.has(s[i])) {
            countB++;
        }
    }
    return countA === countB;
};