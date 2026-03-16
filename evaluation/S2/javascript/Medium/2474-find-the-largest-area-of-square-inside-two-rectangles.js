// Source: https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/   |   Difficulty: Medium
//
// Problem Description:
// There exist n rectangles in a 2D plane with edges parallel to the x and y axis. You are given two 2D integer arrays bottomLeft and topRight where bottomLeft[i] = [a_i, b_i] and topRight[i] = [c_i, d_i] represent the bottom-left and top-right coordinates of the ith rectangle, respectively.
//
// You need to find the maximum area of a square that can fit inside the intersecting region of at least two rectangles. Return 0 if such a square does not exist.
//
// Example:
// Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
//
// Output: 1
//
// Explanation:
//
// A square with side length 1 can fit inside either the intersecting region of rectangles 0 and 1 or the intersecting region of rectangles 1 and 2. Hence the maximum area is 1. It can be shown that a square with a greater side length can not fit inside any intersecting region of two rectangles.
//
// Constraints:
// n == bottomLeft.length == topRight.length
// 	2 <= n <= 103
// 	bottomLeft[i].length == topRight[i].length == 2
// 	1 <= bottomLeft[i][0], bottomLeft[i][1] <= 107
// 	1 <= topRight[i][0], topRight[i][1] <= 107
// 	bottomLeft[i][0] < topRight[i][0]
// 	bottomLeft[i][1] < topRight[i][1]
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
 * @param {number[][]} bottomLeft
 * @param {number[][]} topRight
 * @return {number}
 */
var largestSquareArea = function(bottomLeft, topRight) {
    let maxArea = 0;
    for (let i = 0; i < bottomLeft.length; i++) {
        for (let j = i + 1; j < bottomLeft.length; j++) {
            const xOverlap = Math.max(0, Math.min(topRight[i][0], topRight[j][0]) - Math.max(bottomLeft[i][0], bottomLeft[j][0]));
            const yOverlap = Math.max(0, Math.min(topRight[i][1], topRight[j][1]) - Math.max(bottomLeft[i][1], bottomLeft[j][1]));
            const sideLength = Math.min(xOverlap, yOverlap);
            maxArea = Math.max(maxArea, sideLength * sideLength);
        }
    }
    return maxArea;
};
