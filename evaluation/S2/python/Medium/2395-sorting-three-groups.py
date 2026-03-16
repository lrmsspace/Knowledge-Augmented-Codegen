# Source: https://leetcode.com/problems/sorting-three-groups/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums. Each element in nums is 1, 2 or 3. In each operation, you can remove an element from nums. Return the minimum number of operations to make nums non-decreasing.
#
# Example:
# Input: nums = [2,1,3,2,1]
#
# Output: 3
#
# Explanation:
#
# One of the optimal solutions is to remove nums[0], nums[2] and nums[3].
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 3
#
#
#  
# Follow-up: Can you come up with an algorithm that runs in O(n) time complexity?
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
#   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
#   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
#   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
#   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
#   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
# - Ternary Search (interval, number, binary-search, enumeration)
#   • When to use: Use Ternary Search to find the minimum or maximum of a unimodal or bitonic function over a continuous or discrete interval. It is effective when the function's derivative is hard to compute or unavailable.
#   • Idea: Ternary search is a divide and conquer algorithm that repeatedly narrows down the search space for the extremum of a unimodal function by evaluating two points within the current interval. It reduces the search interval by one-third in each step, achieving O(log N) time complexity.
#   • Invariants: The extremum of the unimodal function lies within the current interval [l, r].; The function value at m1 is compared with m2 to narrow the search.
#   • Tips: Ensure the function is strictly unimodal or bitonic within the search range.; Handle floating-point precision carefully for continuous functions.
#   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Floating-point errors can lead to incorrect bounds or infinite loops.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        dp = [[0] * 4 for _ in range(n + 1)]

        for i in range(1, n + 1):
            for j in range(1, 4):
                dp[i][j] = dp[i - 1][j] + (nums[i - 1] != j)
                if j > 1:
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (nums[i - 1] != j))

        return min(dp[n][1], dp[n][2], dp[n][3])