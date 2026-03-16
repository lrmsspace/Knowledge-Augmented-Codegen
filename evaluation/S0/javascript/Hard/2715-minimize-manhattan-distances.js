// Source: https://leetcode.com/problems/minimize-manhattan-distances/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array points representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].
//
// The distance between two points is defined as their Manhattan distance.
//
// Return the minimum possible value for maximum distance between any two points by removing exactly one point.
//
// Example:
// Input: points = [[3,10],[5,15],[10,2],[4,4]]
//
// Output: 12
//
// Explanation:
//
// The maximum distance after removing each point is the following:
//
//
// 	After removing the 0th point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
// 	After removing the 1st point the maximum distance is between points (3, 10) and (10, 2), which is |3 - 10| + |10 - 2| = 15.
// 	After removing the 2nd point the maximum distance is between points (5, 15) and (4, 4), which is |5 - 4| + |15 - 4| = 12.
// 	After removing the 3rd point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
//
//
// 12 is the minimum possible maximum distance between any two points after removing exactly one point.
//
// Constraints:
// 3 <= points.length <= 105
// 	points[i].length == 2
// 	1 <= points[i][0], points[i][1] <= 108
//

/**
 * @param {number[][]} points
 * @return {number}
 */
var minimumDistance = function(points) {
    const n = points.length;
    const x = points.map(p => p[0]);
    const y = points.map(p => p[1]);
    x.sort((a, b) => a - b);
    y.sort((a, b) => a - b);
    const candidates = [];  
    for (let i = 0; i < 4; i++) {
        candidates.push(x[i] + y[i]);
        candidates.push(x[i] - y[n - 1 - i]);
        candidates.push(-x[n - 1 - i] + y[i]);
        candidates.push(-x[n - 1 - i] - y[n - 1 - i]);
    }
    let minDistance = Infinity;
    for (const candidate of candidates) {
        let maxDistance = 0;
        for (let i = 0; i < n; i++) {
            const distance = Math.abs(points[i][0] + points[i][1] - candidate);
            maxDistance = Math.max(maxDistance, distance);
        }
        minDistance = Math.min(minDistance, maxDistance);
    }
    return minDistance;
};
