// Source: https://leetcode.com/problems/categorize-box-according-to-criteria/   |   Difficulty: Easy
//
// Problem Description:
// Given four integers length, width, height, and mass, representing the dimensions and mass of a box, respectively, return a string representing the category of the box.
//
//
// 	The box is "Bulky" if:
//
// 	
// 		Any of the dimensions of the box is greater or equal to 104.
// 		Or, the volume of the box is greater or equal to 109.
// 	
// 	
// 	If the mass of the box is greater or equal to 100, it is "Heavy".
// 	If the box is both "Bulky" and "Heavy", then its category is "Both".
// 	If the box is neither "Bulky" nor "Heavy", then its category is "Neither".
// 	If the box is "Bulky" but not "Heavy", then its category is "Bulky".
// 	If the box is "Heavy" but not "Bulky", then its category is "Heavy".
//
//
// Note that the volume of the box is the product of its length, width and height.
//
// Example:
// Input: length = 1000, width = 35, height = 700, mass = 300
// Output: "Heavy"
// Explanation: 
// None of the dimensions of the box is greater or equal to 104. 
// Its volume = 24500000 <= 109. So it cannot be categorized as "Bulky".
// However mass >= 100, so the box is "Heavy".
// Since the box is not "Bulky" but "Heavy", we return "Heavy".
//
// Constraints:
// 1 <= length, width, height <= 105
// 	1 <= mass <= 103
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
 * @param {number} length
 * @param {number} width
 * @param {number} height
 * @param {number} mass
 * @return {string}
 */
var categorizeBox = function(length, width, height, mass) {
    const isBulky = length >= 10000 || width >= 10000 || height >= 10000 || (length * width * height) >= 1e9;
    const isHeavy = mass >= 100;
    if (isBulky && isHeavy) {
        return "Both";
    } else if (isBulky) {
        return "Bulky";
    } else if (isHeavy) {
        return "Heavy";
    } else {
        return "Neither";
    }
};