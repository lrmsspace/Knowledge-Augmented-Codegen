// Source: https://leetcode.com/problems/find-all-anagrams-in-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.
//
// Example:
// Input: s = "cbaebabacd", p = "abc"
// Output: [0,6]
// Explanation:
// The substring with start index = 0 is "cba", which is an anagram of "abc".
// The substring with start index = 6 is "bac", which is an anagram of "abc".
//
// Constraints:
// 1 <= s.length, p.length <= 3 * 104
// 	s and p consist of lowercase English letters.
//

/**
 * @param {string} s
 * @param {string} p
 * @return {number[]}
 */
var findAnagrams = function(s, p) {
    const result = [];
    const pCount = Array(26).fill(0);
    const sCount = Array(26).fill(0);
    const aCharCode = 'a'.charCodeAt(0);

    for (let i = 0; i < p.length; i++) {
        pCount[p.charCodeAt(i) - aCharCode]++;
        sCount[s.charCodeAt(i) - aCharCode]++;
    }

    if (pCount.toString() === sCount.toString()) {
        result.push(0);
    }

    for (let i = p.length; i < s.length; i++) {
        sCount[s.charCodeAt(i) - aCharCode]++;
        sCount[s.charCodeAt(i - p.length) - aCharCode]--;

        if (pCount.toString() === sCount.toString()) {
            result.push(i - p.length + 1);
        }
    }

    return result;
};