# Source: https://leetcode.com/problems/earliest-second-to-mark-indices-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given two 1-indexed integer arrays, nums and, changeIndices, having lengths n and m, respectively.
#
# Initially, all indices in nums are unmarked. Your task is to mark all indices in nums.
#
# In each second, s, in order from 1 to m (inclusive), you can perform one of the following operations:
#
#
# 	Choose an index i in the range [1, n] and decrement nums[i] by 1.
# 	If nums[changeIndices[s]] is equal to 0, mark the index changeIndices[s].
# 	Do nothing.
#
#
# Return an integer denoting the earliest second in the range [1, m] when all indices in nums can be marked by choosing operations optimally, or -1 if it is impossible.
#
# Example:
# Input: nums = [2,2,0], changeIndices = [2,2,2,2,3,2,2,1]
# Output: 8
# Explanation: In this example, we have 8 seconds. The following operations can be performed to mark all indices:
# Second 1: Choose index 1 and decrement nums[1] by one. nums becomes [1,2,0].
# Second 2: Choose index 1 and decrement nums[1] by one. nums becomes [0,2,0].
# Second 3: Choose index 2 and decrement nums[2] by one. nums becomes [0,1,0].
# Second 4: Choose index 2 and decrement nums[2] by one. nums becomes [0,0,0].
# Second 5: Mark the index changeIndices[5], which is marking index 3, since nums[3] is equal to 0.
# Second 6: Mark the index changeIndices[6], which is marking index 2, since nums[2] is equal to 0.
# Second 7: Do nothing.
# Second 8: Mark the index changeIndices[8], which is marking index 1, since nums[1] is equal to 0.
# Now all indices have been marked.
# It can be shown that it is not possible to mark all indices earlier than the 8th second.
# Hence, the answer is 8.
#
# Constraints:
# 1 <= n == nums.length <= 2000
# 	0 <= nums[i] <= 109
# 	1 <= m == changeIndices.length <= 2000
# 	1 <= changeIndices[i] <= n
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def earliestSecondToMarkIndices(self, nums, changeIndices):
        """
        :type nums: List[int]
        :type changeIndices: List[int]
        :rtype: int
        """
        n = len(nums)
        m = len(changeIndices)

        # Create a list of (value, index) pairs and sort by value
        indexed_nums = sorted([(nums[i], i + 1) for i in range(n)])

        # Create a mapping from index to the earliest second it can be marked
        mark_time = {}
        for i in range(n):
            mark_time[indexed_nums[i][1]] = float('inf')

        # Iterate through changeIndices and update the mark_time for each index
        for second in range(m):
            idx = changeIndices[second]
            if idx in mark_time:
                mark_time[idx] = min(mark_time[idx], second + 1)

        # Calculate the total time required to mark all indices
        total_time = 0
        for value, idx in indexed_nums:
            if value > 0:
                total_time += value
                if mark_time[idx] == float('inf'):
                    return -1  # If any index cannot be marked, return -1

        # The earliest second to mark all indices is the maximum of total_time and the latest mark time
        return max(total_time, max(mark_time.values()))