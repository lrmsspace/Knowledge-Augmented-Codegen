// Source: https://leetcode.com/problems/make-number-of-distinct-characters-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed strings word1 and word2.
//
// A move consists of choosing two indices i and j such that 0 <= i < word1.length and 0 <= j < word2.length and swapping word1[i] with word2[j].
//
// Return true if it is possible to get the number of distinct characters in word1 and word2 to be equal with exactly one move. Return false otherwise.
//
// Example:
// Input: word1 = "ac", word2 = "b"
// Output: false
// Explanation: Any pair of swaps would yield two distinct characters in the first string, and one in the second string.
//
// Constraints:
// 1 <= word1.length, word2.length <= 105
// 	word1 and word2 consist of only lowercase English letters.
//

/**
 * @param {string} word1
 * @param {string} word2
 * @return {boolean}
 */
var isItPossible = function(word1, word2) {
    const getCharCount = (word) => {
        const charCount = new Array(26).fill(0);
        for (const char of word) {
            charCount[char.charCodeAt(0) - 97]++;
        }
        return charCount;
    };

    const charCount1 = getCharCount(word1);
    const charCount2 = getCharCount(word2);
    for (let i = 0; i < 26; i++) {
        if (charCount1[i] === 0) continue;
        for (let j = 0; j < 26; j++) {
            if (charCount2[j] === 0) continue;
            charCount1[i]--;
            charCount1[j]++;
            charCount2[j]--;
            charCount2[i]++;
            const distinct1 = charCount1.filter(count => count > 0).length;
            const distinct2 = charCount2.filter(count => count > 0).length;
            if (distinct1 === distinct2) {
                return true;
            }
            charCount1[i]++;
            charCount1[j]--;
            charCount2[j]++;
            charCount2[i]--;
        }
    }   
    return false;
};  