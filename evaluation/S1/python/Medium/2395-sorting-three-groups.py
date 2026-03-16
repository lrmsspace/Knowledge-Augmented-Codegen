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
# - Longest increasing subsequence (array, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
#   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
#   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
#   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
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
        
        # Count occurrences of 1s, 2s, and 3s
        count1 = nums.count(1)
        count2 = nums.count(2)
        count3 = nums.count(3)
        
        # Define segments based on counts
        seg1 = nums[:count1]
        seg2 = nums[count1:count1 + count2]
        seg3 = nums[count1 + count2:]
        
        # Count misplacements in each segment
        misplace_1_in_2 = seg2.count(1)
        misplace_1_in_3 = seg3.count(1)
        misplace_2_in_1 = seg1.count(2)
        misplace_2_in_3 = seg3.count(2)
        misplace_3_in_1 = seg1.count(3)
        misplace_3_in_2 = seg2.count(3)
        
        # Direct swaps between segments
        swap_12 = min(misplace_1_in_2, misplace_2_in_1)
        swap_13 = min(misplace_1_in_3, misplace_3_in_1)
        swap_23 = min(misplace_2_in_3, misplace_3_in_2)
        
        # Remaining misplacements after direct swaps
        rem_1_in_2 = misplace_1_in_2 - swap_12
        rem_2_in_1 = misplace_2_in_1 - swap_12
        rem_1_in_3 = misplace_1_in_3 - swap_13
        rem_3_in_1 = misplace_3_in_1 - swap_13
        rem_2_in_3 = misplace_2_in_3 - swap_23
        rem_3_in_2 = misplace_3_in_2 - swap_23
        
        # Each remaining misplacement requires two operations (cycle)
        total_operations = (swap_12 + swap_13 + swap_23) + 2 * (rem_1_in_2 + rem_1_in_3)
        
        return total_operations