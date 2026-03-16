# Source: https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and an integer k. Your task is to partition nums into one or more non-empty contiguous segments such that in each segment, the difference between its maximum and minimum elements is at most k.
#
# Return the total number of ways to partition nums under this condition.
#
# Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [9,4,1,3,7], k = 4
#
# Output: 6
#
# Explanation:
#
# There are 6 valid partitions where the difference between the maximum and minimum elements in each segment is at most k = 4:
#
#
# 	[[9], [4], [1], [3], [7]]
# 	[[9], [4], [1], [3, 7]]
# 	[[9], [4], [1, 3], [7]]
# 	[[9], [4, 1], [3], [7]]
# 	[[9], [4, 1], [3, 7]]
# 	[[9], [4, 1, 3], [7]]
#
# Constraints:
# 2 <= nums.length <= 5 * 104
# 	1 <= nums[i] <= 109
# 	0 <= k <= 109
#
# Helpful references (internal KB):
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
# - Longest Increasing Subsequence (array, dp-1d)
#   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
#   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
#   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
#   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countPartitions(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        
        total_ways = pow(2, n - 1, MOD)
        
        dp = [0] * (n + 1)
        dp[0] = 1
        
        left = 0
        curr_min = nums[0]
        curr_max = nums[0]
        
        for right in range(n):
            curr_min = min(curr_min, nums[right])
            curr_max = max(curr_max, nums[right])
            
            while curr_max - curr_min > k:
                dp[right + 1] = (dp[right + 1] - dp[left]) % MOD
                left += 1
                curr_min = min(nums[left:right + 1])
                curr_max = max(nums[left:right + 1])
            
            dp[right + 1] = (dp[right + 1] + dp[right]) % MOD
        
        invalid_ways = (dp[n] - dp[left]) % MOD
        
        return (total_ways - invalid_ways + MOD) % MOD