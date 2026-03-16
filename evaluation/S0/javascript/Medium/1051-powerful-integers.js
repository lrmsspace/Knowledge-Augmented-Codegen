// Source: https://leetcode.com/problems/powerful-integers/   |   Difficulty: Medium
//
// Problem Description:
// Given three integers x, y, and bound, return a list of all the powerful integers that have a value less than or equal to bound.
//
// An integer is powerful if it can be represented as xi + yj for some integers i >= 0 and j >= 0.
//
// You may return the answer in any order. In your answer, each value should occur at most once.
//
// Example:
// Input: x = 2, y = 3, bound = 10
// Output: [2,3,4,5,7,9,10]
// Explanation:
// 2 = 20 + 30
// 3 = 21 + 30
// 4 = 20 + 31
// 5 = 21 + 31
// 7 = 22 + 31
// 9 = 23 + 30
// 10 = 20 + 32
//
// Constraints:
// 1 <= x, y <= 100
// 	0 <= bound <= 106
//

/**
 * @param {number} x
 * @param {number} y
 * @param {number} bound
 * @return {number[]}
 */
var powerfulIntegers = function(x, y, bound) {
    
    const powerfulInts = new Set();
    for (let i = 0; i <= Math.log(bound) / Math.log(x); i++) {
        for (let j = 0; j <= Math.log(bound) / Math.log(y); j++) {
            const val = Math.pow(x, i) + Math.pow(y, j);
            if (val <= bound) {
                powerfulInts.add(val);
            }
            if (y === 1) break;
        }
        if (x === 1) break;
    }
    return Array.from(powerfulInts);
    
};
