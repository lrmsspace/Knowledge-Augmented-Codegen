# Source: https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/   |   Difficulty: Hard
#
# Problem Description:
# You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the ith job, you have to finish all the jobs j where 0 <= j < i).
#
# You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done on that day.
#
# You are given an integer array jobDifficulty and an integer d. The difficulty of the ith job is jobDifficulty[i].
#
# Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.
#
# Example:
# Input: jobDifficulty = [6,5,4,3,2,1], d = 2
# Output: 7
# Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
# Second day you can finish the last job, total difficulty = 1.
# The difficulty of the schedule = 6 + 1 = 7
#
# Constraints:
# 1 <= jobDifficulty.length <= 300
# 	0 <= jobDifficulty[i] <= 1000
# 	1 <= d <= 10
#

class Solution(object):
    def minDifficulty(self, jobDifficulty, d):
        """
        :type jobDifficulty: List[int]
        :type d: int
        :rtype: int
        """
        n = len(jobDifficulty)
        if n < d:
            return -1

        dp = [[float('inf')] * n for _ in range(d)]
        
        max_difficulty = 0
        for j in range(n):
            max_difficulty = max(max_difficulty, jobDifficulty[j])
            dp[0][j] = max_difficulty

        for day in range(1, d):
            for job in range(day, n):
                max_difficulty = 0
                for k in range(job, day - 1, -1):
                    max_difficulty = max(max_difficulty, jobDifficulty[k])
                    dp[day][job] = min(dp[day][job], dp[day - 1][k - 1] + max_difficulty)

        return dp[d - 1][n - 1]