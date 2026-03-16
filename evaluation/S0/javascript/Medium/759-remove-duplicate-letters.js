// Source: https://leetcode.com/problems/remove-duplicate-letters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
//
// Example:
// Input: s = "bcabc"
// Output: "abc"
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
//
//
//  
// Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
//

/**
 * @param {string} s
 * @return {string}
 */
var removeDuplicateLetters = function(s) {
    const lastOccurrence = {};      
    for (let i = 0; i < s.length; i++) {
        lastOccurrence[s[i]] = i;
    }
    const stack = [];
    const inStack = new Set();
    for (let i = 0; i < s.length; i++) {
        const char = s[i];
        if (inStack.has(char)) continue;
        while (stack.length > 0 && char < stack[stack.length - 1] && i < lastOccurrence[stack[stack.length - 1]]) {
            inStack.delete(stack.pop());
        }
        stack.push(char);
        inStack.add(char);
    }
    return stack.join('');  
};
