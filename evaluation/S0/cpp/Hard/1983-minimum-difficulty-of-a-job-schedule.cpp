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

class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        if (n < d) return -1;
        
        // dp[i][j]: min difficulty to schedule first j jobs in i days
        vector<vector<int>> dp(d + 1, vector<int>(n + 1, INT_MAX));
        dp[0][0] = 0;
        
        for (int day = 1; day <= d; day++) {
            for (int job = day; job <= n; job++) {
                int maxDifficulty = 0;
                for (int k = job - 1; k >= day - 1; k--) {
                    maxDifficulty = max(maxDifficulty, jobDifficulty[k]);
                    if (dp[day - 1][k] != INT_MAX) {
                        dp[day][job] = min(dp[day][job], dp[day - 1][k] + maxDifficulty);
                    }
                }
            }
        }
        
        return dp[d][n] == INT_MAX ? -1 : dp[d][n];         
    }
};
