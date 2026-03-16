// Source: https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
//
// Example:
// Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
// Output: "apple"
//
// Constraints:
// 1 <= s.length <= 1000
// 	1 <= dictionary.length <= 1000
// 	1 <= dictionary[i].length <= 1000
// 	s and dictionary[i] consist of lowercase English letters.
//

/**
 * @param {string} s
 * @param {string[]} dictionary
 * @return {string}
 */
var findLongestWord = function(s, dictionary) {
    let longestWord = "";
    for (const word of dictionary) {
        let i = 0, j = 0;
        while (i < s.length && j < word.length) {
            if (s[i] === word[j]) {
                j++;
            }
            i++;
        }
        if (j === word.length) {
            if (word.length > longestWord.length || (word.length === longestWord.length && word < longestWord)) {
                longestWord = word;
            }
        }
    }
    return longestWord;
};