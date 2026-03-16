# Source: https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array jobs, where jobs[i] is the amount of time it takes to complete the ith job.
#
# There are k workers that you can assign jobs to. Each job should be assigned to exactly one worker. The working time of a worker is the sum of the time it takes to complete all jobs assigned to them. Your goal is to devise an optimal assignment such that the maximum working time of any worker is minimized.
#
# Return the minimum possible maximum working time of any assignment.
#
# Example:
# Input: jobs = [3,2,3], k = 3
# Output: 3
# Explanation: By assigning each person one job, the maximum time is 3.
#
# Constraints:
# 1 <= k <= jobs.length <= 12
# 	1 <= jobs[i] <= 107
#

class Solution(object):
    def minimumTimeRequired(self, jobs, k):
        """
        :type jobs: List[int]
        :type k: int
        :rtype: int
        """
        def canFinish(limit):
            workloads = [0] * k

            def backtrack(index):
                if index == len(jobs):
                    return True
                for i in range(k):
                    if workloads[i] + jobs[index] <= limit:
                        workloads[i] += jobs[index]
                        if backtrack(index + 1):
                            return True
                        workloads[i] -= jobs[index]
                    if workloads[i] == 0:
                        break
                return False

            return backtrack(0)

        left, right = max(jobs), sum(jobs)
        while left < right:
            mid = (left + right) // 2
            if canFinish(mid):
                right = mid
            else:
                left = mid + 1
        return left