// Source: https://leetcode.com/problems/number-of-matching-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an array of strings words, return the number of words[i] that is a subsequence of s.
//
// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
//
// 	For example, "ace" is a subsequence of "abcde".
//
// Example:
// Input: s = "abcde", words = ["a","bb","acd","ace"]
// Output: 3
// Explanation: There are three strings in words that are a subsequence of s: "a", "acd", "ace".
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	1 <= words.length <= 5000
// 	1 <= words[i].length <= 50
// 	s and words[i] consist of only lowercase English letters.
//

/**
 * @param {string} s
 * @param {string[]} words
 * @return {number}
 */
var numMatchingSubseq = function(s, words) {
    const charIndices = {};
    for (let i = 0; i < s.length; i++) {
        const char = s[i];
        if (!charIndices[char]) {
            charIndices[char] = [];
        }
        charIndices[char].push(i);
    }

    const binarySearch = (arr, target) => {
        let left = 0;
        let right = arr.length;
        while (left < right) {
            const mid = Math.floor((left + right) / 2);
            if (arr[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    };

    let count = 0;
    for (const word of words) {
        let prevIndex = -1;
        let isSubsequence = true;
        for (const char of word) {
            if (!charIndices[char]) {
                isSubsequence = false;
                break;
            }
            const indices = charIndices[char];
            const nextIndex = binarySearch(indices, prevIndex);
            if (nextIndex === indices.length) {
                isSubsequence = false;
                break;
            }
            prevIndex = indices[nextIndex];
        }
        if (isSubsequence) {
            count++;
        }
    }
    return count;
};  