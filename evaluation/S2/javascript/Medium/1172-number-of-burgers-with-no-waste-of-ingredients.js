// Source: https://leetcode.com/problems/number-of-burgers-with-no-waste-of-ingredients/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers tomatoSlices and cheeseSlices. The ingredients of different burgers are as follows:
//
//
// 	Jumbo Burger: 4 tomato slices and 1 cheese slice.
// 	Small Burger: 2 Tomato slices and 1 cheese slice.
//
//
// Return [total_jumbo, total_small] so that the number of remaining tomatoSlices equal to 0 and the number of remaining cheeseSlices equal to 0. If it is not possible to make the remaining tomatoSlices and cheeseSlices equal to 0 return [].
//
// Example:
// Input: tomatoSlices = 16, cheeseSlices = 7
// Output: [1,6]
// Explantion: To make one jumbo burger and 6 small burgers we need 4*1 + 2*6 = 16 tomato and 1 + 6 = 7 cheese.
// There will be no remaining ingredients.
//
// Constraints:
// 0 <= tomatoSlices, cheeseSlices <= 107
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} tomatoSlices
 * @param {number} cheeseSlices
 * @return {number[]}
 */
var numOfBurgers = function(tomatoSlices, cheeseSlices) {
    const jumbo = tomatoSlices / 2 - cheeseSlices;
    const small = cheeseSlices - jumbo;
    if (jumbo < 0 || small < 0 || !Number.isInteger(jumbo) || !Number.isInteger(small)) {
        return [];
    }
    return [jumbo, small];
};
