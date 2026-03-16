# Source: https://leetcode.com/problems/peaks-in-array/   |   Difficulty: Hard
#
# Problem Description:
# A peak in an array arr is an element that is greater than its previous and next element in arr.
#
# You are given an integer array nums and a 2D integer array queries.
#
# You have to process queries of two types:
#
#
# 	queries[i] = [1, li, ri], determine the count of peak elements in the subarray nums[li..ri].
# 	queries[i] = [2, indexi, vali], change nums[indexi] to vali.
#
#
# Return an array answer containing the results of the queries of the first type in order.
#
# Notes:
#
#
# 	The first and the last element of an array or a subarray cannot be a peak.
#
# Example:
# Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]
#
# Output: [0]
#
# Explanation:
#
# First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].
#
# Second query: The number of peaks in the [3,1,4,4,5] is 0.
#
# Constraints:
# 3 <= nums.length <= 105
# 	1 <= nums[i] <= 105
# 	1 <= queries.length <= 105
# 	queries[i][0] == 1 or queries[i][0] == 2
# 	For all i that:
# 	
# 		queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
# 		queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 105
#
# Helpful references (internal KB):
# - Segment Tree (tree, array, segment-tree, divide-and-conquer)
#   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
#   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
#   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
#   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
#   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
# - MEX (minimal excluded) of a sequence (ds, enumeration)
#   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
#   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
#   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
#   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
#   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countOfPeaks(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(nums)

        # Function to check if an index is a peak
        def is_peak(i):
            return 0 < i < n - 1 and nums[i] > nums[i - 1] and nums[i] > nums[i + 1]

        # Precompute peaks
        peaks = [0] * n
        for i in range(1, n - 1):
            peaks[i] = peaks[i - 1] + (1 if is_peak(i) else 0)
        peaks[n - 1] = peaks[n - 2]

        result = []
        for query in queries:
            if query[0] == 1:
                l, r = query[1], query[2]
                count = peaks[r - 1] - peaks[l]
                result.append(count)
            else:
                index, value = query[1], query[2]
                nums[index] = value
                # Update peaks around the changed index
                for i in range(max(1, index - 1), min(n - 1, index + 2)):
                    peaks[i] = peaks[i - 1] + (1 if is_peak(i) else 0)
                for i in range(index + 2, n):
                    peaks[i] = peaks[i - 1] + (1 if is_peak(i) else 0)

        return result