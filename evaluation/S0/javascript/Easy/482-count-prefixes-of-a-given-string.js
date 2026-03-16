// Source: https://leetcode.com/problems/count-prefixes-of-a-given-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string array words and a string s, where words[i] and s comprise only of lowercase English letters.
//
// Return the number of strings in words that are a prefix of s.
//
// A prefix of a string is a substring that occurs at the beginning of the string. A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: words = ["a","b","c","ab","bc","abc"], s = "abc"
// Output: 3
// Explanation:
// The strings in words which are a prefix of s = "abc" are:
// "a", "ab", and "abc".
// Thus the number of strings in words which are a prefix of s is 3.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length, s.length <= 10
// 	words[i] and s consist of lowercase English letters only.
//

/**
 * @param {string[]} words
 * @param {string} s
 * @return {number}
 */
var countPrefixes = function(words, s) {
    let count = 0;
    for (const word of words) {
        if (s.startsWith(word)) {
            count++;
        }
    }
    return count;
};
