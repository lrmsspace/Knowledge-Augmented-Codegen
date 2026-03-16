# Source: https://leetcode.com/problems/maximum-profit-in-job-scheduling/   |   Difficulty: Hard
#
# Problem Description:
# We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].
#
# You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.
#
# If you choose a job that ends at time X you will be able to start another job that starts at time X.
#
# Example:
# Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
# Output: 120
# Explanation: The subset chosen is the first and fourth job. 
# Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
#
# Constraints:
# 1 <= startTime.length == endTime.length == profit.length <= 5 * 104
# 	1 <= startTime[i] < endTime[i] <= 109
# 	1 <= profit[i] <= 104
#

class Solution(object):
    def jobScheduling(self, startTime, endTime, profit):
        """
        :type startTime: List[int]
        :type endTime: List[int]
        :type profit: List[int]
        :rtype: int
        """
        from bisect import bisect_right

        # Combine the job attributes and sort by end time
        jobs = sorted(zip(startTime, endTime, profit), key=lambda x: x[1])
        n = len(jobs)

        # dp[i] will store the maximum profit for jobs[0..i]
        dp = [0] * (n + 1)

        # Extract end times for binary search
        end_times = [job[1] for job in jobs]

        for i in range(1, n + 1):
            start, end, prof = jobs[i - 1]

            # Find the last non-conflicting job using binary search
            index = bisect_right(end_times, start) - 1

            # Include the current job
            include_profit = prof + dp[index + 1]

            # Exclude the current job
            exclude_profit = dp[i - 1]

            # Take the maximum of including or excluding the current job
            dp[i] = max(include_profit, exclude_profit)

        return dp[n]