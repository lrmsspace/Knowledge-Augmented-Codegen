// Source: https://leetcode.com/problems/add-digits/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer num, repeatedly add all its digits until the result has only one digit, and return it.
//
// Example:
// Input: num = 38
// Output: 2
// Explanation: The process is
// 38 --> 3 + 8 --> 11
// 11 --> 1 + 1 --> 2 
// Since 2 has only one digit, return it.
//
// Constraints:
// 0 <= num <= 231 - 1
//
//
//  
// Follow up: Could you do it without any loop/recursion in O(1) runtime?
//

/**
 * @param {number} num
 * @return {number}
 */
var addDigits = function(num) {
    if (num === 0) return 0;
    return 1 + (num - 1) % 9;   
};
