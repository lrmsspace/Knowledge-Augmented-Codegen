// Source: https://leetcode.com/problems/sorting-the-sentence/   |   Difficulty: Easy
//
// Problem Description:
// A sentence is a list of words that are separated by a single space with no leading or trailing spaces. Each word consists of lowercase and uppercase English letters.
//
// A sentence can be shuffled by appending the 1-indexed word position to each word then rearranging the words in the sentence.
//
//
// 	For example, the sentence "This is a sentence" can be shuffled as "sentence4 a3 is2 This1" or "is2 sentence4 This1 a3".
//
//
// Given a shuffled sentence s containing no more than 9 words, reconstruct and return the original sentence.
//
// Example:
// Input: s = "is2 sentence4 This1 a3"
// Output: "This is a sentence"
// Explanation: Sort the words in s to their original positions "This1 is2 a3 sentence4", then remove the numbers.
//
// Constraints:
// 2 <= s.length <= 200
// 	s consists of lowercase and uppercase English letters, spaces, and digits from 1 to 9.
// 	The number of words in s is between 1 and 9.
// 	The words in s are separated by a single space.
// 	s contains no leading or trailing spaces.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {string}
 */
var sortSentence = function(s) {
    const words = s.split(' ');
    const sortedWords = new Array(words.length);
    
    for (const word of words) {
        const index = parseInt(word[word.length - 1]);
        sortedWords[index - 1] = word.substring(0, word.length - 1);
    }
    
    return sortedWords.join(' ');
};
