// Source: https://leetcode.com/problems/minimum-area-rectangle/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of points in the X-Y plane points where points[i] = [xi, yi].
//
// Return the minimum area of a rectangle formed from these points, with sides parallel to the X and Y axes. If there is not any such rectangle, return 0.
//
// Example:
// Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]
// Output: 4
//
// Constraints:
// 1 <= points.length <= 500
// 	points[i].length == 2
// 	0 <= xi, yi <= 4 * 104
// 	All the given points are unique.
//

/**
 * @param {number[][]} points
 * @return {number}
 */
var minAreaRect = function(points) {
    const pointSet = new Set(points.map(([x, y]) => `${x},${y}`));
    let minArea = Infinity;             
    const n = points.length;
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            const [x1, y1] = points[i];
            const [x2, y2] = points[j];
            if (x1 !== x2 && y1 !== y2) {
                if (pointSet.has(`${x1},${y2}`) && pointSet.has(`${x2},${y1}`)) {
                    const area = Math.abs(x2 - x1) * Math.abs(y2 - y1);
                    minArea = Math.min(minArea, area);
                }
            }
        }    
    }
    return minArea === Infinity ? 0 : minArea;
};
