// Source: https://leetcode.com/problems/next-greater-element-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
//
// Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
//
// Example:
// Input: n = 12
// Output: 21
//
// Constraints:
// 1 <= n <= 231 - 1
//

/**
 * @param {number} n
 * @return {number}
 */
var nextGreaterElement = function(n) {
    const digits = n.toString().split('').map(Number);
    let i = digits.length - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) {
        i--;
    }
    if (i === -1) return -1;

    let j = digits.length - 1;

    while (digits[j] <= digits[i]) {
        j--;
    }
    [digits[i], digits[j]] = [digits[j], digits[i]];

    let left = i + 1;
    let right = digits.length - 1;
    while (left < right) {
        [digits[left], digits[right]] = [digits[right], digits[left]];
        left++;
        right--;
    }
    const result = Number(digits.join(''));
    return result <= 0x7FFFFFFF ? result : -1;
};
