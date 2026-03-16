# Source: https://leetcode.com/problems/most-profit-assigning-work/   |   Difficulty: Medium
#
# Problem Description:
# You have n jobs and m workers. You are given three arrays: difficulty, profit, and worker where:
#
#
# 	difficulty[i] and profit[i] are the difficulty and the profit of the ith job, and
# 	worker[j] is the ability of jth worker (i.e., the jth worker can only complete a job with difficulty at most worker[j]).
#
#
# Every worker can be assigned at most one job, but one job can be completed multiple times.
#
#
# 	For example, if three workers attempt the same job that pays $1, then the total profit will be $3. If a worker cannot complete any job, their profit is $0.
#
#
# Return the maximum profit we can achieve after assigning the workers to the jobs.
#
# Example:
# Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
# Output: 100
# Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get a profit of [20,20,30,30] separately.
#
# Constraints:
# n == difficulty.length
# 	n == profit.length
# 	m == worker.length
# 	1 <= n, m <= 104
# 	1 <= difficulty[i], profit[i], worker[i] <= 105
#

class Solution(object):
    def maxProfitAssignment(self, difficulty, profit, worker):
        """
        :type difficulty: List[int]
        :type profit: List[int]
        :type worker: List[int]
        :rtype: int
        """
        jobs = sorted(zip(difficulty, profit))
        max_profit = 0
        total_profit = 0
        j = 0
        
        for ability in sorted(worker):
            while j < len(jobs) and ability >= jobs[j][0]:
                max_profit = max(max_profit, jobs[j][1])
                j += 1
            total_profit += max_profit
            
        return total_profit