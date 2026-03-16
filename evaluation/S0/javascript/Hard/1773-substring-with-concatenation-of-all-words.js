// Source: https://leetcode.com/problems/substring-with-concatenation-of-all-words/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an array of strings words. All the strings of words are of the same length.
//
// A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.
//
//
// 	For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
//
//
// Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.
//
// Example:
// Input: s = "barfoothefoobarman", words = ["foo","bar"]
//
// Output: [0,9]
//
// Explanation:
//
// The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
// The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
//
// Constraints:
// 1 <= s.length <= 104
// 	1 <= words.length <= 5000
// 	1 <= words[i].length <= 30
// 	s and words[i] consist of lowercase English letters.
//

/**
 * @param {string} s
 * @param {string[]} words
 * @return {number[]}
 */
var findSubstring = function(s, words) {
    if (words.length === 0 || s.length === 0) return [];
    const wordLength = words[0].length;
    const wordCount = words.length;
    const substringSize = wordLength * wordCount;
    const wordFrequency = new Map();
    for (const word of words) {
        wordFrequency.set(word, (wordFrequency.get(word) || 0) + 1);
    }
    const resultIndices = [];
    for (let i = 0; i <= s.length - substringSize; i++) {
        const wordsSeen = new Map();
        for (let j = 0; j < wordCount; j++) {
            const nextWordIndex = i + j * wordLength;
            const word = s.substring(nextWordIndex, nextWordIndex + wordLength);
            if (!wordFrequency.has(word)) {
                break;
            }
            wordsSeen.set(word, (wordsSeen.get(word) || 0) + 1);
            if (wordsSeen.get(word) > wordFrequency.get(word)) {
                break;
            }
            if (j + 1 === wordCount) {
                resultIndices.push(i);
            }
        }
    }
    return resultIndices;
        
};
