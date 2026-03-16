# Source: https://leetcode.com/problems/time-needed-to-inform-all-employees/   |   Difficulty: Medium
#
# Problem Description:
# A company has n employees with a unique ID for each employee from 0 to n - 1. The head of the company is the one with headID.
#
# Each employee has one direct manager given in the manager array where manager[i] is the direct manager of the i-th employee, manager[headID] = -1. Also, it is guaranteed that the subordination relationships have a tree structure.
#
# The head of the company wants to inform all the company employees of an urgent piece of news. He will inform his direct subordinates, and they will inform their subordinates, and so on until all employees know about the urgent news.
#
# The i-th employee needs informTime[i] minutes to inform all of his direct subordinates (i.e., After informTime[i] minutes, all his direct subordinates can start spreading the news).
#
# Return the number of minutes needed to inform all the employees about the urgent news.
#
# Example:
# Input: n = 1, headID = 0, manager = [-1], informTime = [0]
# Output: 0
# Explanation: The head of the company is the only employee in the company.
#
# Constraints:
# 1 <= n <= 105
# 	0 <= headID < n
# 	manager.length == n
# 	0 <= manager[i] < n
# 	manager[headID] == -1
# 	informTime.length == n
# 	0 <= informTime[i] <= 1000
# 	informTime[i] == 0 if employee i has no subordinates.
# 	It is guaranteed that all the employees can be informed.
#

class Solution(object):
    def numOfMinutes(self, n, headID, manager, informTime):
        """
        :type n: int
        :type headID: int
        :type manager: List[int]
        :type informTime: List[int]
        :rtype: int
        """
        from collections import defaultdict, deque

        # Build the graph
        graph = defaultdict(list)
        for emp_id in range(n):
            mgr_id = manager[emp_id]
            if mgr_id != -1:
                graph[mgr_id].append(emp_id)

        # BFS to calculate the time needed
        max_time = 0
        queue = deque([(headID, 0)])  # (employee_id, current_time)

        while queue:
            emp_id, curr_time = queue.popleft()
            total_time = curr_time + informTime[emp_id]
            max_time = max(max_time, total_time)

            for subordinate in graph[emp_id]:
                queue.append((subordinate, total_time))

        return max_time