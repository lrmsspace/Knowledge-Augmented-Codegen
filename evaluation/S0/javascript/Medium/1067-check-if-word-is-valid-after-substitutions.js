// Source: https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, determine if it is valid.
//
// A string s is valid if, starting with an empty string t = "", you can transform t into s after performing the following operation any number of times:
//
//
// 	Insert string "abc" into any position in t. More formally, t becomes tleft + "abc" + tright, where t == tleft + tright. Note that tleft and tright may be empty.
//
//
// Return true if s is a valid string, otherwise, return false.
//
// Example:
// Input: s = "aabcbc"
// Output: true
// Explanation:
// "" -> "abc" -> "aabcbc"
// Thus, "aabcbc" is valid.
//
// Constraints:
// 1 <= s.length <= 2 * 104
// 	s consists of letters 'a', 'b', and 'c'
//

/**
 * @param {string} s
 * @return {boolean}
 */
var isValid = function(s) {
    const stack = [];
    for (const char of s) {
        if (char === 'c') {
            if (stack.length < 2 || stack.pop() !== 'b' || stack.pop() !== 'a') {
                return false;
            }
        }
        else {
            stack.push(char);
        }
    }
    return stack.length === 0;  
                    
};
