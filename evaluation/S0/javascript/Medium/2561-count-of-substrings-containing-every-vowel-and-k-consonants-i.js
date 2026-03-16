// Source: https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word and a non-negative integer k.
//
// Return the total number of substrings of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once and exactly k consonants.
//
// Example:
// Input: word = "aeioqq", k = 1
//
// Output: 0
//
// Explanation:
//
// There is no substring with every vowel.
//
// Constraints:
// 5 <= word.length <= 250
// 	word consists only of lowercase English letters.
// 	0 <= k <= word.length - 5
//

/**
 * @param {string} word
 * @param {number} k
 * @return {number}
 */
var countOfSubstrings = function(word, k) {
    const vowels = new Set(['a', 'e', 'i', 'o', 'u']);
    let count = 0;
    for (let i = 0; i < word.length; i++) {
        const seenVowels = new Set();
        let consonantCount = 0;
        for (let j = i; j < word.length; j++) {
            const char = word[j];
            if (vowels.has(char)) {
                seenVowels.add(char);
            }
            else {
                consonantCount++;
            }
            if (seenVowels.size === 5 && consonantCount === k) {
                count++;
            }
        }
    }
    return count;   
};
