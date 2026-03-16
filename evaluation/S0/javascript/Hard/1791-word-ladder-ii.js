// Source: https://leetcode.com/problems/word-ladder-ii/   |   Difficulty: Hard
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
// Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].
//
// Example:
// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
// Explanation: There are 2 shortest transformation sequences:
// "hit" -> "hot" -> "dot" -> "dog" -> "cog"
// "hit" -> "hot" -> "lot" -> "log" -> "cog"
//
// Constraints:
// 1 <= beginWord.length <= 5
// 	endWord.length == beginWord.length
// 	1 <= wordList.length <= 500
// 	wordList[i].length == beginWord.length
// 	beginWord, endWord, and wordList[i] consist of lowercase English letters.
// 	beginWord != endWord
// 	All the words in wordList are unique.
// 	The sum of all shortest transformation sequences does not exceed 105.
//

/**
 * @param {string} beginWord
 * @param {string} endWord
 * @param {string[]} wordList
 * @return {string[][]}
 */
var findLadders = function(beginWord, endWord, wordList) {
    const wordSet = new Set(wordList);
    if (!wordSet.has(endWord)) return [];
    const result = [];
    const queue = [[beginWord]];
    let found = false;
    while (queue.length > 0 && !found) {
        const levelSize = queue.length;
        const visited = new Set();
        for (let i = 0; i < levelSize; i++) {   
            const path = queue.shift();
            const lastWord = path[path.length - 1];
            for (let j = 0; j < lastWord.length; j++) {
                for (let c = 97; c <= 122; c++) {
                    const nextWord = lastWord.substring(0, j) + String.fromCharCode(c) + lastWord.substring(j + 1);
                    if (wordSet.has(nextWord) && !visited.has(nextWord)) {
                        const newPath = [...path, nextWord];
                        if (nextWord === endWord) {
                            result.push(newPath);
                            found = true;
                        }
                        queue.push(newPath);
                        visited.add(nextWord);
                    }
                }
            }
        }        for (const word of visited) {
            wordSet.delete(word);
        }
    }
    return result;
};
