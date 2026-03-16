// Source: https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// With respect to a given puzzle string, a word is valid if both the following conditions are satisfied:
//
// 	word contains the first letter of puzzle.
// 	For each letter in word, that letter is in puzzle.
// 	
// 		For example, if the puzzle is "abcdefg", then valid words are "faced", "cabbage", and "baggage", while
// 		invalid words are "beefed" (does not include 'a') and "based" (includes 's' which is not in the puzzle).
// 	
// 	
//
// Return an array answer, where answer[i] is the number of words in the given word list words that is valid with respect to the puzzle puzzles[i].
//
// Example:
// Input: words = ["aaaa","asas","able","ability","actt","actor","access"], puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
// Output: [1,1,3,2,4,0]
// Explanation: 
// 1 valid word for "aboveyz" : "aaaa" 
// 1 valid word for "abrodyz" : "aaaa"
// 3 valid words for "abslute" : "aaaa", "asas", "able"
// 2 valid words for "absoryz" : "aaaa", "asas"
// 4 valid words for "actresz" : "aaaa", "asas", "actt", "access"
// There are no valid words for "gaswxyz" cause none of the words in the list contains letter 'g'.
//
// Constraints:
// 1 <= words.length <= 105
// 	4 <= words[i].length <= 50
// 	1 <= puzzles.length <= 104
// 	puzzles[i].length == 7
// 	words[i] and puzzles[i] consist of lowercase English letters.
// 	Each puzzles[i] does not contain repeated characters.
//

/**
 * @param {string[]} words
 * @param {string[]} puzzles
 * @return {number[]}
 */
var findNumOfValidWords = function(words, puzzles) {
    const wordCount = new Map();
    for (const word of words) {
        let bitmask = 0;
        for (const char of new Set(word)) {
            bitmask |= 1 << (char.charCodeAt(0) - 'a'.charCodeAt(0));
        }
        wordCount.set(bitmask, (wordCount.get(bitmask) || 0) + 1);
    }
    const result = [];
    for (const puzzle of puzzles) {
        const firstCharBit = 1 << (puzzle.charCodeAt(0) - 'a'.charCodeAt(0));
        let count = 0;
        const puzzleBitmask = puzzle.split('').reduce((mask, char) => mask | (1 << (char.charCodeAt(0) - 'a'.charCodeAt(0))), 0);
        let submask = puzzleBitmask;
        while (submask) {
            if ((submask & firstCharBit) === firstCharBit && wordCount.has(submask)) {
                count += wordCount.get(submask);
            }
            submask = (submask - 1) & puzzleBitmask;
        }
        result.push(count);
    }
    return result;
};
