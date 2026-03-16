// Source: https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/   |   Difficulty: Medium
//
// Problem Description:
// Given 3 positives numbers a, b and c. Return the minimum flips required in some bits of a and b to make ( a OR b == c ). (bitwise OR operation).
// Flip operation consists of change any single bit 1 to 0 or change the bit 0 to 1 in their binary representation.
//
// Example:
// Input: a = 2, b = 6, c = 5
// Output: 3
// Explanation: After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)
//
// Constraints:
// 1 <= a <= 10^9
// 	1 <= b <= 10^9
// 	1 <= c <= 10^9
//

/**
 * @param {number} a
 * @param {number} b
 * @param {number} c
 * @return {number}
 */
var minFlips = function(a, b, c) {
    
    let flips = 0;
    for (let i = 0; i < 32; i++) {
        const bitA = (a >> i) & 1;
        const bitB = (b >> i) & 1;
        const bitC = (c >> i) & 1;
        if (bitC === 0) {
            flips += bitA + bitB;
        } else {
            if (bitA === 0 && bitB === 0) {
                flips += 1;
            }
        }
    }
    return flips;
    
};
