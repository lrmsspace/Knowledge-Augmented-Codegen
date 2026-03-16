// Source: https://leetcode.com/problems/min-cost-to-connect-all-points/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
//
// The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.
//
// Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.
//
// Example:
// Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// Output: 20
// Explanation: 
//
// We can connect the points as shown above to get the minimum cost of 20.
// Notice that there is a unique path between every pair of points.
//
// Constraints:
// 1 <= points.length <= 1000
// 	-106 <= xi, yi <= 106
// 	All pairs (xi, yi) are distinct.
//

/**
 * @param {number[][]} points
 * @return {number}
 */
var minCostConnectPoints = function(points) {
    const n = points.length;
    const inMST = Array(n).fill(false);
    const minDist = Array(n).fill(Infinity);
    minDist[0] = 0;
    let totalCost = 0;
    for (let i = 0; i < n; i++) {
        let u = -1;
        for (let v = 0; v < n; v++) {
            if (!inMST[v] && (u === -1 || minDist[v] < minDist[u])) {
                u = v;
            }
        }
        inMST[u] = true;
        totalCost += minDist[u];
        for (let v = 0; v < n; v++) {
            if (!inMST[v]) {
                const dist = Math.abs(points[u][0] - points[v][0]) + Math.abs(points[u][1] - points[v][1]);
                if (dist < minDist[v]) {
                    minDist[v] = dist;
                }
            }
        }
    }
    return totalCost;
};