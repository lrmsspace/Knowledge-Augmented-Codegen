// Source: https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/   |   Difficulty: Hard
//
// Problem Description:
// You are given two groups of points where the first group has size1 points, the second group has size2 points, and size1 >= size2.
//
// The cost of the connection between any two points are given in an size1 x size2 matrix where cost[i][j] is the cost of connecting point i of the first group and point j of the second group. The groups are connected if each point in both groups is connected to one or more points in the opposite group. In other words, each point in the first group must be connected to at least one point in the second group, and each point in the second group must be connected to at least one point in the first group.
//
// Return the minimum cost it takes to connect the two groups.
//
// Example:
// Input: cost = [[15, 96], [36, 2]]
// Output: 17
// Explanation: The optimal way of connecting the groups is:
// 1--A
// 2--B
// This results in a total cost of 17.
//
// Constraints:
// size1 == cost.length
// 	size2 == cost[i].length
// 	1 <= size1, size2 <= 12
// 	size1 >= size2
// 	0 <= cost[i][j] <= 100
//

/**
 * @param {number[][]} cost
 * @return {number}
 */
var connectTwoGroups = function(cost) {
    const size1 = cost.length;
    const size2 = cost[0].length;
    const dp = new Array(1 << size2).fill(Infinity);
    dp[0] = 0;
    for (let i = 0; i < size1; i++) {
        const newDp = new Array(1 << size2).fill(Infinity);
        for (let mask = 0; mask < (1 << size2); mask++) {
            for (let j = 0; j < size2; j++) {
                const newMask = mask | (1 << j);
                newDp[newMask] = Math.min(newDp[newMask], dp[mask] + cost[i][j]);
            }
        }
        for (let mask = 0; mask < (1 << size2); mask++) {
            newDp[mask] = Math.min(newDp[mask], dp[mask]);
        }
        dp.splice(0, dp.length, ...newDp);
    }
    return dp[(1 << size2) - 1];
};
