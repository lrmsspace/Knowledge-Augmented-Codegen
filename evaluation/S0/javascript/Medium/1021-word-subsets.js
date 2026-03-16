// Source: https://leetcode.com/problems/word-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given two string arrays words1 and words2.
//
// A string b is a subset of string a if every letter in b occurs in a including multiplicity.
//
//
// 	For example, "wrr" is a subset of "warrior" but is not a subset of "world".
//
//
// A string a from words1 is universal if for every string b in words2, b is a subset of a.
//
// Return an array of all the universal strings in words1. You may return the answer in any order.
//
// Example:
// Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
//
// Output: ["facebook","google","leetcode"]
//
// Constraints:
// 1 <= words1.length, words2.length <= 104
// 	1 <= words1[i].length, words2[i].length <= 10
// 	words1[i] and words2[i] consist only of lowercase English letters.
// 	All the strings of words1 are unique.
//

/**
 * @param {string[]} words1
 * @param {string[]} words2
 * @return {string[]}
 */
var wordSubsets = function(words1, words2) {
    const maxFreq = Array(26).fill(0);
    for (const b of words2) {
        const freq = Array(26).fill(0);
        for (const ch of b) {
            freq[ch.charCodeAt(0) - 97]++;
        }
        for (let i = 0; i < 26; i++) {
            maxFreq[i] = Math.max(maxFreq[i], freq[i]);
        }
    }    

    const result = [];
    for (const a of words1) {
        const freq = Array(26).fill(0);
        for (const ch of a) {
            freq[ch.charCodeAt(0) - 97]++;
        }
        let isUniversal = true;
        for (let i = 0; i < 26; i++) {
            if (freq[i] < maxFreq[i]) {
                isUniversal = false;
                break;
            }
        }
        if (isUniversal) {
            result.push(a);
        }
    }
    return result;
};              