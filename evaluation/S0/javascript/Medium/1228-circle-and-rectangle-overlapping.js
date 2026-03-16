// Source: https://leetcode.com/problems/circle-and-rectangle-overlapping/   |   Difficulty: Medium
//
// Problem Description:
// You are given a circle represented as (radius, xCenter, yCenter) and an axis-aligned rectangle represented as (x1, y1, x2, y2), where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the rectangle.
//
// Return true if the circle and rectangle are overlapped otherwise return false. In other words, check if there is any point (xi, yi) that belongs to the circle and the rectangle at the same time.
//
// Example:
// Input: radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
// Output: true
// Explanation: Circle and rectangle share the point (1,0).
//
// Constraints:
// 1 <= radius <= 2000
// 	-104 <= xCenter, yCenter <= 104
// 	-104 <= x1 < x2 <= 104
// 	-104 <= y1 < y2 <= 104
//

/**
 * @param {number} radius
 * @param {number} xCenter
 * @param {number} yCenter
 * @param {number} x1
 * @param {number} y1
 * @param {number} x2
 * @param {number} y2
 * @return {boolean}
 */
var checkOverlap = function(radius, xCenter, yCenter, x1, y1, x2, y2) {
    // Find the closest point on the rectangle to the circle's center
    const closestX = Math.max(x1, Math.min(xCenter, x2));
    const closestY = Math.max(y1, Math.min(yCenter, y2));
    // Calculate the distance between the circle's center and this closest point
    const distanceX = xCenter - closestX;
    const distanceY = yCenter - closestY;
    // Check if the distance is less than or equal to the radius
    return (distanceX * distanceX + distanceY * distanceY) <= (radius * radius);
        
};
