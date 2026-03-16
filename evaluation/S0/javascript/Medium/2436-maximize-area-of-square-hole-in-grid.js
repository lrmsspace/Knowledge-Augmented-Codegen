// Source: https://leetcode.com/problems/maximize-area-of-square-hole-in-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given the two integers, n and m and two integer arrays, hBars and vBars. The grid has n + 2 horizontal and m + 2 vertical bars, creating 1 x 1 unit cells. The bars are indexed starting from 1.
//
// You can remove some of the bars in hBars from horizontal bars and some of the bars in vBars from vertical bars. Note that other bars are fixed and cannot be removed.
//
// Return an integer denoting the maximum area of a square-shaped hole in the grid, after removing some bars (possibly none).
//
// Example:
// Input: n = 2, m = 1, hBars = [2,3], vBars = [2]
//
// Output: 4
//
// Explanation:
//
// The left image shows the initial grid formed by the bars. The horizontal bars are [1,2,3,4], and the vertical bars are [1,2,3].
//
// One way to get the maximum square-shaped hole is by removing horizontal bar 2 and vertical bar 2.
//
// Constraints:
// 1 <= n <= 109
// 	1 <= m <= 109
// 	1 <= hBars.length <= 100
// 	2 <= hBars[i] <= n + 1
// 	1 <= vBars.length <= 100
// 	2 <= vBars[i] <= m + 1
// 	All values in hBars are distinct.
// 	All values in vBars are distinct.
//

/**
 * @param {number} n
 * @param {number} m
 * @param {number[]} hBars
 * @param {number[]} vBars
 * @return {number}
 */
var maximizeSquareHoleArea = function(n, m, hBars, vBars) {
    hBars.push(1);
    hBars.push(n + 2);
    vBars.push(1);
    vBars.push(m + 2);
    hBars.sort((a, b) => a - b);
    vBars.sort((a, b) => a - b);
    let maxHGap = 0;
    for (let i = 1; i < hBars.length; i++) {
        maxHGap = Math.max(maxHGap, hBars[i] - hBars[i - 1]);
    }
    let maxVGap = 0;
    for (let i = 1; i < vBars.length; i++) {
        maxVGap = Math.max(maxVGap, vBars[i] - vBars[i - 1]);
    }
    const maxSide = Math.min(maxHGap - 1, maxVGap - 1);
    return maxSide * maxSide;
};