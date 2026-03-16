// Source: https://leetcode.com/problems/number-of-boomerangs/   |   Difficulty: Medium
//
// Problem Description:
// You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
//
// Return the number of boomerangs.
//
// Example:
// Input: points = [[0,0],[1,0],[2,0]]
// Output: 2
// Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
//
// Constraints:
// n == points.length
// 	1 <= n <= 500
// 	points[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the points are unique.
//

/**
 * @param {number[][]} points
 * @return {number}
 */
var numberOfBoomerangs = function(points) {
    let boomerangCount = 0;

    for (let i = 0; i < points.length; i++) {
        const distanceMap = new Map();
        for (let j = 0; j < points.length; j++) {
            if (i !== j) {
                const dx = points[i][0] - points[j][0];
                const dy = points[i][1] - points[j][1];
                const distanceSquared = dx * dx + dy * dy;
                distanceMap.set(distanceSquared, (distanceMap.get(distanceSquared) || 0) + 1);
            }
        }
        for (const count of distanceMap.values()) {
            if (count > 1) {
                boomerangCount += count * (count - 1);
            }
        }
    }
    return boomerangCount;
};
