// Source: https://leetcode.com/problems/add-strings/   |   Difficulty: Easy
//
// Problem Description:
// Given two non-negative integers, num1 and num2 represented as string, return the sum of num1 and num2 as a string.
//
// You must solve the problem without using any built-in library for handling large integers (such as BigInteger). You must also not convert the inputs to integers directly.
//
// Example:
// Input: num1 = "11", num2 = "123"
// Output: "134"
//
// Constraints:
// 1 <= num1.length, num2.length <= 104
// 	num1 and num2 consist of only digits.
// 	num1 and num2 don't have any leading zeros except for the zero itself.
//

/**
 * @param {string} num1
 * @param {string} num2
 * @return {string}
 */
var addStrings = function(num1, num2) {
    let i = num1.length - 1;
    let j = num2.length - 1;
    let carry = 0;
    let result = '';
    while (i >= 0 || j >= 0 || carry > 0) {
        const digit1 = i >= 0 ? parseInt(num1[i]) : 0;
        const digit2 = j >= 0 ? parseInt(num2[j]) : 0;
        const sum = digit1 + digit2 + carry;
        carry = Math.floor(sum / 10);
        result = (sum % 10) + result;
        i--;
        j--;
    }
    return result;
};