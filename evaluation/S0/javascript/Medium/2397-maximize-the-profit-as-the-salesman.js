// Source: https://leetcode.com/problems/maximize-the-profit-as-the-salesman/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the number of houses on a number line, numbered from 0 to n - 1.
//
// Additionally, you are given a 2D integer array offers where offers[i] = [starti, endi, goldi], indicating that ith buyer wants to buy all the houses from starti to endi for goldi amount of gold.
//
// As a salesman, your goal is to maximize your earnings by strategically selecting and selling houses to buyers.
//
// Return the maximum amount of gold you can earn.
//
// Note that different buyers can't buy the same house, and some houses may remain unsold.
//
// Example:
// Input: n = 5, offers = [[0,0,1],[0,2,2],[1,3,2]]
// Output: 3
// Explanation: There are 5 houses numbered from 0 to 4 and there are 3 purchase offers.
// We sell houses in the range [0,0] to 1st buyer for 1 gold and houses in the range [1,3] to 3rd buyer for 2 golds.
// It can be proven that 3 is the maximum amount of gold we can achieve.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= offers.length <= 105
// 	offers[i].length == 3
// 	0 <= starti <= endi <= n - 1
// 	1 <= goldi <= 103
//

/**
 * @param {number} n
 * @param {number[][]} offers
 * @return {number}
 */
var maximizeTheProfit = function(n, offers) {
    const dp = Array(n + 1).fill(0);
    const offerMap = Array.from({ length: n }, () => []);
    for (const [start, end, gold] of offers) {
        offerMap[end].push([start, gold]);
    }
    for (let i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        for (const [start, gold] of offerMap[i - 1]) {
            dp[i] = Math.max(dp[i], dp[start] + gold);
        }
    }
    return dp[n];
};