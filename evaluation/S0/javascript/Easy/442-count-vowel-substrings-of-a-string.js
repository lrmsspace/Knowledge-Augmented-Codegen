// Source: https://leetcode.com/problems/count-vowel-substrings-of-a-string/   |   Difficulty: Easy
//
// Problem Description:
// A substring is a contiguous (non-empty) sequence of characters within a string.
//
// A vowel substring is a substring that only consists of vowels ('a', 'e', 'i', 'o', and 'u') and has all five vowels present in it.
//
// Given a string word, return the number of vowel substrings in word.
//
// Example:
// Input: word = "aeiouu"
// Output: 2
// Explanation: The vowel substrings of word are as follows (underlined):
// - "aeiouu"
// - "aeiouu"
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists of lowercase English letters only.
//

/**
 * @param {string} word
 * @return {number}
 */
var countVowelSubstrings = function(word) {
    const isVowel = (char) => 'aeiou'.includes(char);
    let count = 0;
    for (let i = 0; i < word.length; i++) {
        for (let j = i; j < word.length; j++) {
            const substring = word.slice(i, j + 1);
            if ([...substring].every(isVowel)) {
                const uniqueVowels = new Set(substring);
                if (uniqueVowels.size === 5) {
                    count++;
                }
            }
        }
    }
    return count;
};