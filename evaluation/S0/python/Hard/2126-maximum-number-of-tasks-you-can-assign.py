# Source: https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/   |   Difficulty: Hard
#
# Problem Description:
# You have n tasks and m workers. Each task has a strength requirement stored in a 0-indexed integer array tasks, with the ith task requiring tasks[i] strength to complete. The strength of each worker is stored in a 0-indexed integer array workers, with the jth worker having workers[j] strength. Each worker can only be assigned to a single task and must have a strength greater than or equal to the task's strength requirement (i.e., workers[j] >= tasks[i]).
#
# Additionally, you have pills magical pills that will increase a worker's strength by strength. You can decide which workers receive the magical pills, however, you may only give each worker at most one magical pill.
#
# Given the 0-indexed integer arrays tasks and workers and the integers pills and strength, return the maximum number of tasks that can be completed.
#
# Example:
# Input: tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
# Output: 3
# Explanation:
# We can assign the magical pill and tasks as follows:
# - Give the magical pill to worker 0.
# - Assign worker 0 to task 2 (0 + 1 >= 1)
# - Assign worker 1 to task 1 (3 >= 2)
# - Assign worker 2 to task 0 (3 >= 3)
#
# Constraints:
# n == tasks.length
# 	m == workers.length
# 	1 <= n, m <= 5 * 104
# 	0 <= pills <= m
# 	0 <= tasks[i], workers[j], strength <= 109
#

class Solution(object):
    def maxTaskAssign(self, tasks, workers, pills, strength):
        """
        :type tasks: List[int]
        :type workers: List[int]
        :type pills: int
        :type strength: int
        :rtype: int
        """
        tasks.sort()
        workers.sort()
        
        def canAssign(k):
            available = []
            i = len(workers) - 1
            for j in range(k - 1, -1, -1):
                while i >= len(workers) - k and workers[i] + strength >= tasks[j]:
                    available.append(workers[i])
                    i -= 1
                if not available:
                    return False
                if available[-1] >= tasks[j]:
                    available.pop()
                else:
                    if pills == 0:
                        return False
                    pills_used = 1
                    while available and available[-1] < tasks[j]:
                        available.pop()
                        pills_used += 1
                        if pills_used > pills:
                            return False
                    if not available:
                        return False
                    available.pop()
            return True
        
        left, right = 0, min(len(tasks), len(workers))
        result = 0
        while left <= right:
            mid = (left + right) // 2
            if canAssign(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        return result