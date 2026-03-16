// Source: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.
//
// Example:
// Input: s = "bcabc"
// Output: "abc"
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters.
//
//
//  
// Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/
//

/**
 * @param {string} s
 * @return {string}
 */
var smallestSubsequence = function(s) {
    const lastOccurrence = {};
    for (let i = 0; i < s.length; i++) {
        lastOccurrence[s[i]] = i;
    }
    const stack = [];
    const seen = new Set();
    for (let i = 0; i < s.length; i++) {
        const char = s[i];
            
        if (!seen.has(char)) {
            while (stack.length > 0 && char < stack[stack.length - 1] && i < lastOccurrence[stack[stack.length - 1]]) {
                seen.delete(stack.pop());
            }
            stack.push(char);
            seen.add(char);
        }
    }
    return stack.join('');
    
};
