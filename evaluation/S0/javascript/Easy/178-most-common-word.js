// Source: https://leetcode.com/problems/most-common-word/   |   Difficulty: Easy
//
// Problem Description:
// Given a string paragraph and a string array of the banned words banned, return the most frequent word that is not banned. It is guaranteed there is at least one word that is not banned, and that the answer is unique.
//
// The words in paragraph are case-insensitive and the answer should be returned in lowercase.
//
// Note that words can not contain punctuation symbols.
//
// Example:
// Input: paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.", banned = ["hit"]
// Output: "ball"
// Explanation: 
// "hit" occurs 3 times, but it is a banned word.
// "ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph. 
// Note that words in the paragraph are not case sensitive,
// that punctuation is ignored (even if adjacent to words, such as "ball,"), 
// and that "hit" isn't the answer even though it occurs more because it is banned.
//
// Constraints:
// 1 <= paragraph.length <= 1000
// 	paragraph consists of English letters, space ' ', or one of the symbols: "!?',;.".
// 	0 <= banned.length <= 100
// 	1 <= banned[i].length <= 10
// 	banned[i] consists of only lowercase English letters.
//

/**
 * @param {string} paragraph
 * @param {string[]} banned
 * @return {string}
 */
var mostCommonWord = function(paragraph, banned) {
    const bannedSet = new Set(banned);
    const wordCount = new Map();
    const words = paragraph.toLowerCase().match(/\b\w+\b/g);
    for (const word of words) {
        if (!bannedSet.has(word)) {
            wordCount.set(word, (wordCount.get(word) || 0) + 1);
        }
    }

    let mostCommon = "";
    let maxCount = 0;
    for (const [word, count] of wordCount.entries()) {
        if (count > maxCount) {
            mostCommon = word;
            maxCount = count;
        }
    }
    return mostCommon;
};
