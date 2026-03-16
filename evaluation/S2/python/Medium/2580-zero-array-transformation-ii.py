# Source: https://leetcode.com/problems/zero-array-transformation-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].
#
# Each queries[i] represents the following action on nums:
#
#
# 	Decrement the value at each index in the range [li, ri] in nums by at most vali.
# 	The amount by which each value is decremented can be chosen independently for each index.
#
#
# A Zero Array is an array with all its elements equal to 0.
#
# Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.
#
# Example:
# Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
#
# Output: 2
#
# Explanation:
#
#
# 	For i = 0 (l = 0, r = 2, val = 1):
#
# 	
# 		Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
# 		The array will become [1, 0, 1].
# 	
# 	
# 	For i = 1 (l = 0, r = 2, val = 1):
# 	
# 		Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
# 		The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 5 * 105
# 	1 <= queries.length <= 105
# 	queries[i].length == 3
# 	0 <= li <= ri < nums.length
# 	1 <= vali <= 5
#
# Helpful references (internal KB):
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
# - Sqrt Tree (array, tree, recursion)
#   • When to use: When you need to perform O(1) range queries and support efficient updates (single element or range) on an array, leveraging a hierarchical decomposition.
#   • Idea: A Sqrt Tree is a data structure that supports O(1) range queries and efficient updates on an array. It recursively decomposes the array into blocks and layers, using precomputed information and bitwise operations to quickly answer queries and propagate updates.
#   • Invariants: Each element is part of exactly one block at each layer of the Sqrt Tree.; The highest differing bit between `l` and `r` identifies the specific layer for processing `q(l, r)`.
#   • Tips: Precompute highest bit for efficient layer selection.; Decompose queries into intra-block and inter-block segments.
#   • Pitfalls: Naive updates can result in O(N) complexity per update.; High memory consumption due to multiple layers of precomputed arrays.
# - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
#   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
#   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
#   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
#   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
#   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minZeroArray(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: int
        """
        n = len(nums)
        m = len(queries)

        # Step 1: Calculate the total decrement needed for each index
        total_decrement = [0] * n
        for i in range(n):
            total_decrement[i] = nums[i]

        # Step 2: Process queries in reverse to determine how many times each query is needed
        for i in range(m - 1, -1, -1):
            l, r, val = queries[i]
            for j in range(l, r + 1):
                if total_decrement[j] > 0:
                    decrement_amount = min(val, total_decrement[j])
                    total_decrement[j] -= decrement_amount

        # Step 3: Check if all indices can be reduced to zero
        for i in range(n):
            if total_decrement[i] > 0:
                return -1

        return m