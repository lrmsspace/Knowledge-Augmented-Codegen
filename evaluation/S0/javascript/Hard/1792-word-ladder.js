// Source: https://leetcode.com/problems/word-ladder/   |   Difficulty: Hard
//
// Problem Description:
// A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
//
//
// 	Every adjacent pair of words differs by a single letter.
// 	Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
// 	sk == endWord
//
//
// Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.
//
// Example:
// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// Output: 5
// Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
//
// Constraints:
// 1 <= beginWord.length <= 10
// 	endWord.length == beginWord.length
// 	1 <= wordList.length <= 5000
// 	wordList[i].length == beginWord.length
// 	beginWord, endWord, and wordList[i] consist of lowercase English letters.
// 	beginWord != endWord
// 	All the words in wordList are unique.
//

/**
 * @param {string} beginWord
 * @param {string} endWord
 * @param {string[]} wordList
 * @return {number}
 */
var ladderLength = function(beginWord, endWord, wordList) {
    const wordSet = new Set(wordList);
    if (!wordSet.has(endWord)) return 0;
    const queue = [[beginWord, 1]];
    while (queue.length > 0) {
        const [word, length] = queue.shift();
        if (word === endWord) {
            return length;
        }
        for (let i = 0; i < word.length; i++) {
            for (let c = 97; c <= 122; c++) {
                const nextWord = word.substring(0, i) + String.fromCharCode(c) + word.substring(i + 1);
                if (wordSet.has(nextWord)) {
                    queue.push([nextWord, length + 1]);
                    wordSet.delete(nextWord);
                }
            }
        }
    }
    return 0;   
};









