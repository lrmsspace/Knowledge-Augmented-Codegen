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

int minimumTimeRequired(int* jobs, int jobsSize, int k) {
    int left = 0, right = 0;
    for (int i = 0; i < jobsSize; ++i) {
        if (jobs[i] > left) left = jobs[i];
        right += jobs[i];
    }

    int canFinish(int limit, int idx, int *workers, int k, int *jobs, int jobsSize) {
        if (idx == jobsSize) return 1;
        for (int i = 0; i < k; ++i) {
            if (workers[i] + jobs[idx] <= limit) {
                workers[i] += jobs[idx];
                if (canFinish(limit, idx + 1, workers, k, jobs, jobsSize)) return 1;
                workers[i] -= jobs[idx];
            }
            if (workers[i] == 0) break; // optimization: avoid symmetric cases
        }
        return 0;
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        int *workers = (int*)calloc(k, sizeof(int));
        if (canFinish(mid, 0, workers, k, jobs, jobsSize)) {
            right = mid;
        } else {
            left = mid + 1;
        }
        free(workers);
    }
    return left;        
}
