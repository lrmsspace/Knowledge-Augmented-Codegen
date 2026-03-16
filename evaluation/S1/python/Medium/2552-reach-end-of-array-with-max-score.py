# Source: https://leetcode.com/problems/reach-end-of-array-with-max-score/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of length n.
#
# Your goal is to start at index 0 and reach index n - 1. You can only jump to indices greater than your current index.
#
# The score for a jump from index i to index j is calculated as (j - i) * nums[i].
#
# Return the maximum possible total score by the time you reach the last index.
#
# Example:
# Input: nums = [1,3,1,5]
#
# Output: 7
#
# Explanation:
#
# First, jump to index 1 and then jump to the last index. The final score is 1 * 1 + 2 * 3 = 7.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#
# Helpful references (internal KB):
# - Convex hull trick and Li Chao tree (array, number, dp-1d)
#   • When to use: Use when the optimal solution for a subproblem depends only on solutions to smaller, contiguous subproblems. It's effective for optimizing sequential decision-making or finding optimal values in arrays.
#   • Idea: Dynamic Programming 1D solves problems by breaking them into overlapping subproblems and storing results to avoid recomputation. It typically achieves O(N) or O(N log N) time and O(N) or O(1) space complexity.
#   • Invariants: dp[i] correctly stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been computed and are correct.
#   • Tips: Clearly define the state: what does dp[i] represent for the subproblem?; Establish correct base cases for the smallest subproblems.
#   • Pitfalls: Incorrectly defining the state or recurrence relation.; Missing or incorrect base cases, leading to incorrect results.
# - Segment Tree (tree, array, segment-tree)
#   • When to use: Use when you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in logarithmic time.
#   • Idea: A Segment Tree is a tree-based data structure that stores information about array intervals, enabling efficient O(log n) range queries and point/range updates.
#   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; The value stored in a non-leaf node is an aggregation of the values from its direct children.
#   • Tips: Build the tree recursively, dividing the array into halves.; Use lazy propagation for efficient range updates to avoid O(N) updates.
#   • Pitfalls: Off-by-one errors when defining segment boundaries or array indices.; Forgetting to push down lazy tags before querying or updating children nodes.
# - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
#   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
#   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
#   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
#   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
#   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findMaximumScore(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        dp = [0] * n
        dp[0] = 0

        from collections import deque

        deq = deque()
        deq.append(0)

        for j in range(1, n):
            while len(deq) >= 2:
                i1 = deq[0]
                i2 = deq[1]
                score1 = dp[i1] + (j - i1) * nums[i1]
                score2 = dp[i2] + (j - i2) * nums[i2]
                if score2 >= score1:
                    deq.popleft()
                else:
                    break

            i = deq[0]
            dp[j] = dp[i] + (j - i) * nums[i]

            while len(deq) >= 2:
                i1 = deq[-2]
                i2 = deq[-1]

                left = (dp[i2] - dp[i1]) * (nums[j] - nums[i2])
                right = (dp[j] - dp[i2]) * (nums[i2] - nums[i1])

                if left >= right:
                    deq.pop()
                else:
                    break

            deq.append(j)

        return dp[-1]