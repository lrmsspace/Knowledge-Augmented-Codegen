// Source: https://leetcode.com/problems/maximum-number-of-robots-within-budget/   |   Difficulty: Hard
//
// Problem Description:
// You have n robots. You are given two 0-indexed integer arrays, chargeTimes and runningCosts, both of length n. The ith robot costs chargeTimes[i] units to charge and costs runningCosts[i] units to run. You are also given an integer budget.
//
// The total cost of running k chosen robots is equal to max(chargeTimes) + k * sum(runningCosts), where max(chargeTimes) is the largest charge cost among the k robots and sum(runningCosts) is the sum of running costs among the k robots.
//
// Return the maximum number of consecutive robots you can run such that the total cost does not exceed budget.
//
// Example:
// Input: chargeTimes = [3,6,1,3,4], runningCosts = [2,1,3,4,5], budget = 25
// Output: 3
// Explanation: 
// It is possible to run all individual and consecutive pairs of robots within budget.
// To obtain answer 3, consider the first 3 robots. The total cost will be max(3,6,1) + 3 * sum(2,1,3) = 6 + 3 * 6 = 24 which is less than 25.
// It can be shown that it is not possible to run more than 3 consecutive robots within budget, so we return 3.
//
// Constraints:
// chargeTimes.length == runningCosts.length == n
// 	1 <= n <= 5 * 104
// 	1 <= chargeTimes[i], runningCosts[i] <= 105
// 	1 <= budget <= 1015
//

/**
 * @param {number[]} chargeTimes
 * @param {number[]} runningCosts
 * @param {number} budget
 * @return {number}
 */
var maximumRobots = function(chargeTimes, runningCosts, budget) {
    const n = chargeTimes.length;
    let left = 0;
    let sumRunningCosts = 0;
    let maxChargeTime = 0;
    let maxRobots = 0;
    for (let right = 0; right < n; right++) {
        sumRunningCosts += runningCosts[right];
        maxChargeTime = Math.max(maxChargeTime, chargeTimes[right]);
        while (maxChargeTime + (right - left + 1) * sumRunningCosts > budget) {
            sumRunningCosts -= runningCosts[left];
            if (chargeTimes[left] === maxChargeTime) {
                maxChargeTime = 0;
                for (let i = left + 1; i <= right; i++) {
                    maxChargeTime = Math.max(maxChargeTime, chargeTimes[i]);
                }
            }
            left++;
        }
        maxRobots = Math.max(maxRobots, right - left + 1);
    }
    return maxRobots;   
};
