# Source: https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/   |   Difficulty: Hard
#
# Problem Description:
# You may recall that an array arr is a mountain array if and only if:
#
#
# 	arr.length >= 3
# 	There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
# 	
# 		arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
# 		arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
# 	
# 	
#
#
# Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.
#
# Example:
# Input: nums = [1,3,1]
# Output: 0
# Explanation: The array itself is a mountain array so we do not need to remove any elements.
#
# Constraints:
# 3 <= nums.length <= 1000
# 	1 <= nums[i] <= 109
# 	It is guaranteed that you can make a mountain array out of nums.
#
# Helpful references (internal KB):
# - Longest Increasing Subsequence (array, dp-1d)
#   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
#   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
#   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
#   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumMountainRemovals(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n < 3:
            return 0

        # Step 1: Calculate the longest increasing subsequence (LIS) from the left
        left_lis = [1] * n
        for i in range(n):
            for j in range(i):
                if nums[j] < nums[i]:
                    left_lis[i] = max(left_lis[i], left_lis[j] + 1)

        # Step 2: Calculate the longest decreasing subsequence (LDS) from the right
        right_lds = [1] * n
        for i in range(n - 1, -1, -1):
            for j in range(n - 1, i, -1):
                if nums[j] < nums[i]:
                    right_lds[i] = max(right_lds[i], right_lds[j] + 1)

        # Step 3: Find the maximum length of a valid mountain array
        max_mountain_length = 0
        for i in range(1, n - 1):
            if left_lis[i] > 1 and right_lds[i] > 1:  # Valid peak
                max_mountain_length = max(max_mountain_length, left_lis[i] + right_lds[i] - 1)

        # Step 4: Calculate minimum removals
        return n - max_mountain_length