# Source: https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums. The value of this array is defined as the sum of |nums[i] - nums[i + 1]| for all 0 <= i < nums.length - 1.
#
# You are allowed to select any subarray of the given array and reverse it. You can perform this operation only once.
#
# Find maximum possible value of the final array.
#
# Example:
# Input: nums = [2,3,1,5,4]
# Output: 10
# Explanation: By reversing the subarray [3,1,5] the array becomes [2,5,1,3,4] whose value is 10.
#
# Constraints:
# 2 <= nums.length <= 3 * 104
# 	-105 <= nums[i] <= 105
# 	The answer is guaranteed to fit in a 32-bit integer.
#

class Solution(object):
    def maxValueAfterReverse(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        original_value = sum(abs(nums[i] - nums[i + 1]) for i in range(n - 1))
        
        max_increase = 0
        
        for i in range(1, n):
            a, b = nums[i - 1], nums[i]
            max_increase = max(max_increase, abs(nums[0] - b) - abs(a - b))
            max_increase = max(max_increase, abs(nums[-1] - a) - abs(a - b))
        
        min_a_plus_b = float('inf')
        max_a_plus_b = float('-inf')
        min_a_minus_b = float('inf')
        max_a_minus_b = float('-inf')
        
        for i in range(1, n):
            a, b = nums[i - 1], nums[i]
            min_a_plus_b = min(min_a_plus_b, a + b)
            max_a_plus_b = max(max_a_plus_b, a + b)
            min_a_minus_b = min(min_a_minus_b, a - b)
            max_a_minus_b = max(max_a_minus_b, a - b)
        
        max_increase = max(max_increase, (max_a_plus_b - min_a_plus_b) * 2)
        max_increase = max(max_increase, (max_a_minus_b - min_a_minus_b) * 2)
        
        return original_value + max_increase