# Source: https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums consisting of integers. You are also given a 2D array queries, where queries[i] = [posi, xi].
#
# For query i, we first set nums[posi] equal to xi, then we calculate the answer to query i which is the maximum sum of a subsequence of nums where no two adjacent elements are selected.
#
# Return the sum of the answers to all queries.
#
# Since the final answer may be very large, return it modulo 109 + 7.
#
# A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: nums = [3,5,9], queries = [[1,-2],[0,-3]]
#
# Output: 21
#
# Explanation:
# After the 1st query, nums = [3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 3 + 9 = 12.
# After the 2nd query, nums = [-3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 9.
#
# Constraints:
# 1 <= nums.length <= 5 * 104
# 	-105 <= nums[i] <= 105
# 	1 <= queries.length <= 5 * 104
# 	queries[i] == [posi, xi]
# 	0 <= posi <= nums.length - 1
# 	-105 <= xi <= 105
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
#   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
#   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
#   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
#   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
#   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
# - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
#   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
#   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
#   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
#   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
#   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
# - Factorial modulo 
# p (number, array, recursion, mod-exp, dp-1d)
#   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
#   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
#   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
#   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
#   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumSumSubsequence(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: int
        """
        # Step 1: Precompute the maximum sum of a subsequence with non-adjacent elements for the initial array
        n = len(nums)
        if n == 0:
            return 0
        
        # dp[i] will store the maximum sum of a subsequence with non-adjacent elements from nums[0] to nums[i]
        dp = [0] * n
        dp[0] = max(0, nums[0])  # We can choose to take the first element or not
        if n > 1:
            dp[1] = max(dp[0], nums[1])  # We can choose to take the second element or not
        
        for i in range(2, n):
            dp[i] = max(dp[i-1], nums[i] + dp[i-2])  # Either skip current or take current + best from i-2
        
        total_sum = sum(dp) % (10**9 + 7)  # Initial total sum of answers for all queries
        
        # Step 2: Process each query and update the total sum accordingly
        for posi, xi in queries:
            old_value = nums[posi]
            nums[posi] = xi
            
            # Update dp array based on the change at position posi
            if posi == 0:
                dp[0] = max(0, nums[0])
                if n > 1:
                    dp[1] = max(dp[0], nums[1])
            elif posi == 1:
                dp[1] = max(dp[0], nums[1])
            else:
                for i in range(posi, min(posi + 2, n)):
                    if i == posi:
                        dp[i] = max(dp[i-1], nums[i] + (dp[i-2] if i >= 2 else 0))
                    else:
                        dp[i] = max(dp[i-1], nums[i] + (dp[i-2] if i >= 2 else 0))
            
            total_sum = (total_sum + dp[-1]) % (10**9 + 7)  # Add the new answer after each query
        
        return total_sum