# Source: https://leetcode.com/problems/minimum-cost-to-divide-array-into-subarrays/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integer arrays, nums and cost, of the same size, and an integer k.
#
# You can divide nums into subarrays. The cost of the ith subarray consisting of elements nums[l..r] is:
#
#
# 	(nums[0] + nums[1] + ... + nums[r] + k * i) * (cost[l] + cost[l + 1] + ... + cost[r]).
#
#
# Note that i represents the order of the subarray: 1 for the first subarray, 2 for the second, and so on.
#
# Return the minimum total cost possible from any valid division.
#
# Example:
# Input: nums = [3,1,4], cost = [4,6,6], k = 1
#
# Output: 110
#
# Explanation:
# The minimum total cost possible can be achieved by dividing nums into subarrays [3, 1] and [4].
#
#
# 	The cost of the first subarray [3,1] is (3 + 1 + 1 * 1) * (4 + 6) = 50.
# 	The cost of the second subarray [4] is (3 + 1 + 4 + 1 * 2) * 6 = 60.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	cost.length == nums.length
# 	1 <= nums[i], cost[i] <= 1000
# 	1 <= k <= 1000
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
# - Convex hull trick and Li Chao tree (array, number, dp-1d)
#   • When to use: Use when the optimal solution for a subproblem depends only on solutions to smaller, contiguous subproblems. It's effective for optimizing sequential decision-making or finding optimal values in arrays.
#   • Idea: Dynamic Programming 1D solves problems by breaking them into overlapping subproblems and storing results to avoid recomputation. It typically achieves O(N) or O(N log N) time and O(N) or O(1) space complexity.
#   • Invariants: dp[i] correctly stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been computed and are correct.
#   • Tips: Clearly define the state: what does dp[i] represent for the subproblem?; Establish correct base cases for the smallest subproblems.
#   • Pitfalls: Incorrectly defining the state or recurrence relation.; Missing or incorrect base cases, leading to incorrect results.
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumCost(self, nums, cost, k):
        """
        :type nums: List[int]
        :type cost: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        prefix_nums = [0] * (n + 1)
        prefix_cost = [0] * (n + 1)

        for i in range(n):
            prefix_nums[i + 1] = prefix_nums[i] + nums[i]
            prefix_cost[i + 1] = prefix_cost[i] + cost[i]

        dp = [float('inf')] * (n + 1)
        dp[0] = 0

        for i in range(1, n + 1):
            for j in range(i):
                subarray_cost = (prefix_nums[i] - prefix_nums[j] + k * (len(dp) - i)) * (prefix_cost[i] - prefix_cost[j])
                dp[i] = min(dp[i], dp[j] + subarray_cost)

        return dp[n]