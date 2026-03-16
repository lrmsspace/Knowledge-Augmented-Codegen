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
# Helpful references (internal KB):
# - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
#   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
#   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
#   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
#   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
#   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
# - Priority Queues (array, heap, heap-select)
#   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
#   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
#   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
#   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
#   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def totalCost(self, costs, k, candidates):
        """
        :type costs: List[int]
        :type k: int
        :type candidates: int
        :rtype: int
        """
        import heapq

        n = len(costs)
        total_cost = 0

        left_heap = []
        right_heap = []

        left_index = 0
        right_index = n - 1

        for _ in range(k):
            while len(left_heap) < candidates and left_index <= right_index:
                heapq.heappush(left_heap, costs[left_index])
                left_index += 1

            while len(right_heap) < candidates and left_index <= right_index:
                heapq.heappush(right_heap, costs[right_index])
                right_index -= 1

            if left_heap and (not right_heap or left_heap[0] <= right_heap[0]):
                total_cost += heapq.heappop(left_heap)
            else:
                total_cost += heapq.heappop(right_heap)

        return total_cost