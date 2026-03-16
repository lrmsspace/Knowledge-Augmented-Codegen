// Source: https://leetcode.com/problems/maximum-profit-in-job-scheduling/   |   Difficulty: Hard
//
// Problem Description:
// We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].
//
// You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.
//
// If you choose a job that ends at time X you will be able to start another job that starts at time X.
//
// Example:
// Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
// Output: 120
// Explanation: The subset chosen is the first and fourth job. 
// Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
//
// Constraints:
// 1 <= startTime.length == endTime.length == profit.length <= 5 * 104
// 	1 <= startTime[i] < endTime[i] <= 109
// 	1 <= profit[i] <= 104
//

/**
 * @param {number[]} startTime
 * @param {number[]} endTime
 * @param {number[]} profit
 * @return {number}
 */
var jobScheduling = function(startTime, endTime, profit) {
    const n = startTime.length;
    const jobs = [];
    for (let i = 0; i < n; i++) {
        jobs.push([startTime[i], endTime[i], profit[i]]);
    }
    jobs.sort((a, b) => a[1] - b[1]);
    const dp = new Array(n).fill(0);
    dp[0] = jobs[0][2];
    for (let i = 1; i < n; i++) {
        dp[i] = Math.max(dp[i - 1], jobs[i][2]);
        const idx = binarySearch(jobs, i);
        if (idx !== -1) {
            dp[i] = Math.max(dp[i], dp[idx] + jobs[i][2]);
        }   
    }
    return dp[n - 1];   
};
