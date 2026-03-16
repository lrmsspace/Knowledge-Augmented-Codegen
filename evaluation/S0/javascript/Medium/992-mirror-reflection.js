// Source: https://leetcode.com/problems/mirror-reflection/   |   Difficulty: Medium
//
// Problem Description:
// There is a special square room with mirrors on each of the four walls. Except for the southwest corner, there are receptors on each of the remaining corners, numbered 0, 1, and 2.
//
// The square room has walls of length p and a laser ray from the southwest corner first meets the east wall at a distance q from the 0th receptor.
//
// Given the two integers p and q, return the number of the receptor that the ray meets first.
//
// The test cases are guaranteed so that the ray will meet a receptor eventually.
//
// Example:
// Input: p = 2, q = 1
// Output: 2
// Explanation: The ray meets receptor 2 the first time it gets reflected back to the left wall.
//
// Constraints:
// 1 <= q <= p <= 1000
//

/**
 * @param {number} p
 * @param {number} q
 * @return {number}
 */
var mirrorReflection = function(p, q) {
    const gcd = (a, b) => {
        if (b === 0) return a;
        return gcd(b, a % b);
    };

    const lcm = (a, b) => (a * b) / gcd(a, b);

    const l = lcm(p, q);
    const m = l / q;
    const n = l / p;

    if (m % 2 === 0 && n % 2 === 1) return 0;
    if (m % 2 === 1 && n % 2 === 1) return 1;
    if (m % 2 === 1 && n % 2 === 0) return 2;
};  