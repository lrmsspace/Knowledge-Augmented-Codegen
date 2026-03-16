// Source: https://leetcode.com/problems/check-balanced-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string num consisting of only digits. A string of digits is called balanced if the sum of the digits at even indices is equal to the sum of digits at odd indices.
//
// Return true if num is balanced, otherwise return false.
//
// Example:
// Input: num = "1234"
//
// Output: false
//
// Explanation:
//
//
// 	The sum of digits at even indices is 1 + 3 == 4, and the sum of digits at odd indices is 2 + 4 == 6.
// 	Since 4 is not equal to 6, num is not balanced.
//
// Constraints:
// 2 <= num.length <= 100
// 	num consists of digits only
//

/**
 * @param {string} num
 * @return {boolean}
 */
var isBalanced = function(num) {
    let evenSum = 0;
    let oddSum = 0;
    for (let i = 0; i < num.length; i++) {
        if (i % 2 === 0) {
            evenSum += parseInt(num[i]);
        } else {
            oddSum += parseInt(num[i]);
        }
    }
    return evenSum === oddSum;
};