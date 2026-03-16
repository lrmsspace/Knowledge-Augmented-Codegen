// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-x-and-y-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers x and y.
//
// In one operation, you can do one of the four following operations:
//
//
// 	Divide x by 11 if x is a multiple of 11.
// 	Divide x by 5 if x is a multiple of 5.
// 	Decrement x by 1.
// 	Increment x by 1.
//
//
// Return the minimum number of operations required to make  x and y equal.
//
// Example:
// Input: x = 26, y = 1
// Output: 3
// Explanation: We can make 26 equal to 1 by applying the following operations: 
// 1. Decrement x by 1
// 2. Divide x by 5
// 3. Divide x by 5
// It can be shown that 3 is the minimum number of operations required to make 26 equal to 1.
//
// Constraints:
// 1 <= x, y <= 104
//

/**
 * @param {number} x
 * @param {number} y
 * @return {number}
 */
var minimumOperationsToMakeEqual = function(x, y) {
    const queue = [];
    const visited = new Set();
    queue.push([x, 0]);
    visited.add(x);
    while (queue.length > 0) {
        const [current, steps] = queue.shift();
        if (current === y) {
            return steps;
        }
        if (current % 11 === 0 && !visited.has(current / 11)) {
            queue.push([current / 11, steps + 1]);
            visited.add(current / 11);
        }
        if (current % 5 === 0 && !visited.has(current / 5)) {
            queue.push([current / 5, steps + 1]);
            visited.add(current / 5);
        }
        if (!visited.has(current - 1)) {
            queue.push([current - 1, steps + 1]);
            visited.add(current - 1);
        }
        if (!visited.has(current + 1)) {
            queue.push([current + 1, steps + 1]);
            visited.add(current + 1);
        }
    }
    return -1;
};