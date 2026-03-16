// Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called valid if x can be rearranged to have word2 as a prefix.
//
// Return the total number of valid substrings of word1.
//
// Example:
// Input: word1 = "bcca", word2 = "abc"
//
// Output: 1
//
// Explanation:
//
// The only valid substring is "bcca" which can be rearranged to "abcc" having "abc" as a prefix.
//
// Constraints:
// 1 <= word1.length <= 105
// 	1 <= word2.length <= 104
// 	word1 and word2 consist only of lowercase English letters.
//

/**
 * @param {string} word1
 * @param {string} word2
 * @return {number}
 */
var validSubstringCount = function(word1, word2) {
    const count1 = Array(26).fill(0);
    const count2 = Array(26).fill(0);
    for (const char of word2) {
        count2[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }
    let validCount = 0;
    for (let i = 0; i < word1.length; i++) {
        count1[word1.charCodeAt(i) - 'a'.charCodeAt(0)]++;
        if (i >= word2.length) {
            count1[word1.charCodeAt(i - word2.length) - 'a'.charCodeAt(0)]--;
        }
        if (i >= word2.length - 1) {
            let isValid = true;
            for (let j = 0; j < 26; j++) {
                if (count1[j] < count2[j]) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                validCount++;
            }
        }
    }
    return validCount;  
};
