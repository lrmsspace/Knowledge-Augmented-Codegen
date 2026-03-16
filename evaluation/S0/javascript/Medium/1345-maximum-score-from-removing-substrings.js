// Source: https://leetcode.com/problems/maximum-score-from-removing-substrings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and two integers x and y. You can perform two types of operations any number of times.
//
//
// 	Remove substring "ab" and gain x points.
//
// 	
// 		For example, when removing "ab" from "cabxbae" it becomes "cxbae".
// 	
// 	
// 	Remove substring "ba" and gain y points.
// 	
// 		For example, when removing "ba" from "cabxbae" it becomes "cabxe".
// 	
// 	
//
//
// Return the maximum points you can gain after applying the above operations on s.
//
// Example:
// Input: s = "cdbcbbaaabab", x = 4, y = 5
// Output: 19
// Explanation:
// - Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
// - Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
// - Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
// - Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
// Total score = 5 + 4 + 5 + 5 = 19.
//
// Constraints:
// 1 <= s.length <= 105
// 	1 <= x, y <= 104
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @param {number} x
 * @param {number} y
 * @return {number}
 */
var maximumGain = function(s, x, y) {
    let totalScore = 0;
    const firstPair = x >= y ? 'ab' : 'ba';
    const secondPair = x >= y ? 'ba' : 'ab';
    const firstScore = Math.max(x, y);
    const secondScore = Math.min(x, y);
    const stack1 = [];
    for (const char of s) {
        if (stack1.length > 0 && stack1[stack1.length - 1] === firstPair[0] && char === firstPair[1]) {
            stack1.pop();
            totalScore += firstScore;
        } else {
            stack1.push(char);
        }
    }
    const stack2 = [];
    for (const char of stack1) {
        if (stack2.length > 0 && stack2[stack2.length - 1] === secondPair[0] && char === secondPair[1]) {
            stack2.pop();
            totalScore += secondScore;
        } else {
            stack2.push(char);
        }
    }
    return totalScore;
};
