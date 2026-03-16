// Source: https://leetcode.com/problems/replace-words/   |   Difficulty: Medium
//
// Problem Description:
// In English, we have a concept called root, which can be followed by some other word to form another longer word - let's call this word derivative. For example, when the root "help" is followed by the word "ful", we can form a derivative "helpful".
//
// Given a dictionary consisting of many roots and a sentence consisting of words separated by spaces, replace all the derivatives in the sentence with the root forming it. If a derivative can be replaced by more than one root, replace it with the root that has the shortest length.
//
// Return the sentence after the replacement.
//
// Example:
// Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
// Output: "the cat was rat by the bat"
//
// Constraints:
// 1 <= dictionary.length <= 1000
// 	1 <= dictionary[i].length <= 100
// 	dictionary[i] consists of only lower-case letters.
// 	1 <= sentence.length <= 106
// 	sentence consists of only lower-case letters and spaces.
// 	The number of words in sentence is in the range [1, 1000]
// 	The length of each word in sentence is in the range [1, 1000]
// 	Every two consecutive words in sentence will be separated by exactly one space.
// 	sentence does not have leading or trailing spaces.
//

/**
 * @param {string[]} dictionary
 * @param {string} sentence
 * @return {string}
 */
var replaceWords = function(dictionary, sentence) {
    const rootSet = new Set(dictionary);
    const words = sentence.split(' ');
    const replacedWords = words.map(word => {
        for (let i = 1; i <= word.length; i++) {
            const prefix = word.slice(0, i);
            if (rootSet.has(prefix)) {
                return prefix;
            }
        }
        return word;
    });
    return replacedWords.join(' ');
};