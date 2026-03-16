// Source: https://leetcode.com/problems/triangle/   |   Difficulty: Medium
//
// Problem Description:
// Given a triangle array, return the minimum path sum from top to bottom.
//
// For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.
//
// Example:
// Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
// Output: 11
// Explanation: The triangle looks like:
//    2
//   3 4
//  6 5 7
// 4 1 8 3
// The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
//
// Constraints:
// 1 <= triangle.length <= 200
// 	triangle[0].length == 1
// 	triangle[i].length == triangle[i - 1].length + 1
// 	-104 <= triangle[i][j] <= 104
//
//
//  
// Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?
//

/**
 * @param {number[][]} triangle
 * @return {number}
 */
var minimumTotal = function(triangle) {
    const n = triangle.length;
    const dp = Array.from({ length: n }, () => Array(n).fill(0));
    dp[0][0] = triangle[0][0];
    for (let i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + triangle[i][0];
        for (let j = 1; j < i; j++) {
            dp[i][j] = Math.min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
        }
        dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
    }
    return Math.min(...dp[n - 1]);
};