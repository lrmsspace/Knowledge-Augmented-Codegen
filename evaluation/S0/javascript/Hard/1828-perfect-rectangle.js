// Source: https://leetcode.com/problems/perfect-rectangle/   |   Difficulty: Hard
//
// Problem Description:
// Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
//
// Return true if all the rectangles together form an exact cover of a rectangular region.
//
// Example:
// Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
// Output: true
// Explanation: All 5 rectangles together form an exact cover of a rectangular region.
//
// Constraints:
// 1 <= rectangles.length <= 2 * 104
// 	rectangles[i].length == 4
// 	-105 <= xi < ai <= 105
// 	-105 <= yi < bi <= 105
//

/**
 * @param {number[][]} rectangles
 * @return {boolean}
 */
var isRectangleCover = function(rectangles) {
    let minX = Infinity, minY = Infinity, maxX = -Infinity, maxY = -Infinity;
    const points = new Set();
    let area = 0;
    for (let [x1, y1, x2, y2] of rectangles) {
        minX = Math.min(minX, x1);
        minY = Math.min(minY, y1);
        maxX = Math.max(maxX, x2);
        maxY = Math.max(maxY, y2);
        area += (x2 - x1) * (y2 - y1);
        const corners = [[x1, y1], [x1, y2], [x2, y1], [x2, y2]];
        for (let corner of corners) {
            const key = corner.join(',');
            if (points.has(key)) {
                points.delete(key);
            }
            else {                points.add(key);
            }
        }
    }
    const expectedArea = (maxX - minX) * (maxY - minY);
    return area === expectedArea && points.size === 4 && points.has(`${minX},${minY}`) && points.has(`${minX},${maxY}`) && points.has(`${maxX},${minY}`) && points.has(`${maxX},${maxY}`);  
};
