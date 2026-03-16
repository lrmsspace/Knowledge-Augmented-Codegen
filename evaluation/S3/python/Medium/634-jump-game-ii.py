# Source: https://leetcode.com/problems/jump-game-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array of integers nums of length n. You are initially positioned at index 0.
#
# Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at index i, you can jump to any index (i + j) where:
#
#
# 	0 <= j <= nums[i] and
# 	i + j < n
#
#
# Return the minimum number of jumps to reach index n - 1. The test cases are generated such that you can reach index n - 1.
#
# Example:
# Input: nums = [2,3,1,1,4]
# Output: 2
# Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
#
# Constraints:
# 1 <= nums.length <= 104
# 	0 <= nums[i] <= 1000
# 	It's guaranteed that you can reach nums[n - 1].
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
#   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
#   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
#   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
# - Longest Increasing Subsequence (array, dp-1d)
#   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
#   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
#   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
#   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
# - Longest increasing subsequence (array, greedy, dp-1d)
#   • When to use: Use when finding the longest sequence of elements in a given array such that each element is greater than the preceding one, without changing their relative order. It's applicable for optimizing problems involving ordered subsets.
#   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of an array where elements are in strictly increasing order. It can be solved in O(N log N) time using a greedy approach with binary search, or O(N^2) using dynamic programming.
#   • Invariants: The 'tails' array elements are always in strictly increasing order.; tails[i] stores the smallest possible ending element of an increasing subsequence of length i+1.
#   • Tips: Prefer the O(N log N) greedy approach with binary search for better performance.; The 'tails' array in the greedy approach stores the smallest tail of all increasing subsequences of a certain length.
#   • Pitfalls: Confusing LIS with Longest Common Subsequence (LCS) or contiguous subarrays.; Incorrectly handling duplicate elements when 'strictly increasing' is required.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def jump(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        jumps = 0
        current_end = 0
        farthest = 0

        for i in range(len(nums) - 1):
            farthest = max(farthest, i + nums[i])
            if i == current_end:
                jumps += 1
                current_end = farthest

        return jumps