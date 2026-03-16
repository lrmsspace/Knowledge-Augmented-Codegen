# Source: https://leetcode.com/problems/k-th-nearest-obstacle-queries/   |   Difficulty: Medium
#
# Problem Description:
# There is an infinite 2D plane.
#
# You are given a positive integer k. You are also given a 2D array queries, which contains the following queries:
#
#
# 	queries[i] = [x, y]: Build an obstacle at coordinate (x, y) in the plane. It is guaranteed that there is no obstacle at this coordinate when this query is made.
#
#
# After each query, you need to find the distance of the kth nearest obstacle from the origin.
#
# Return an integer array results where results[i] denotes the kth nearest obstacle after query i, or results[i] == -1 if there are less than k obstacles.
#
# Note that initially there are no obstacles anywhere.
#
# The distance of an obstacle at coordinate (x, y) from the origin is given by |x| + |y|.
#
# Example:
# Input: queries = [[1,2],[3,4],[2,3],[-3,0]], k = 2
#
# Output: [-1,7,5,3]
#
# Explanation:
#
#
# 	Initially, there are 0 obstacles.
# 	After queries[0], there are less than 2 obstacles.
# 	After queries[1], there are obstacles at distances 3 and 7.
# 	After queries[2], there are obstacles at distances 3, 5, and 7.
# 	After queries[3], there are obstacles at distances 3, 3, 5, and 7.
#
# Constraints:
# 1 <= queries.length <= 2 * 105
# 	All queries[i] are unique.
# 	-109 <= queries[i][0], queries[i][1] <= 109
# 	1 <= k <= 105
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
    def resultsArray(self, queries, k):
        """
        :type queries: List[List[int]]
        :type k: int
        :rtype: List[int]
        """
        import heapq

        max_heap = []  # Max-heap to store the k nearest distances
        results = []

        for x, y in queries:
            distance = abs(x) + abs(y)

            if len(max_heap) < k:
                heapq.heappush(max_heap, -distance)  # Push negative for max-heap
            else:
                if distance < -max_heap[0]:  # If the new distance is smaller than the largest in the heap
                    heapq.heapreplace(max_heap, -distance)

            if len(max_heap) < k:
                results.append(-1)
            else:
                results.append(-max_heap[0])  # The kth nearest distance is the largest in the max-heap

        return results