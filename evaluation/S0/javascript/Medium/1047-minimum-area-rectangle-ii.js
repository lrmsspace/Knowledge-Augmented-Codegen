// Source: https://leetcode.com/problems/minimum-area-rectangle-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of points in the X-Y plane points where points[i] = [xi, yi].
//
// Return the minimum area of any rectangle formed from these points, with sides not necessarily parallel to the X and Y axes. If there is not any such rectangle, return 0.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: points = [[1,2],[2,1],[1,0],[0,1]]
// Output: 2.00000
// Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.
//
// Constraints:
// 1 <= points.length <= 50
// 	points[i].length == 2
// 	0 <= xi, yi <= 4 * 104
// 	All the given points are unique.
//

/**
 * @param {number[][]} points
 * @return {number}
 */
var minAreaFreeRect = function(points) {
    
    const n = points.length;
    let minArea = Infinity;
    const pointSet = new Set(points.map(([x, y]) => `${x},${y}`));

    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            for (let k = 0; k < n; k++) {
                if (i !== j && i !== k && j !== k) {
                    const [x1, y1] = points[i];
                    const [x2, y2] = points[j];
                    const [x3, y3] = points[k];
                    const dotProduct = (x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1);
                    if (dotProduct === 0) {
                        const x4 = x2 + x3 - x1;
                        const y4 = y2 + y3 - y1;
                        if (pointSet.has(`${x4},${y4}`)) {
                            const area = Math.hypot(x2 - x1, y2 - y1) * Math.hypot(x3 - x1, y3 - y1);
                            minArea = Math.min(minArea, area);
                        }
                    }
                }
            }
        }
    }
    return minArea === Infinity ? 0 : minArea;
    
};
