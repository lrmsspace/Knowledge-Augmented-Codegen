// Source: https://leetcode.com/problems/length-of-the-longest-increasing-path/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of integers coordinates of length n and an integer k, where 0 <= k < n.
//
// coordinates[i] = [xi, yi] indicates the point (xi, yi) in a 2D plane.
//
// An increasing path of length m is defined as a list of points (x1, y1), (x2, y2), (x3, y3), ..., (xm, ym) such that:
//
//
// 	xi < xi + 1 and yi < yi + 1 for all i where 1 <= i < m.
// 	(xi, yi) is in the given coordinates for all i where 1 <= i <= m.
//
//
// Return the maximum length of an increasing path that contains coordinates[k].
//
// Example:
// Input: coordinates = [[3,1],[2,2],[4,1],[0,0],[5,3]], k = 1
//
// Output: 3
//
// Explanation:
//
// (0, 0), (2, 2), (5, 3) is the longest increasing path that contains (2, 2).
//
// Constraints:
// 1 <= n == coordinates.length <= 105
// 	coordinates[i].length == 2
// 	0 <= coordinates[i][0], coordinates[i][1] <= 109
// 	All elements in coordinates are distinct.
// 	0 <= k <= n - 1
//

/**
 * @param {number[][]} coordinates
 * @param {number} k
 * @return {number}
 */
var maxPathLength = function(coordinates, k) {
    const n = coordinates.length;
    const dp = Array(n).fill(1);
    coordinates.sort((a, b) => a[0] - b[0] || a[1] - b[1]);
    let maxLength = 1;
    let targetLength = 1;
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < i; j++) {
            if (coordinates[i][0] > coordinates[j][0] && coordinates[i][1] > coordinates[j][1]) {
                dp[i] = Math.max(dp[i], dp[j] + 1);
            }
        }
        if (i === k) {
            targetLength = dp[i];
        }
        maxLength = Math.max(maxLength, dp[i]);
    }
    return targetLength;    
};
