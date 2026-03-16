# Source: https://leetcode.com/problems/minimum-time-to-complete-all-tasks/   |   Difficulty: Hard
#
# Problem Description:
# There is a computer that can run an unlimited number of tasks at the same time. You are given a 2D integer array tasks where tasks[i] = [starti, endi, durationi] indicates that the ith task should run for a total of durationi seconds (not necessarily continuous) within the inclusive time range [starti, endi].
#
# You may turn on the computer only when it needs to run a task. You can also turn it off if it is idle.
#
# Return the minimum time during which the computer should be turned on to complete all tasks.
#
# Example:
# Input: tasks = [[2,3,1],[4,5,1],[1,5,2]]
# Output: 2
# Explanation: 
# - The first task can be run in the inclusive time range [2, 2].
# - The second task can be run in the inclusive time range [5, 5].
# - The third task can be run in the two inclusive time ranges [2, 2] and [5, 5].
# The computer will be on for a total of 2 seconds.
#
# Constraints:
# 1 <= tasks.length <= 2000
# 	tasks[i].length == 3
# 	1 <= starti, endi <= 2000
# 	1 <= durationi <= endi - starti + 1
#

class Solution(object):
    def findMinimumTime(self, tasks):
        """
        :type tasks: List[List[int]]
        :rtype: int
        """
        tasks.sort(key=lambda x: x[1])
        n = len(tasks)
        max_end = max(task[1] for task in tasks)
        timeline = [0] * (max_end + 2)
        total_time = 0

        for start, end, duration in tasks:
            already_scheduled = sum(timeline[start:end + 1])
            remaining = duration - already_scheduled

            if remaining > 0:
                for t in range(end, start - 1, -1):
                    if timeline[t] == 0 and remaining > 0:
                        timeline[t] = 1
                        remaining -= 1
                        total_time += 1

                    if remaining == 0:
                        break

        return total_time