// Source: https://leetcode.com/problems/add-to-array-form-of-integer/   |   Difficulty: Easy
//
// Problem Description:
// The array-form of an integer num is an array representing its digits in left to right order.
//
//
// 	For example, for num = 1321, the array form is [1,3,2,1].
//
//
// Given num, the array-form of an integer, and an integer k, return the array-form of the integer num + k.
//
// Example:
// Input: num = [1,2,0,0], k = 34
// Output: [1,2,3,4]
// Explanation: 1200 + 34 = 1234
//
// Constraints:
// 1 <= num.length <= 104
// 	0 <= num[i] <= 9
// 	num does not contain any leading zeros except for the zero itself.
// 	1 <= k <= 104
//

/**
 * @param {number[]} num
 * @param {number} k
 * @return {number[]}
 */
var addToArrayForm = function(num, k) {
    const result = [];
    let carry = 0;
    let i = num.length - 1;
    while (i >= 0 || k > 0 || carry > 0) {
        let sum = carry;
        if (i >= 0) {
            sum += num[i];
            i--;
        }
        if (k > 0) {
            sum += k % 10;
            k = Math.floor(k / 10);
        }
        carry = Math.floor(sum / 10);
        result.push(sum % 10);
    }
    result.reverse();
    return result;
};