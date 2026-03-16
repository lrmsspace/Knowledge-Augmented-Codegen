# Source: https://leetcode.com/problems/time-to-cross-a-bridge/   |   Difficulty: Hard
#
# Problem Description:
# There are k workers who want to move n boxes from the right (old) warehouse to the left (new) warehouse. You are given the two integers n and k, and a 2D integer array time of size k x 4 where time[i] = [righti, picki, lefti, puti].
#
# The warehouses are separated by a river and connected by a bridge. Initially, all k workers are waiting on the left side of the bridge. To move the boxes, the ith worker can do the following:
#
#
# 	Cross the bridge to the right side in righti minutes.
# 	Pick a box from the right warehouse in picki minutes.
# 	Cross the bridge to the left side in lefti minutes.
# 	Put the box into the left warehouse in puti minutes.
#
#
# The ith worker is less efficient than the jth worker if either condition is met:
#
#
# 	lefti + righti > leftj + rightj
# 	lefti + righti == leftj + rightj and i > j
#
#
# The following rules regulate the movement of the workers through the bridge:
#
#
# 	Only one worker can use the bridge at a time.
# 	When the bridge is unused prioritize the least efficient worker (who have picked up the box) on the right side to cross. If not, prioritize the least efficient worker on the left side to cross.
# 	If enough workers have already been dispatched from the left side to pick up all the remaining boxes, no more workers will be sent from the left side.
#
#
# Return the elapsed minutes at which the last box reaches the left side of the bridge.
#
# Example:
# Input: n = 1, k = 3, time = [[1,1,2,1],[1,1,3,1],[1,1,4,1]]
#
# Output: 6
#
# Explanation:
#
#
# From 0 to 1 minutes: worker 2 crosses the bridge to the right.
# From 1 to 2 minutes: worker 2 picks up a box from the right warehouse.
# From 2 to 6 minutes: worker 2 crosses the bridge to the left.
# From 6 to 7 minutes: worker 2 puts a box at the left warehouse.
# The whole process ends after 7 minutes. We return 6 because the problem asks for the instance of time at which the last worker reaches the left side of the bridge.
#
# Constraints:
# 1 <= n, k <= 104
# 	time.length == k
# 	time[i].length == 4
# 	1 <= lefti, picki, righti, puti <= 1000
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findCrossingTime(self, n, k, time):
        """
        :type n: int
        :type k: int
        :type time: List[List[int]]
        :rtype: int
        """
        # Step 1: Calculate efficiency and sort workers
        workers = sorted([(time[i][0] + time[i][2], i) for i in range(k)], reverse=True)

        # Step 2: Initialize variables
        left_heap = []  # Workers on the left side (available to cross)
        right_heap = []  # Workers on the right side (available to cross)
        current_time = 0
        boxes_moved = 0

        # Step 3: Simulate the process
        while boxes_moved < n:
            # Move workers from right to left if they are available
            while right_heap and right_heap[0][0] <= current_time:
                _, worker_index = heapq.heappop(right_heap)
                heapq.heappush(left_heap, (workers[worker_index][0], worker_index))

            # Move workers from left to right if they are available and we still have boxes to move
            while left_heap and boxes_moved < n:
                _, worker_index = heapq.heappop(left_heap)
                heapq.heappush(right_heap, (current_time + time[worker_index][0], worker_index))
                current_time += time[worker_index][0] + time[worker_index][1] + time[worker_index][2] + time[worker_index][3]
                boxes_moved += 1

            # If no workers are available, move time forward to the next available worker
            if not left_heap and not right_heap:
                current_time += 1

        return current_time - time[workers[right_heap[0][1]][1]][2] if right_heap else current_time