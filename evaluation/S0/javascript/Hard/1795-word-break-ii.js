// Source: https://leetcode.com/problems/word-break-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.
//
// Note that the same word in the dictionary may be reused multiple times in the segmentation.
//
// Example:
// Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
// Output: ["cats and dog","cat sand dog"]
//
// Constraints:
// 1 <= s.length <= 20
// 	1 <= wordDict.length <= 1000
// 	1 <= wordDict[i].length <= 10
// 	s and wordDict[i] consist of only lowercase English letters.
// 	All the strings of wordDict are unique.
// 	Input is generated in a way that the length of the answer doesn't exceed 105.
//

/**
 * @param {string} s
 * @param {string[]} wordDict
 * @return {string[]}
 */
var wordBreak = function(s, wordDict) {
    

    const wordSet = new Set(wordDict);
    const memo = new Map();
    function backtrack(start) {
        if (memo.has(start)) {
            return memo.get(start);
        }
        const sentences = [];
        for (let end = start + 1; end <= s.length; end++) {
            const word = s.substring(start, end);
            if (wordSet.has(word)) {
                if (end === s.length) {
                    sentences.push(word);
                } else {
                    const subSentences = backtrack(end);
                    for (const sub of subSentences) {
                        sentences.push(word + ' ' + sub);
                    }
                }
            }
        }
        memo.set(start, sentences);
        return sentences;
     }
     
    return backtrack(0);
};
