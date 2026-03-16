// Source: https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a parentheses string s containing only the characters '(' and ')'. A parentheses string is balanced if:
//
//
// 	Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
// 	Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.
//
//
// In other words, we treat '(' as an opening parenthesis and '))' as a closing parenthesis.
//
//
// 	For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.
//
//
// You can insert the characters '(' and ')' at any position of the string to balance it if needed.
//
// Return the minimum number of insertions needed to make s balanced.
//
// Example:
// Input: s = "(()))"
// Output: 1
// Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching. We need to add one more ')' at the end of the string to be "(())))" which is balanced.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of '(' and ')' only.
//

/**
 * @param {string} s
 * @return {number}
 */
var minInsertions = function(s) {
    let insertions = 0;
    let balance = 0; // Number of unmatched '('
    let i = 0;
    while (i < s.length) {
        if (s[i] === '(') {
            balance++;
            i++;
        } else {
            if (i + 1 < s.length && s[i + 1] === ')') {
                i += 2;
            } else {
                insertions++;
                i++;
            }
            if (balance > 0) {
                balance--;
            } else {
                insertions++;
            }
        }
    }
    insertions += balance * 2;
    return insertions;
};