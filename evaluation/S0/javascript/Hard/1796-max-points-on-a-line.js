// Source: https://leetcode.com/problems/max-points-on-a-line/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.
//
// Example:
// Input: points = [[1,1],[2,2],[3,3]]
// Output: 3
//
// Constraints:
// 1 <= points.length <= 300
// 	points[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the points are unique.
//

/**
 * @param {number[][]} points
 * @return {number}
 */
var maxPoints = function(points) {
    


    const n = points.length;
    if (n <= 2) return n;

    let maxPointsOnLine = 1;
    for (let i = 0; i < n; i++) {
        const slopeCount = new Map();
        let duplicatePoints = 1; // Count the point itself

        for (let j = 0; j < n; j++) {
            if (i === j) continue;
            const dx = points[j][0] - points[i][0];
            const dy = points[j][1] - points[i][1];
            if (dx === 0 && dy === 0) {
                duplicatePoints++;
                continue;
            }
            const gcd = (a, b) => b === 0 ? a : gcd(b, a % b);
            const g = gcd(dx, dy);
            const slope = `${dy / g}/${dx / g}`;
            slopeCount.set(slope, (slopeCount.get(slope) || 0) + 1);
        }
        let currentMax = 0;
        for (const count of slopeCount.values()) {
            currentMax = Math.max(currentMax, count);
        }
        maxPointsOnLine = Math.max(maxPointsOnLine, currentMax + duplicatePoints);
    }
    return maxPointsOnLine; 
    
};
