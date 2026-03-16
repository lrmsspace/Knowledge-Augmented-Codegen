// Source: https://leetcode.com/problems/water-and-jug-problem/   |   Difficulty: Medium
//
// Problem Description:
// You are given two jugs with capacities x liters and y liters. You have an infinite water supply. Return whether the total amount of water in both jugs may reach target using the following operations:
//
//
// 	Fill either jug completely with water.
// 	Completely empty either jug.
// 	Pour water from one jug into another until the receiving jug is full, or the transferring jug is empty.
//
// Example:
// Input:   x = 3, y = 5, target = 4 
//
// Output:   true 
//
// Explanation:
//
// Follow these steps to reach a total of 4 liters:
//
//
// 	Fill the 5-liter jug (0, 5).
// 	Pour from the 5-liter jug into the 3-liter jug, leaving 2 liters (3, 2).
// 	Empty the 3-liter jug (0, 2).
// 	Transfer the 2 liters from the 5-liter jug to the 3-liter jug (2, 0).
// 	Fill the 5-liter jug again (2, 5).
// 	Pour from the 5-liter jug into the 3-liter jug until the 3-liter jug is full. This leaves 4 liters in the 5-liter jug (3, 4).
// 	Empty the 3-liter jug. Now, you have exactly 4 liters in the 5-liter jug (0, 4).
//
//
// Reference: The Die Hard example.
//
// Constraints:
// 1 <= x, y, target <= 103
//

/**
 * @param {number} x
 * @param {number} y
 * @param {number} target
 * @return {boolean}
 */
var canMeasureWater = function(x, y, target) {
    if (x + y < target) return false;
    const gcd = (a, b) => {
        while (b !== 0) {
            [a, b] = [b, a % b];
        }
        return a;
    };
    return target % gcd(x, y) === 0;
};
