// Source: https://leetcode.com/problems/find-maximum-number-of-non-intersecting-substrings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word.
//
// Return the maximum number of non-intersecting substrings of word that are at least four characters long and start and end with the same letter.
//
// Example:
// Input: word = "abcdeafdef"
//
// Output: 2
//
// Explanation:
//
// The two substrings are "abcdea" and "fdef".
//
// Constraints:
// 1 <= word.length <= 2 * 105
// 	word consists only of lowercase English letters.
//

/**
 * @param {string} word
 * @return {number}
 */
var maxSubstrings = function(word) {
    const n = word.length;
    const firstOccurrence = new Array(26).fill(-1);
    const lastOccurrence = new Array(26).fill(-1);  
    for (let i = 0; i < n; i++) {
        const charIndex = word.charCodeAt(i) - 97;
        if (firstOccurrence[charIndex] === -1) {
            firstOccurrence[charIndex] = i;
        }
        lastOccurrence[charIndex] = i;
    }
    const intervals = [];
    for (let i = 0; i < 26; i++) {
        if (firstOccurrence[i] !== -1 && lastOccurrence[i] - firstOccurrence[i] >= 3) {
            intervals.push([firstOccurrence[i], lastOccurrence[i]]);
        }
    }
    intervals.sort((a, b) => a[1] - b[1]);
    let count = 0;
    let lastEnd = -1;
    for (const [start, end] of intervals) {
        if (start > lastEnd) {
            count++;
            lastEnd = end;
        }
    }
    return count;   
};
