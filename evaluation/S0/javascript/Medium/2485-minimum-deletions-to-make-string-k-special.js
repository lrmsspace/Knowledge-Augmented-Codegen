// Source: https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word and an integer k.
//
// We consider word to be k-special if |freq(word[i]) - freq(word[j])| <= k for all indices i and j in the string.
//
// Here, freq(x) denotes the frequency of the character x in word, and |y| denotes the absolute value of y.
//
// Return the minimum number of characters you need to delete to make word k-special.
//
// Example:
// Input: word = "aabcaba", k = 0
//
// Output: 3
//
// Explanation: We can make word 0-special by deleting 2 occurrences of "a" and 1 occurrence of "c". Therefore, word becomes equal to "baba" where freq('a') == freq('b') == 2.
//
// Constraints:
// 1 <= word.length <= 105
// 	0 <= k <= 105
// 	word consists only of lowercase English letters.
//

/**
 * @param {string} word
 * @param {number} k
 * @return {number}
 */
var minimumDeletions = function(word, k) {
    const freq = Array(26).fill(0);
    for (const char of word) {
        freq[char.charCodeAt(0) - 97]++;
    }
    freq.sort((a, b) => a - b);
    const n = freq.length;
    let minDeletions = Infinity;
    for (let targetFreq = 0; targetFreq <= freq[n - 1]; targetFreq++) {
        let deletions = 0;
        for (let i = 0; i < n; i++) {
            if (freq[i] > targetFreq + k) {
                deletions += freq[i] - (targetFreq + k);
            } else if (freq[i] < targetFreq) {
                deletions += freq[i];
            }
        }
        minDeletions = Math.min(minDeletions, deletions);
    }
    return minDeletions;
};
