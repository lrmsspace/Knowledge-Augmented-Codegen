// Source: https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called almost equal to y if you can change at most one character in x to make it identical to y.
//
// A sequence of indices seq is called valid if:
//
//
// 	The indices are sorted in ascending order.
// 	Concatenating the characters at these indices in word1 in the same order results in a string that is almost equal to word2.
//
//
// Return an array of size word2.length representing the lexicographically smallest valid sequence of indices. If no such sequence of indices exists, return an empty array.
//
// Note that the answer must represent the lexicographically smallest array, not the corresponding string formed by those indices.
//
// Example:
// Input: word1 = "vbcca", word2 = "abc"
//
// Output: [0,1,2]
//
// Explanation:
//
// The lexicographically smallest valid sequence of indices is [0, 1, 2]:
//
//
// 	Change word1[0] to 'a'.
// 	word1[1] is already 'b'.
// 	word1[2] is already 'c'.
//
// Constraints:
// 1 <= word2.length < word1.length <= 3 * 105
// 	word1 and word2 consist only of lowercase English letters.
//

/**
 * @param {string} word1
 * @param {string} word2
 * @return {number[]}
 */
var validSequence = function(word1, word2) {
    const indices = [];
    let mismatchIndex = -1;
    for (let i = 0, j = 0; i < word1.length && j < word2.length; i++) {
        if (word1[i] === word2[j]) {
            indices.push(i);
            j++;
        } else if (mismatchIndex === -1) {
            mismatchIndex = i;
        }
    }
    if (indices.length === word2.length) {
        return indices;
    }
    if (mismatchIndex !== -1) {
        indices.unshift(mismatchIndex);
        return indices;
    }
    return [];
};
