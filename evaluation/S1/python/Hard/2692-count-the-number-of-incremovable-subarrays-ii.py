# Source: https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed array of positive integers nums.
#
# A subarray of nums is called incremovable if nums becomes strictly increasing on removing the subarray. For example, the subarray [3, 4] is an incremovable subarray of [5, 3, 4, 6, 7] because removing this subarray changes the array [5, 3, 4, 6, 7] to [5, 6, 7] which is strictly increasing.
#
# Return the total number of incremovable subarrays of nums.
#
# Note that an empty array is considered strictly increasing.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [1,2,3,4]
# Output: 10
# Explanation: The 10 incremovable subarrays are: [1], [2], [3], [4], [1,2], [2,3], [3,4], [1,2,3], [2,3,4], and [1,2,3,4], because on removing any one of these subarrays nums becomes strictly increasing. Note that you cannot select an empty subarray.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
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
    def incremovableSubarrayCount(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n == 1:
            return 1
        
        # Calculate the length of the longest increasing subarray ending at each index
        inc = [1] * n
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                inc[i] = inc[i - 1] + 1
        
        # Calculate the length of the longest increasing subarray starting at each index
        dec = [1] * n
        for i in range(n - 2, -1, -1):
            if nums[i] < nums[i + 1]:
                dec[i] = dec[i + 1] + 1
        
        # Count the number of incremovable subarrays
        count = 0
        for i in range(n):
            count += inc[i] * dec[i]
        
        return count