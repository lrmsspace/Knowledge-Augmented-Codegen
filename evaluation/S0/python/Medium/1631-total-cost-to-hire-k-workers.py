# Source: https://leetcode.com/problems/total-cost-to-hire-k-workers/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array costs where costs[i] is the cost of hiring the ith worker.
#
# You are also given two integers k and candidates. We want to hire exactly k workers according to the following rules:
#
#
# 	You will run k sessions and hire exactly one worker in each session.
# 	In each hiring session, choose the worker with the lowest cost from either the first candidates workers or the last candidates workers. Break the tie by the smallest index.
# 	
# 		For example, if costs = [3,2,7,7,1,2] and candidates = 2, then in the first hiring session, we will choose the 4th worker because they have the lowest cost [3,2,7,7,1,2].
# 		In the second hiring session, we will choose 1st worker because they have the same lowest cost as 4th worker but they have the smallest index [3,2,7,7,2]. Please note that the indexing may be changed in the process.
# 	
# 	
# 	If there are fewer than candidates workers remaining, choose the worker with the lowest cost among them. Break the tie by the smallest index.
# 	A worker can only be chosen once.
#
#
# Return the total cost to hire exactly k workers.
#
# Example:
# Input: costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
# Output: 11
# Explanation: We hire 3 workers in total. The total cost is initially 0.
# - In the first hiring round we choose the worker from [17,12,10,2,7,2,11,20,8]. The lowest cost is 2, and we break the tie by the smallest index, which is 3. The total cost = 0 + 2 = 2.
# - In the second hiring round we choose the worker from [17,12,10,7,2,11,20,8]. The lowest cost is 2 (index 4). The total cost = 2 + 2 = 4.
# - In the third hiring round we choose the worker from [17,12,10,7,11,20,8]. The lowest cost is 7 (index 3). The total cost = 4 + 7 = 11. Notice that the worker with index 3 was common in the first and last four workers.
# The total hiring cost is 11.
#
# Constraints:
# 1 <= costs.length <= 105 
# 	1 <= costs[i] <= 105
# 	1 <= k, candidates <= costs.length
#

class Solution(object):
    def totalCost(self, costs, k, candidates):
        """
        :type costs: List[int]
        :type k: int
        :type candidates: int
        :rtype: int
        """
        n = len(costs)
        import heapq

        left_heap = []
        right_heap = []

        left_ptr = 0
        right_ptr = n - 1

        for _ in range(candidates):
            if left_ptr <= right_ptr:
                heapq.heappush(left_heap, costs[left_ptr])
                left_ptr += 1
            if left_ptr <= right_ptr:
                heapq.heappush(right_heap, costs[right_ptr])
                right_ptr -= 1

        total_cost = 0

        for _ in range(k):
            if not left_heap:
                chosen_cost = heapq.heappop(right_heap)
                total_cost += chosen_cost
                if left_ptr <= right_ptr:
                    heapq.heappush(right_heap, costs[right_ptr])
                    right_ptr -= 1
            elif not right_heap:
                chosen_cost = heapq.heappop(left_heap)
                total_cost += chosen_cost
                if left_ptr <= right_ptr:
                    heapq.heappush(left_heap, costs[left_ptr])
                    left_ptr += 1
            else:
                if left_heap[0] <= right_heap[0]:
                    chosen_cost = heapq.heappop(left_heap)
                    total_cost += chosen_cost
                    if left_ptr <= right_ptr:
                        heapq.heappush(left_heap, costs[left_ptr])
                        left_ptr += 1
                else:
                    chosen_cost = heapq.heappop(right_heap)
                    total_cost += chosen_cost
                    if left_ptr <= right_ptr:
                        heapq.heappush(right_heap, costs[right_ptr])
                        right_ptr -= 1

        return total_cost