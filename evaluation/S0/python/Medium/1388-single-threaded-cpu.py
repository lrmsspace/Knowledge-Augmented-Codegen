# Source: https://leetcode.com/problems/single-threaded-cpu/   |   Difficulty: Medium
#
# Problem Description:
# You are given n​​​​​​ tasks labeled from 0 to n - 1 represented by a 2D integer array tasks, where tasks[i] = [enqueueTimei, processingTimei] means that the i​​​​​​th​​​​ task will be available to process at enqueueTimei and will take processingTimei to finish processing.
#
# You have a single-threaded CPU that can process at most one task at a time and will act in the following way:
#
#
# 	If the CPU is idle and there are no available tasks to process, the CPU remains idle.
# 	If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest processing time. If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.
# 	Once a task is started, the CPU will process the entire task without stopping.
# 	The CPU can finish a task then start a new one instantly.
#
#
# Return the order in which the CPU will process the tasks.
#
# Example:
# Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
# Output: [0,2,3,1]
# Explanation: The events go as follows: 
# - At time = 1, task 0 is available to process. Available tasks = {0}.
# - Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
# - At time = 2, task 1 is available to process. Available tasks = {1}.
# - At time = 3, task 2 is available to process. Available tasks = {1, 2}.
# - Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it is the shortest. Available tasks = {1}.
# - At time = 4, task 3 is available to process. Available tasks = {1, 3}.
# - At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the shortest. Available tasks = {1}.
# - At time = 6, the CPU finishes task 3 and starts processing task 1. Available tasks = {}.
# - At time = 10, the CPU finishes task 1 and becomes idle.
#
# Constraints:
# tasks.length == n
# 	1 <= n <= 105
# 	1 <= enqueueTimei, processingTimei <= 109
#

class Solution(object):
    def getOrder(self, tasks):
        """
        :type tasks: List[List[int]]
        :rtype: List[int]
        """
        import heapq

        # Add original indices to tasks
        indexed_tasks = [(et, pt, i) for i, (et, pt) in enumerate(tasks)]
        # Sort tasks by enqueue time
        indexed_tasks.sort(key=lambda x: x[0])

        result = []
        min_heap = []
        time = 0
        task_index = 0
        n = len(tasks)

        while len(result) < n:
            # Add all tasks that have become available by current time
            while task_index < n and indexed_tasks[task_index][0] <= time:
                et, pt, i = indexed_tasks[task_index]
                heapq.heappush(min_heap, (pt, i))
                task_index += 1

            if min_heap:
                # Get the task with the smallest processing time (and smallest index if tie)
                pt, i = heapq.heappop(min_heap)
                time += pt
                result.append(i)
            else:
                # If no tasks are available, jump to the next task's enqueue time
                time = indexed_tasks[task_index][0]

        return result