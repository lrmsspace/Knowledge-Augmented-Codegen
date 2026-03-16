# Source: https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/   |   Difficulty: Medium
#
# Problem Description:
# A swap is defined as taking two distinct positions in an array and swapping the values in them.
#
# A circular array is defined as an array where we consider the first element and the last element to be adjacent.
#
# Given a binary circular array nums, return the minimum number of swaps required to group all 1's present in the array together at any location.
#
# Example:
# Input: nums = [0,1,0,1,1,0,0]
# Output: 1
# Explanation: Here are a few of the ways to group all the 1's together:
# [0,0,1,1,1,0,0] using 1 swap.
# [0,1,1,1,0,0,0] using 1 swap.
# [1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
# There is no way to group all 1's together with 0 swaps.
# Thus, the minimum number of swaps required is 1.
#
# Constraints:
# 1 <= nums.length <= 105
# 	nums[i] is either 0 or 1.
#

class Solution(object):
    def minSwaps(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        total_ones = sum(nums)
        n = len(nums)
        
        if total_ones == 0 or total_ones == n:
            return 0
        
        # Create a circular array by extending the original array
        extended_nums = nums + nums
        
        # Initialize the number of ones in the first window
        current_ones = sum(extended_nums[:total_ones])
        max_ones_in_window = current_ones
        
        # Slide the window over the extended array
        for i in range(1, n):
            current_ones += extended_nums[i + total_ones - 1] - extended_nums[i - 1]
            max_ones_in_window = max(max_ones_in_window, current_ones)
        
        # Minimum swaps needed is the number of zeros in the best window
        return total_ones - max_ones_in_window