// Source: https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].
//
// Count the number of pairs of points (A, B), where
//
//
// 	A is on the upper left side of B, and
// 	there are no other points in the rectangle (or line) they make (including the border), except for the points A and B.
//
//
// Return the count.
//
// Example:
// Input: points = [[1,1],[2,2],[3,3]]
//
// Output: 0
//
// Explanation:
//
//
//
// There is no way to choose A and B such that A is on the upper left side of B.
//
// Constraints:
// 2 <= n <= 50
// 	points[i].length == 2
// 	0 <= points[i][0], points[i][1] <= 50
// 	All points[i] are distinct.
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
 * @param {number[][]} points
 * @return {number}
 */
var numberOfPairs = function(points) {
    let count = 0;
    for (let i = 0; i < points.length; i++) {
        for (let j = 0; j < points.length; j++) {
            if (i === j) continue;
            const [x1, y1] = points[i];
            const [x2, y2] = points[j];
            if (x1 < x2 && y1 > y2) {
                let valid = true;
                for (let k = 0; k < points.length; k++) {
                    if (k === i || k === j) continue;
                    const [x3, y3] = points[k];
                    if (x1 <= x3 && x3 <= x2 && y1 >= y3 && y3 >= y2) {
                        valid = false;
                        break;
                    }
                }
                if (valid) count++;
            }
        }
    }
    return count;
};
