# Source: https://leetcode.com/problems/zero-array-transformation-iv/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of length n and a 2D array queries, where queries[i] = [li, ri, vali].
#
# Each queries[i] represents the following action on nums:
#
#
# 	Select a subset of indices in the range [li, ri] from nums.
# 	Decrement the value at each selected index by exactly vali.
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
# 	For query 0 (l = 0, r = 2, val = 1):
#
# 	
# 		Decrement the values at indices [0, 2] by 1.
# 		The array will become [1, 0, 1].
# 	
# 	
# 	For query 1 (l = 0, r = 2, val = 1):
# 	
# 		Decrement the values at indices [0, 2] by 1.
# 		The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.
#
# Constraints:
# 1 <= nums.length <= 10
# 	0 <= nums[i] <= 1000
# 	1 <= queries.length <= 1000
# 	queries[i] = [li, ri, vali]
# 	0 <= li <= ri < nums.length
# 	1 <= vali <= 10
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
#   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
#   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
#   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
#   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
#   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
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

        def can_make_zero_array(k):
            diff = [0] * (n + 1)

            for i in range(k):
                l, r, val = queries[i]
                diff[l] += val
                if r + 1 < n:
                    diff[r + 1] -= val

            current = 0
            for i in range(n):
                current += diff[i]
                if current > nums[i]:
                    return False
            return True

        left, right = 0, m
        answer = -1

        while left <= right:
            mid = (left + right) // 2
            if can_make_zero_array(mid):
                answer = mid
                right = mid - 1
            else:
                left = mid + 1

        return answer