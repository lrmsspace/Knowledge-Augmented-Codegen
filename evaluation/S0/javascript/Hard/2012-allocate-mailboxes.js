// Source: https://leetcode.com/problems/allocate-mailboxes/   |   Difficulty: Hard
//
// Problem Description:
// Given the array houses where houses[i] is the location of the ith house along a street and an integer k, allocate k mailboxes in the street.
//
// Return the minimum total distance between each house and its nearest mailbox.
//
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: houses = [1,4,8,10,20], k = 3
// Output: 5
// Explanation: Allocate mailboxes in position 3, 9 and 20.
// Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5
//
// Constraints:
// 1 <= k <= houses.length <= 100
// 	1 <= houses[i] <= 104
// 	All the integers of houses are unique.
//

/**
 * @param {number[]} houses
 * @param {number} k
 * @return {number}
 */
var minDistance = function(houses, k) {
    houses.sort((a, b) => a - b);
    const n = houses.length;
    const dp = new Array(n + 1).fill(0).map(() => new Array(k + 1).fill(Infinity));
    dp[0][0] = 0;
    for (let i = 1; i <= n; i++) {
        for (let j = 1; j <= k; j++) {
            for (let m = 0; m < i; m++) {
                const median = houses[Math.floor((m + i - 1) / 2)];
                let cost = 0;
                for (let x = m; x < i; x++) {
                    cost += Math.abs(houses[x] - median);
                }
                dp[i][j] = Math.min(dp[i][j], dp[m][j - 1] + cost);
            }
        }
    }
    return dp[n][k];
};
