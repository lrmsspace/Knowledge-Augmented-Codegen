// Source: https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer side, representing the edge length of a square with corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian plane.
//
// You are also given a positive integer k and a 2D integer array points, where points[i] = [xi, yi] represents the coordinate of a point lying on the boundary of the square.
//
// You need to select k elements among points such that the minimum Manhattan distance between any two points is maximized.
//
// Return the maximum possible minimum Manhattan distance between the selected k points.
//
// The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
//
// Example:
// Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4
//
// Output: 2
//
// Explanation:
//
//
//
// Select all four points.
//
// Constraints:
// 1 <= side <= 109
// 	4 <= points.length <= min(4 * side, 15 * 103)
// 	points[i] == [xi, yi]
// 	The input is generated such that:
// 	
// 		points[i] lies on the boundary of the square.
// 		All points[i] are unique.
// 	
// 	
// 	4 <= k <= min(25, points.length)
//

/**
 * @param {number} side
 * @param {number[][]} points
 * @param {number} k
 * @return {number}
 */
var maxDistance = function(side, points, k) {
    const n = points.length;
    const manhattanDistances = Array.from({ length: n }, () => Array(n).fill(0));
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            manhattanDistances[i][j] = Math.abs(points[i][0] - points[j][0]) + Math.abs(points[i][1] - points[j][1]);
        }
    }
    let left = 0, right = 2 * side;
    const canSelectKPoints = (minDist) => {
        const selected = [];
        for (let i = 0; i < n; i++) {
            let valid = true;
            for (const idx of selected) {
                if (manhattanDistances[i][idx] < minDist) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                selected.push(i);
                if (selected.length === k) {
                    return true;
                }
            }
        }        return false;
    }
    let result = 0;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        if (canSelectKPoints(mid)) {
            result = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return result;  
};
