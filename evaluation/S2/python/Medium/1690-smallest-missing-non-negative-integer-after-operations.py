# Source: https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums and an integer value.
#
# In one operation, you can add or subtract value from any element of nums.
#
#
# 	For example, if nums = [1,2,3] and value = 2, you can choose to subtract value from nums[0] to make nums = [-1,2,3].
#
#
# The MEX (minimum excluded) of an array is the smallest missing non-negative integer in it.
#
#
# 	For example, the MEX of [-1,2,3] is 0 while the MEX of [1,0,3] is 2.
#
#
# Return the maximum MEX of nums after applying the mentioned operation any number of times.
#
# Example:
# Input: nums = [1,-10,7,13,6,8], value = 5
# Output: 4
# Explanation: One can achieve this result by applying the following operations:
# - Add value to nums[1] twice to make nums = [1,0,7,13,6,8]
# - Subtract value from nums[2] once to make nums = [1,0,2,13,6,8]
# - Subtract value from nums[3] twice to make nums = [1,0,2,3,6,8]
# The MEX of nums is 4. It can be shown that 4 is the maximum MEX we can achieve.
#
# Constraints:
# 1 <= nums.length, value <= 105
# 	-109 <= nums[i] <= 109
#
# Helpful references (internal KB):
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
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
    def findSmallestInteger(self, nums, value):
        """
        :type nums: List[int]
        :type value: int
        :rtype: int
        """
        remainder_count = [0] * value

        for num in nums:
            remainder = num % value
            if remainder < 0:
                remainder += value
            remainder_count[remainder] += 1

        for i in range(value):
            if remainder_count[i] == 0:
                return i

        max_count = max(remainder_count)
        for i in range(value):
            if remainder_count[i] == max_count:
                return i + (max_count - 1) * value