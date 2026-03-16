// Source: https://leetcode.com/problems/largest-triangle-area/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of points on the X-Y plane points where points[i] = [xi, yi], return the area of the largest triangle that can be formed by any three different points. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
// Output: 2.00000
// Explanation: The five points are shown in the above figure. The red triangle is the largest.
//
// Constraints:
// 3 <= points.length <= 50
// 	-50 <= xi, yi <= 50
// 	All the given points are unique.
//

/**
 * @param {number[][]} points
 * @return {number}
 */
var largestTriangleArea = function(points) {
    const n = points.length;
    let maxArea = 0;    
    for (let i = 0; i < n - 2; i++) {   
        for (let j = i + 1; j < n - 1; j++) {   
            for (let k = j + 1; k < n; k++) {   
                const area = Math.abs(
                    points[i][0] * (points[j][1] - points[k][1]) +
                    points[j][0] * (points[k][1] - points[i][1]) +
                    points[k][0] * (points[i][1] - points[j][1])
                ) / 2;
                maxArea = Math.max(maxArea, area);
            }
        }
    }
    return maxArea;
};
