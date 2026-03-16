// Source: https://leetcode.com/problems/a-number-after-a-double-reversal/   |   Difficulty: Easy
//
// Problem Description:
// Reversing an integer means to reverse all its digits.
//
//
// 	For example, reversing 2021 gives 1202. Reversing 12300 gives 321 as the leading zeros are not retained.
//
//
// Given an integer num, reverse num to get reversed1, then reverse reversed1 to get reversed2. Return true if reversed2 equals num. Otherwise return false.
//
// Example:
// Input: num = 526
// Output: true
// Explanation: Reverse num to get 625, then reverse 625 to get 526, which equals num.
//
// Constraints:
// 0 <= num <= 106
//

/**
 * @param {number} num
 * @return {boolean}
 */
var isSameAfterReversals = function(num) {
    if (num === 0) {
        return true;
    }
    const reverse = (n) => {
        let rev = 0;
        while (n > 0) {
            rev = rev * 10 + (n % 10);
            n = Math.floor(n / 10);
        }
        return rev;
    };
    const reversed1 = reverse(num);
    const reversed2 = reverse(reversed1);
    return reversed2 === num;
};