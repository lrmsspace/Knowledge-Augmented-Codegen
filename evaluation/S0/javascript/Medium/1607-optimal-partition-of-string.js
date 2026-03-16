// Source: https://leetcode.com/problems/optimal-partition-of-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, partition the string into one or more substrings such that the characters in each substring are unique. That is, no letter appears in a single substring more than once.
//
// Return the minimum number of substrings in such a partition.
//
// Note that each character should belong to exactly one substring in a partition.
//
// Example:
// Input: s = "abacaba"
// Output: 4
// Explanation:
// Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
// It can be shown that 4 is the minimum number of substrings needed.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only English lowercase letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var partitionString = function(s) {
    let count = 1;
    const seen = new Set();
    for (const char of s) {
        if (seen.has(char)) {
            count++;
            seen.clear();
        }
        seen.add(char);
    }
    return count;
};