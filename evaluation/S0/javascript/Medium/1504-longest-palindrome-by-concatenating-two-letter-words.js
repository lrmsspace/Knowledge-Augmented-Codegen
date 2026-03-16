// Source: https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings words. Each element of words consists of two lowercase English letters.
//
// Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each element can be selected at most once.
//
// Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.
//
// A palindrome is a string that reads the same forward and backward.
//
// Example:
// Input: words = ["lc","cl","gg"]
// Output: 6
// Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
// Note that "clgglc" is another longest palindrome that can be created.
//
// Constraints:
// 1 <= words.length <= 105
// 	words[i].length == 2
// 	words[i] consists of lowercase English letters.
//

/**
 * @param {string[]} words
 * @return {number}
 */
var longestPalindrome = function(words) {
    const countMap = new Map(); // Map to count occurrences of each word
    let length = 0;
    let hasOddCenter = false;
    for (const word of words) {
        countMap.set(word, (countMap.get(word) || 0) + 1);
    }
    for (const [word, count] of countMap.entries()) {
        const reversed = word[1] + word[0];
        if (word === reversed) {
            length += Math.floor(count / 2) * 4;
            if (count % 2 === 1) {
                hasOddCenter = true;
            }
        } else if (countMap.has(reversed)) {
            length += Math.min(count, countMap.get(reversed)) * 2;
            countMap.set(reversed, 0);
        }
        countMap.set(word, 0);
    }
    if (hasOddCenter) {
        length += 2;
    }
    return length;
};