// Source: https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.
//
// Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
//
// Example:
// Input: s = "abciiidef", k = 3
// Output: 3
// Explanation: The substring "iii" contains 3 vowel letters.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	1 <= k <= s.length
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var maxVowels = function(s, k) {
    const vowels = new Set(['a', 'e', 'i', 'o', 'u']);
    let maxCount = 0;
    let currentCount = 0;
    for (let i = 0; i < s.length; i++) {
        if (vowels.has(s[i])) {
            currentCount++;
        }
        if (i >= k) {
            if (vowels.has(s[i - k])) {
                currentCount--;
            }
        }
        maxCount = Math.max(maxCount, currentCount);
    }
    return maxCount;
        
};
