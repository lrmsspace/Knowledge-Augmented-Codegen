// Source: https://leetcode.com/problems/convert-to-base-2/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return a binary string representing its representation in base -2.
//
// Note that the returned string should not have leading zeros unless the string is "0".
//
// Example:
// Input: n = 2
// Output: "110"
// Explantion: (-2)2 + (-2)1 = 2
//
// Constraints:
// 0 <= n <= 109
//

/**
 * @param {number} n
 * @return {string}
 */
var baseNeg2 = function(n) {
    
    if (n === 0) return "0";
    let result = "";
    while (n !== 0) {
        let remainder = n % -2;
        n = Math.floor(n / -2);
        if (remainder < 0) {
            remainder += 2;
            n += 1;
        }
        result = remainder.toString() + result;
    }
    return result;
    
};
