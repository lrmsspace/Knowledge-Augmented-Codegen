# Source: https://leetcode.com/problems/minimum-processing-time/   |   Difficulty: Medium
#
# Problem Description:
# You have a certain number of processors, each having 4 cores. The number of tasks to be executed is four times the number of processors. Each task must be assigned to a unique core, and each core can only be used once.
#
# You are given an array processorTime representing the time each processor becomes available and an array tasks representing how long each task takes to complete. Return the minimum time needed to complete all tasks.
#
# Example:
# Input: processorTime = [8,10], tasks = [2,2,3,1,8,7,4,5]
#
# Output: 16
#
# Explanation:
#
# Assign the tasks at indices 4, 5, 6, 7 to the first processor which becomes available at time = 8, and the tasks at indices 0, 1, 2, 3 to the second processor which becomes available at time = 10. 
#
# The time taken by the first processor to finish the execution of all tasks is max(8 + 8, 8 + 7, 8 + 4, 8 + 5) = 16.
#
# The time taken by the second processor to finish the execution of all tasks is max(10 + 2, 10 + 2, 10 + 3, 10 + 1) = 13.
#
# Constraints:
# 1 <= n == processorTime.length <= 25000
# 	1 <= tasks.length <= 105
# 	0 <= processorTime[i] <= 109
# 	1 <= tasks[i] <= 109
# 	tasks.length == 4 * n
#

class Solution(object):
    def minProcessingTime(self, processorTime, tasks):
        """
        :type processorTime: List[int]
        :type tasks: List[int]
        :rtype: int
        """
        import heapq

        # Step 1: Sort tasks in descending order
        tasks.sort(reverse=True)

        # Step 2: Create a min-heap for processors based on their available time
        min_heap = [(time, 4) for time in processorTime]  # (available_time, remaining_cores)
        heapq.heapify(min_heap)

        max_completion_time = 0

        # Step 3: Assign tasks to processors
        for task in tasks:
            available_time, remaining_cores = heapq.heappop(min_heap)

            # Calculate the completion time for this task
            completion_time = available_time + task
            max_completion_time = max(max_completion_time, completion_time)

            # Update the processor's available time and remaining cores
            remaining_cores -= 1
            if remaining_cores > 0:
                heapq.heappush(min_heap, (completion_time, remaining_cores))
            else:
                heapq.heappush(min_heap, (completion_time, 0))

        return max_completion_time