// Source: https://leetcode.com/problems/minimum-cost-for-tickets/   |   Difficulty: Medium
//
// Problem Description:
// You have planned some train traveling one year in advance. The days of the year in which you will travel are given as an integer array days. Each day is an integer from 1 to 365.
//
// Train tickets are sold in three different ways:
//
//
// 	a 1-day pass is sold for costs[0] dollars,
// 	a 7-day pass is sold for costs[1] dollars, and
// 	a 30-day pass is sold for costs[2] dollars.
//
//
// The passes allow that many days of consecutive travel.
//
//
// 	For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7, and 8.
//
//
// Return the minimum number of dollars you need to travel every day in the given list of days.
//
// Example:
// Input: days = [1,4,6,7,8,20], costs = [2,7,15]
// Output: 11
// Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
// On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
// On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
// On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
// In total, you spent $11 and covered all the days of your travel.
//
// Constraints:
// 1 <= days.length <= 365
// 	1 <= days[i] <= 365
// 	days is in strictly increasing order.
// 	costs.length == 3
// 	1 <= costs[i] <= 1000
//

/**
 * @param {number[]} days
 * @param {number[]} costs
 * @return {number}
 */
var mincostTickets = function(days, costs) {
    const daySet = new Set(days);
    const maxDay = days[days.length - 1];
    const dp = new Array(maxDay + 1).fill(0);
    for (let day = 1; day <= maxDay; day++) {
        if (!daySet.has(day)) {
            dp[day] = dp[day - 1];
        } else {
            const cost1 = dp[day - 1] + costs[0];
            const cost7 = dp[Math.max(0, day - 7)] + costs[1];
            const cost30 = dp[Math.max(0, day - 30)] + costs[2];
            dp[day] = Math.min(cost1, cost7, cost30);
        }
    }
    return dp[maxDay];
        
};
