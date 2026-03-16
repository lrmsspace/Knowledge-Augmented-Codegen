# Source: https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-i/   |   Difficulty: Easy
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
# 1 <= nums.length <= 50
# 	1 <= nums[i] <= 50
#

class Solution(object):
    def incremovableSubarrayCount(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        left = [0] * n
        right = [0] * n
        
        left[0] = 1
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                left[i] = left[i - 1] + 1
            else:
                left[i] = 1
        
        right[n - 1] = 1
        for i in range(n - 2, -1, -1):
            if nums[i] < nums[i + 1]:
                right[i] = right[i + 1] + 1
            else:
                right[i] = 1
        
        total_subarrays = n * (n + 1) // 2
        non_incremovable_count = 0
        
        for i in range(n):
            non_incremovable_count += left[i] * right[i]
            if i > 0 and i < n - 1 and nums[i - 1] < nums[i + 1]:
                non_incremovable_count -= left[i - 1] * right[i + 1]
        
        return total_subarrays - non_incremovable_count