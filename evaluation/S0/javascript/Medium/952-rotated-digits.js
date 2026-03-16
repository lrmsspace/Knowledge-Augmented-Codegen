// Source: https://leetcode.com/problems/rotated-digits/   |   Difficulty: Medium
//
// Problem Description:
// An integer x is a good if after rotating each digit individually by 180 degrees, we get a valid number that is different from x. Each digit must be rotated - we cannot choose to leave it alone.
//
// A number is valid if each digit remains a digit after rotation. For example:
//
//
// 	0, 1, and 8 rotate to themselves,
// 	2 and 5 rotate to each other (in this case they are rotated in a different direction, in other words, 2 or 5 gets mirrored),
// 	6 and 9 rotate to each other, and
// 	the rest of the numbers do not rotate to any other number and become invalid.
//
//
// Given an integer n, return the number of good integers in the range [1, n].
//
// Example:
// Input: n = 10
// Output: 4
// Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
// Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
//
// Constraints:
// 1 <= n <= 104
//

/**
 * @param {number} n
 * @return {number}
 */
var rotatedDigits = function(n) {
    let count = 0;
    const goodDigits = new Set(['2', '5', '6', '9']);
    const validDigits = new Set(['0', '1', '8', '2', '5', '6', '9']);
    for (let i = 1; i <= n; i++) {
        const str = i.toString();
        let isValid = true;
        let hasGoodDigit = false;
        for (const char of str) {
            if (!validDigits.has(char)) {
                isValid = false;
                break;
            }
            if (goodDigits.has(char)) {
                hasGoodDigit = true;
            }
        }
        if (isValid && hasGoodDigit) {
            count++;
        }
    }
    return count;
};