// Source: https://leetcode.com/problems/shortest-completing-word/   |   Difficulty: Easy
//
// Problem Description:
// Given a string licensePlate and an array of strings words, find the shortest completing word in words.
//
// A completing word is a word that contains all the letters in licensePlate. Ignore numbers and spaces in licensePlate, and treat letters as case insensitive. If a letter appears more than once in licensePlate, then it must appear in the word the same number of times or more.
//
// For example, if licensePlate = "aBc 12c", then it contains letters 'a', 'b' (ignoring case), and 'c' twice. Possible completing words are "abccdef", "caaacab", and "cbca".
//
// Return the shortest completing word in words. It is guaranteed an answer exists. If there are multiple shortest completing words, return the first one that occurs in words.
//
// Example:
// Input: licensePlate = "1s3 PSt", words = ["step","steps","stripe","stepple"]
// Output: "steps"
// Explanation: licensePlate contains letters 's', 'p', 's' (ignoring case), and 't'.
// "step" contains 't' and 'p', but only contains 1 's'.
// "steps" contains 't', 'p', and both 's' characters.
// "stripe" is missing an 's'.
// "stepple" is missing an 's'.
// Since "steps" is the only word containing all the letters, that is the answer.
//
// Constraints:
// 1 <= licensePlate.length <= 7
// 	licensePlate contains digits, letters (uppercase or lowercase), or space ' '.
// 	1 <= words.length <= 1000
// 	1 <= words[i].length <= 15
// 	words[i] consists of lower case English letters.
//

/**
 * @param {string} licensePlate
 * @param {string[]} words
 * @return {string}
 */
var shortestCompletingWord = function(licensePlate, words) {
    const charCount = {};
    for (const char of licensePlate.toLowerCase()) {
        if (char >= 'a' && char <= 'z') {
            charCount[char] = (charCount[char] || 0) + 1;
        }
    }
    let result = null;
    for (const word of words) {
        const wordCount = {};
        for (const char of word) {
            wordCount[char] = (wordCount[char] || 0) + 1;
        }
        let isCompleting = true;
        for (const char in charCount) {
            if ((wordCount[char] || 0) < charCount[char]) {
                isCompleting = false;
                break;
            }
        }
        if (isCompleting && (result === null || word.length < result.length)) {
            result = word;
        }
    }
    return result;
};
