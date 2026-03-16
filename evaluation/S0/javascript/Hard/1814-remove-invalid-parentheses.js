// Source: https://leetcode.com/problems/remove-invalid-parentheses/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.
//
// Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.
//
// Example:
// Input: s = "()())()"
// Output: ["(())()","()()()"]
//
// Constraints:
// 1 <= s.length <= 25
// 	s consists of lowercase English letters and parentheses '(' and ')'.
// 	There will be at most 20 parentheses in s.
//

/**
 * @param {string} s
 * @return {string[]}
 */
var removeInvalidParentheses = function(s) {
    const result = new Set();
    const queue = [s];
    let found = false;
    while (queue.length > 0) {
        const current = queue.shift();
        if (isValid(current)) {
            result.add(current);
            found = true;
        }
        if (found) {
            continue;
        }
        for (let i = 0; i < current.length; i++) {
            if (current[i] === '(' || current[i] === ')') {
                const next = current.substring(0, i) + current.substring(i + 1);
                queue.push(next);
            }
        }
    }
    return Array.from(result);  
};
