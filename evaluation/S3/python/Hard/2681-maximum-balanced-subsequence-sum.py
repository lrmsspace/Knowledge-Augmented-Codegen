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
# - Sqrt Decomposition (array, enumeration, prefix-sum)
#   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
#   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
#   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
#   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
#   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
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