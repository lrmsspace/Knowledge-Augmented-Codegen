# Source: https://leetcode.com/problems/intervals-between-identical-elements/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array of n integers arr.
#
# The interval between two elements in arr is defined as the absolute difference between their indices. More formally, the interval between arr[i] and arr[j] is |i - j|.
#
# Return an array intervals of length n where intervals[i] is the sum of intervals between arr[i] and each element in arr with the same value as arr[i].
#
# Note: |x| is the absolute value of x.
#
# Example:
# Input: arr = [2,1,3,1,2,3,3]
# Output: [4,2,7,2,4,4,5]
# Explanation:
# - Index 0: Another 2 is found at index 4. |0 - 4| = 4
# - Index 1: Another 1 is found at index 3. |1 - 3| = 2
# - Index 2: Two more 3s are found at indices 5 and 6. |2 - 5| + |2 - 6| = 7
# - Index 3: Another 1 is found at index 1. |3 - 1| = 2
# - Index 4: Another 2 is found at index 0. |4 - 0| = 4
# - Index 5: Two more 3s are found at indices 2 and 6. |5 - 2| + |5 - 6| = 4
# - Index 6: Two more 3s are found at indices 2 and 5. |6 - 2| + |6 - 5| = 5
#
# Constraints:
# n == arr.length
# 	1 <= n <= 105
# 	1 <= arr[i] <= 105
#
#
#  
# Note: This question is the same as  2615: Sum of Distances.
#
# Helpful references (internal KB):
# - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
#   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
#   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
#   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
#   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
#   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
# - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
#   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
#   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
#   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
#   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
#   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getDistances(self, arr):
        """
        :type arr: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict

        index_map = defaultdict(list)
        n = len(arr)
        result = [0] * n

        # Collect indices for each value
        for i, value in enumerate(arr):
            index_map[value].append(i)

        # Calculate distances for each group of identical elements
        for indices in index_map.values():
            m = len(indices)
            if m == 1:
                continue

            # Prefix sums to calculate distances efficiently
            prefix_sum = [0] * (m + 1)
            for i in range(m):
                prefix_sum[i + 1] = prefix_sum[i] + indices[i]

            for i in range(m):
                left_count = i
                right_count = m - i - 1
                left_sum = prefix_sum[i]
                right_sum = prefix_sum[m] - prefix_sum[i + 1]

                result[indices[i]] = (indices[i] * left_count - left_sum) + (right_sum - indices[i] * right_count)

        return result