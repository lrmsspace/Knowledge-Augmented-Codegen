// Source: https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array jobs, where jobs[i] is the amount of time it takes to complete the ith job.
//
// There are k workers that you can assign jobs to. Each job should be assigned to exactly one worker. The working time of a worker is the sum of the time it takes to complete all jobs assigned to them. Your goal is to devise an optimal assignment such that the maximum working time of any worker is minimized.
//
// Return the minimum possible maximum working time of any assignment.
//
// Example:
// Input: jobs = [3,2,3], k = 3
// Output: 3
// Explanation: By assigning each person one job, the maximum time is 3.
//
// Constraints:
// 1 <= k <= jobs.length <= 12
// 	1 <= jobs[i] <= 107
//

/**
 * @param {number[]} jobs
 * @param {number} k
 * @return {number}
 */
var minimumTimeRequired = function(jobs, k) {
    const n = jobs.length;
    const totalTime = jobs.reduce((a, b) => a + b, 0);
    const maxTime = Math.max(...jobs);
    let left = maxTime;
    let right = totalTime;
    const canFinish = (limit) => {
        const workers = new Array(k).fill(0);
        const backtrack = (index) => {
            if (index === n) {
                return true;
            }
            for (let i = 0; i < k; i++) {
                if (workers[i] + jobs[index] <= limit) {
                    workers[i] += jobs[index];
                    if (backtrack(index + 1)) {
                        return true;
                    }
                    workers[i] -= jobs[index];
                }
                if (workers[i] === 0) {
                    break;
                }
            }            return false;
        }
        return backtrack(0);
    };
    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        if (canFinish(mid)) {
            right = mid;
        }
        else {            left = mid + 1;
        }
    }
    return left;    
};
