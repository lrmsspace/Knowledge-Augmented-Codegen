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

class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = jobs.size();
        int left = *max_element(jobs.begin(), jobs.end());
        int right = accumulate(jobs.begin(), jobs.end(), 0);
        int answer = right;
        
        function<bool(int, vector<int>&, int)> canFinish = [&](int limit, vector<int>& workers, int jobIdx) {
            if (jobIdx == n) return true;
            
            int jobTime = jobs[jobIdx];
            for (int i = 0; i < workers.size(); i++) {
                if (workers[i] + jobTime <= limit) {
                    workers[i] += jobTime;
                    if (canFinish(limit, workers, jobIdx + 1)) {
                        return true;
                    }
                    workers[i] -= jobTime;
                }
                
                // If this worker has no jobs assigned, no need to try further
                if (workers[i] == 0) break;
            }
            return false;
        };
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            vector<int> workers(k, 0);
            if (canFinish(mid, workers, 0)) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return answer;          
    }
};
