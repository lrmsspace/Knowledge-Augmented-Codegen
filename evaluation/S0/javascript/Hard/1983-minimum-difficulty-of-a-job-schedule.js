// Source: https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/   |   Difficulty: Hard
//
// Problem Description:
// You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the ith job, you have to finish all the jobs j where 0 <= j < i).
//
// You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done on that day.
//
// You are given an integer array jobDifficulty and an integer d. The difficulty of the ith job is jobDifficulty[i].
//
// Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.
//
// Example:
// Input: jobDifficulty = [6,5,4,3,2,1], d = 2
// Output: 7
// Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
// Second day you can finish the last job, total difficulty = 1.
// The difficulty of the schedule = 6 + 1 = 7
//
// Constraints:
// 1 <= jobDifficulty.length <= 300
// 	0 <= jobDifficulty[i] <= 1000
// 	1 <= d <= 10
//

/**
 * @param {number[]} jobDifficulty
 * @param {number} d
 * @return {number}
 */
var minDifficulty = function(jobDifficulty, d) {
    const n = jobDifficulty.length;
    if (n < d) {
        return -1;
    }
    const dp = Array.from({ length: d }, () => Array(n).fill(Infinity));
    for (let i = 0, maxDifficulty = 0; i < n; i++) {
        maxDifficulty = Math.max(maxDifficulty, jobDifficulty[i]);
        dp[0][i] = maxDifficulty;
    }
    for (let day = 1; day < d; day++) {
        for (let i = day; i < n; i++) {
            let maxDifficulty = 0;
            for (let j = i; j >= day; j--) {
                maxDifficulty = Math.max(maxDifficulty, jobDifficulty[j]);
                dp[day][i] = Math.min(dp[day][i], dp[day - 1][j - 1] + maxDifficulty);
            }
        }
    }
    return dp[d - 1][n - 1];
};
