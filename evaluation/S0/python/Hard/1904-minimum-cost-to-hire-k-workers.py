# Source: https://leetcode.com/problems/minimum-cost-to-hire-k-workers/   |   Difficulty: Hard
#
# Problem Description:
# There are n workers. You are given two integer arrays quality and wage where quality[i] is the quality of the ith worker and wage[i] is the minimum wage expectation for the ith worker.
#
# We want to hire exactly k workers to form a paid group. To hire a group of k workers, we must pay them according to the following rules:
#
#
# 	Every worker in the paid group must be paid at least their minimum wage expectation.
# 	In the group, each worker's pay must be directly proportional to their quality. This means if a worker’s quality is double that of another worker in the group, then they must be paid twice as much as the other worker.
#
#
# Given the integer k, return the least amount of money needed to form a paid group satisfying the above conditions. Answers within 10-5 of the actual answer will be accepted.
#
# Example:
# Input: quality = [10,20,5], wage = [70,50,30], k = 2
# Output: 105.00000
# Explanation: We pay 70 to 0th worker and 35 to 2nd worker.
#
# Constraints:
# n == quality.length == wage.length
# 	1 <= k <= n <= 104
# 	1 <= quality[i], wage[i] <= 104
#

class Solution(object):
    def mincostToHireWorkers(self, quality, wage, k):
        """
        :type quality: List[int]
        :type wage: List[int]
        :type k: int
        :rtype: float
        """
        workers = sorted([(w / q, q) for q, w in zip(quality, wage)])
        import heapq
        heap = []
        total_quality = 0
        min_cost = float('inf')

        for ratio, q in workers:
            heapq.heappush(heap, -q)
            total_quality += q

            if len(heap) > k:
                total_quality += heapq.heappop(heap)

            if len(heap) == k:
                min_cost = min(min_cost, ratio * total_quality)

        return min_cost