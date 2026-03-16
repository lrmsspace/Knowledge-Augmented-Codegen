// Source: https://leetcode.com/problems/smallest-integer-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer k, you need to find the length of the smallest positive integer n such that n is divisible by k, and n only contains the digit 1.
//
// Return the length of n. If there is no such n, return -1.
//
// Note: n may not fit in a 64-bit signed integer.
//
// Example:
// Input: k = 1
// Output: 1
// Explanation: The smallest answer is n = 1, which has length 1.
//
// Constraints:
// 1 <= k <= 105
//

/**
 * @param {number} k
 * @return {number}
 */
var smallestRepunitDivByK = function(k) {
    if (k % 2 === 0 || k % 5 === 0) return -1;
    let remainder = 0;
    for (let length = 1; length <= k; length++) {
        remainder = (remainder * 10 + 1) % k;
        if (remainder === 0) return length;
    }
    return -1;
        
};
