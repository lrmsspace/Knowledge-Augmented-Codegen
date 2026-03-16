// Source: https://leetcode.com/problems/check-if-the-sentence-is-pangram/   |   Difficulty: Easy
//
// Problem Description:
// A pangram is a sentence where every letter of the English alphabet appears at least once.
//
// Given a string sentence containing only lowercase English letters, return true if sentence is a pangram, or false otherwise.
//
// Example:
// Input: sentence = "thequickbrownfoxjumpsoverthelazydog"
// Output: true
// Explanation: sentence contains at least one of every letter of the English alphabet.
//
// Constraints:
// 1 <= sentence.length <= 1000
// 	sentence consists of lowercase English letters.
//

/**
 * @param {string} sentence
 * @return {boolean}
 */
var checkIfPangram = function(sentence) {
    const seen = new Set();
    for (const char of sentence) {
        seen.add(char);
        if (seen.size === 26) {
            return true;
        }
    }
    return false;
};
