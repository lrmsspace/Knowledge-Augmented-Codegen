// Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called valid if x can be rearranged to have word2 as a prefix.
//
// Return the total number of valid substrings of word1.
//
// Note that the memory limits in this problem are smaller than usual, so you must implement a solution with a linear runtime complexity.
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
// 1 <= word1.length <= 106
// 	1 <= word2.length <= 104
// 	word1 and word2 consist only of lowercase English letters.
//

/**
 * @param {string} word1
 * @param {string} word2
 * @return {number}
 */
var validSubstringCount = function(word1, word2) {
    const m = word2.length;
    const targetCount = Array(26).fill(0);
    for (let i = 0; i < m; i++) {
        targetCount[word2.charCodeAt(i) - 97]++;
    }
    let left = 0;
    let right = 0;
    const windowCount = Array(26).fill(0);
    let validCount = 0;
    let result = 0;
    while (right < word1.length) {
        const charIndex = word1.charCodeAt(right) - 97;
        windowCount[charIndex]++;
        if (windowCount[charIndex] === targetCount[charIndex]) {
            validCount++;
        }
        right++;    
        while (right - left >= m) {
            if (validCount === 26) {
                result++;
            }
            const leftCharIndex = word1.charCodeAt(left) - 97;
            if (windowCount[leftCharIndex] === targetCount[leftCharIndex]) {
                validCount--;
            }
            windowCount[leftCharIndex]--;
            left++;
        }
    }
    return result;
};
