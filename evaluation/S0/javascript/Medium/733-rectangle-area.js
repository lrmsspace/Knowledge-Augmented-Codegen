// Source: https://leetcode.com/problems/rectangle-area/   |   Difficulty: Medium
//
// Problem Description:
// Given the coordinates of two rectilinear rectangles in a 2D plane, return the total area covered by the two rectangles.
//
// The first rectangle is defined by its bottom-left corner (ax1, ay1) and its top-right corner (ax2, ay2).
//
// The second rectangle is defined by its bottom-left corner (bx1, by1) and its top-right corner (bx2, by2).
//
// Example:
// Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
// Output: 45
//
// Constraints:
// -104 <= ax1 <= ax2 <= 104
// 	-104 <= ay1 <= ay2 <= 104
// 	-104 <= bx1 <= bx2 <= 104
// 	-104 <= by1 <= by2 <= 104
//

/**
 * @param {number} ax1
 * @param {number} ay1
 * @param {number} ax2
 * @param {number} ay2
 * @param {number} bx1
 * @param {number} by1
 * @param {number} bx2
 * @param {number} by2
 * @return {number}
 */
var computeArea = function(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2) {
    const areaA = (ax2 - ax1) * (ay2 - ay1);
    const areaB = (bx2 - bx1) * (by2 - by1);

    const overlapWidth = Math.max(0, Math.min(ax2, bx2) - Math.max(ax1, bx1));
    const overlapHeight = Math.max(0, Math.min(ay2, by2) - Math.max(ay1, by1));
    const overlapArea = overlapWidth * overlapHeight;

    return areaA + areaB - overlapArea;
};  