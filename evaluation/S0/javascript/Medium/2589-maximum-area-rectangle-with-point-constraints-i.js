// Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array points where points[i] = [xi, yi] represents the coordinates of a point on an infinite plane.
//
// Your task is to find the maximum area of a rectangle that:
//
//
// 	Can be formed using four of these points as its corners.
// 	Does not contain any other point inside or on its border.
// 	Has its edges parallel to the axes.
//
//
// Return the maximum area that you can obtain or -1 if no such rectangle is possible.
//
// Example:
// Input: points = [[1,1],[1,3],[3,1],[3,3]]
//
// Output: 4
//
// Explanation:
//
//
//
// We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border. Hence, the maximum possible area would be 4.
//
// Constraints:
// 1 <= points.length <= 10
// 	points[i].length == 2
// 	0 <= xi, yi <= 100
// 	All the given points are unique.
//

/**
 * @param {number[][]} points
 * @return {number}
 */
var maxRectangleArea = function(points) {
    const pointSet = new Set(points.map(point => point.join(',')));
    let maxArea = -1;
    const n = points.length;
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            const [x1, y1] = points[i];
            const [x2, y2] = points[j];
            if (x1 !== x2 && y1 !== y2) {
                if (pointSet.has(`${x1},${y2}`) && pointSet.has(`${x2},${y1}`)) {
                    let valid = true;
                    for (const [x, y] of points) {
                        if ((x > Math.min(x1, x2) && x < Math.max(x1, x2)) &&
                            (y > Math.min(y1, y2) && y < Math.max(y1, y2))) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        const area = Math.abs(x2 - x1) * Math.abs(y2 - y1);
                        maxArea = Math.max(maxArea, area);
                    }
                }
            }
        }
    }
    return maxArea;
};