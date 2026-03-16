# Source: https://leetcode.com/problems/maximum-balanced-subsequence-sum/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums.
#
# A subsequence of nums having length k and consisting of indices i0 < i1 < ... < ik-1 is balanced if the following holds:
#
#
# 	nums[ij] - nums[ij-1] >= ij - ij-1, for every j in the range [1, k - 1].
#
#
# A subsequence of nums having length 1 is considered balanced.
#
# Return an integer denoting the maximum possible sum of elements in a balanced subsequence of nums.
#
# A subsequence of an array is a new non-empty array that is formed from the original array by deleting some (possibly none) of the elements without disturbing the relative positions of the remaining elements.
#
# Example:
# Input: nums = [3,3,5,6]
# Output: 14
# Explanation: In this example, the subsequence [3,5,6] consisting of indices 0, 2, and 3 can be selected.
# nums[2] - nums[0] >= 2 - 0.
# nums[3] - nums[2] >= 3 - 2.
# Hence, it is a balanced subsequence, and its sum is the maximum among the balanced subsequences of nums.
# The subsequence consisting of indices 1, 2, and 3 is also valid.
# It can be shown that it is not possible to get a balanced subsequence with a sum greater than 14.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
#
# Helpful references (internal KB):
# - Segment Tree (tree, array, segment-tree, divide-and-conquer)
#   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
#   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
#   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
#   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
#   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
# - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
#   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
#   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
#   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
#   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
#   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
# - Balanced bracket sequences (number, counting)
#   • When to use: Use when the problem asks for the total number of valid arrangements of opening and closing brackets, ensuring all pairs are matched and correctly nested. It applies to combinatorial problems requiring structured pairing.
#   • Idea: This technique counts the number of ways to form sequences of opening and closing brackets such that they are balanced and properly nested. It is a classic combinatorial problem, typically solved in O(N) or O(N^2) time.
#   • Invariants: At any point in sequence construction, the count of open brackets placed must be greater than or equal to the count of closed brackets placed.; The total number of open brackets in a complete valid sequence must exactly equal the total number of closed brackets.
#   • Tips: Recognize the connection to Catalan numbers for common variations (e.g., N pairs of parentheses).; Dynamic programming can solve more complex variations with different bracket types or constraints.
#   • Pitfalls: Forgetting the 'prefix sum' condition: the count of open brackets must always be greater than or equal to close brackets at any point.; Incorrectly applying Catalan numbers to problems with additional constraints or different bracket types.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxBalancedSubsequenceSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        dp = [0] * n
        dp[0] = nums[0]

        for i in range(1, n):
            dp[i] = max(dp[i-1], nums[i])
            for j in range(i-1, -1, -1):
                if nums[i] - nums[j] >= i - j:
                    dp[i] = max(dp[i], dp[j] + nums[i])
                else:
                    break

        return max(dp)