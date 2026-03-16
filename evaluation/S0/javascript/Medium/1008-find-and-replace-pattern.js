// Source: https://leetcode.com/problems/find-and-replace-pattern/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of strings words and a string pattern, return a list of words[i] that match pattern. You may return the answer in any order.
//
// A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.
//
// Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.
//
// Example:
// Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
// Output: ["mee","aqq"]
// Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
// "ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation, since a and b map to the same letter.
//
// Constraints:
// 1 <= pattern.length <= 20
// 	1 <= words.length <= 50
// 	words[i].length == pattern.length
// 	pattern and words[i] are lowercase English letters.
//

/**
 * @param {string[]} words
 * @param {string} pattern
 * @return {string[]}
 */
var findAndReplacePattern = function(words, pattern) {
    const matchesPattern = (word, pattern) => {
        const charMap = new Map();
        const usedChars = new Set();
        for (let i = 0; i < word.length; i++) {
            const wChar = word[i];
            const pChar = pattern[i];
            if (!charMap.has(pChar)) {
                if (usedChars.has(wChar)) {
                    return false;
                }
                charMap.set(pChar, wChar);
                usedChars.add(wChar);
            }
            else if (charMap.get(pChar) !== wChar) { 
                return false;
            }
        }
        return true;
    };

    const result = [];
    for (const word of words) {
        if (matchesPattern(word, pattern)) {
            result.push(word);
        }
    }
    return result;
};  