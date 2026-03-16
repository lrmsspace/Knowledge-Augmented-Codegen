// Source: https://leetcode.com/problems/longest-substring-of-one-repeating-character/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s. You are also given a 0-indexed string queryCharacters of length k and a 0-indexed array of integer indices queryIndices of length k, both of which are used to describe k queries.
//
// The ith query updates the character in s at index queryIndices[i] to the character queryCharacters[i].
//
// Return an array lengths of length k where lengths[i] is the length of the longest substring of s consisting of only one repeating character after the ith query is performed.
//
// Example:
// Input: s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
// Output: [3,3,4]
// Explanation: 
// - 1st query updates s = "bbbacc". The longest substring consisting of one repeating character is "bbb" with length 3.
// - 2nd query updates s = "bbbccc". 
//   The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
// - 3rd query updates s = "bbbbcc". The longest substring consisting of one repeating character is "bbbb" with length 4.
// Thus, we return [3,3,4].
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	k == queryCharacters.length == queryIndices.length
// 	1 <= k <= 105
// 	queryCharacters consists of lowercase English letters.
// 	0 <= queryIndices[i] < s.length
//

/**
 * @param {string} s
 * @param {string} queryCharacters
 * @param {number[]} queryIndices
 * @return {number[]}
 */
var longestRepeating = function(s, queryCharacters, queryIndices) {
    const n = s.length;
    const k = queryCharacters.length;
    const chars = s.split('');
    const lengths = new Array(n).fill(1);
    for (let i = 1; i < n; i++) {
        if (chars[i] === chars[i - 1]) {
            lengths[i] = lengths[i - 1] + 1;
        }
    }
    const result = [];
    for (let i = 0; i < k; i++) {
        const index = queryIndices[i];
        const newChar = queryCharacters[i];
        chars[index] = newChar;
        lengths[index] = 1;
        if (index > 0 && chars[index] === chars[index - 1]) {
            lengths[index] = lengths[index - 1] + 1;
        }
        if (index < n - 1 && chars[index] === chars[index + 1]) {
            lengths[index] = Math.max(lengths[index], lengths[index + 1] + 1);
        }
        result.push(Math.max(...lengths));
    }
    return result;  
};
