# Source: https://leetcode.com/problems/maximum-sum-queries/   |   Difficulty: Hard
#
# Problem Description:
# You are given two 0-indexed integer arrays nums1 and nums2, each of length n, and a 1-indexed 2D array queries where queries[i] = [xi, yi].
#
# For the ith query, find the maximum value of nums1[j] + nums2[j] among all indices j (0 <= j < n), where nums1[j] >= xi and nums2[j] >= yi, or -1 if there is no j satisfying the constraints.
#
# Return an array answer where answer[i] is the answer to the ith query.
#
# Example:
# Input: nums1 = [4,3,1,2], nums2 = [2,4,9,5], queries = [[4,1],[1,3],[2,5]]
# Output: [6,10,7]
# Explanation: 
# For the 1st query xi = 4 and yi = 1, we can select index j = 0 since nums1[j] >= 4 and nums2[j] >= 1. The sum nums1[j] + nums2[j] is 6, and we can show that 6 is the maximum we can obtain.
#
# For the 2nd query xi = 1 and yi = 3, we can select index j = 2 since nums1[j] >= 1 and nums2[j] >= 3. The sum nums1[j] + nums2[j] is 10, and we can show that 10 is the maximum we can obtain. 
#
# For the 3rd query xi = 2 and yi = 5, we can select index j = 3 since nums1[j] >= 2 and nums2[j] >= 5. The sum nums1[j] + nums2[j] is 7, and we can show that 7 is the maximum we can obtain.
#
# Therefore, we return [6,10,7].
#
# Constraints:
# nums1.length == nums2.length 
# 	n == nums1.length 
# 	1 <= n <= 105
# 	1 <= nums1[i], nums2[i] <= 109 
# 	1 <= queries.length <= 105
# 	queries[i].length == 2
# 	xi == queries[i][1]
# 	yi == queries[i][2]
# 	1 <= xi, yi <= 109
#
# Helpful references (internal KB):
# - Segment Tree (tree, array, segment-tree, divide-and-conquer)
#   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
#   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
#   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
#   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
#   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
# - Point location in O(logn) (geometry, ds, simulation)
#   • When to use: Use when needing to efficiently determine which region (face or edge) of a planar subdivision a given query point lies within, especially for multiple online queries.
#   • Idea: This algorithm preprocesses a planar subdivision to answer point location queries in logarithmic time. It typically involves building a specialized data structure, possibly persistent, to quickly identify the containing face or edge for any given point.
#   • Invariants: The search process always maintains the invariant that the query point is within the current candidate region.; After each step, the search space for the point's location is reduced by a constant factor.
#   • Tips: Use a suitable geometric data structure like a trapezoidal map or persistent segment tree.; Carefully handle points lying exactly on edges or vertices.
#   • Pitfalls: Degenerate cases (vertical edges, collinear points) require careful handling.; Floating-point precision errors can lead to incorrect classifications.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumSumQueries(self, nums1, nums2, queries):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # Step 1: Preprocess nums1 and nums2 into a list of pairs and sort by nums1 in descending order
        pairs = sorted(zip(nums1, nums2), key=lambda x: x[0], reverse=True)

        # Step 2: Sort queries by xi in descending order and keep track of original indices
        indexed_queries = sorted(enumerate(queries), key=lambda x: x[1][0], reverse=True)

        # Step 3: Use a max-heap to maintain the maximum nums2[j] for valid j
        import heapq
        max_heap = []
        results = [-1] * len(queries)
        j = 0

        for idx, (xi, yi) in indexed_queries:
            # Add all pairs with nums1[j] >= xi to the max-heap
            while j < len(pairs) and pairs[j][0] >= xi:
                heapq.heappush(max_heap, -pairs[j][1])  # Push negative to simulate max-heap
                j += 1
            
            # Remove elements from the heap that do not satisfy nums2[j] >= yi
            while max_heap and -max_heap[0] < yi:
                heapq.heappop(max_heap)
            
            # If the heap is not empty, the top element is the maximum nums2[j]
            if max_heap:
                results[idx] = -max_heap[0] + xi  # Add xi to get the sum

        return results