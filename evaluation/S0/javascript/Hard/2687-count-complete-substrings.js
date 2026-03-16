// Source: https://leetcode.com/problems/count-complete-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string word and an integer k.
//
// A substring s of word is complete if:
//
//
// 	Each character in s occurs exactly k times.
// 	The difference between two adjacent characters is at most 2. That is, for any two adjacent characters c1 and c2 in s, the absolute difference in their positions in the alphabet is at most 2.
//
//
// Return the number of complete substrings of word.
//
// A substring is a non-empty contiguous sequence of characters in a string.
//
// Example:
// Input: word = "igigee", k = 2
// Output: 3
// Explanation: The complete substrings where each character appears exactly twice and the difference between adjacent characters is at most 2 are: igigee, igigee, igigee.
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists only of lowercase English letters.
// 	1 <= k <= word.length
//

/**
 * @param {string} word
 * @param {number} k
 * @return {number}
 */
var countCompleteSubstrings = function(word, k) {
    const n = word.length;
    let count = 0;
    for (let i = 0; i < n; i++) {
        const charCount = new Map();
        let isComplete = true;
        for (let j = i; j < n; j++) {
            const char = word[j];
            charCount.set(char, (charCount.get(char) || 0) + 1);
            if (charCount.get(char) > k) {
                isComplete = false;
                break;
            }
            if (j > i) {
                const prevChar = word[j - 1];
                if (Math.abs(char.charCodeAt(0) - prevChar.charCodeAt(0)) > 2) {
                    isComplete = false;
                    break;
                }
            }
            if (isComplete && charCount.size * k === j - i + 1) {
                count++;
            }
        }
    }
    return count;   
};
