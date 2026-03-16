# Source: https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and an integer x. In one operation, you can either remove the leftmost or the rightmost element from the array nums and subtract its value from x. Note that this modifies the array for future operations.
#
# Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise, return -1.
#
# Example:
# Input: nums = [1,1,4,2,3], x = 5
# Output: 2
# Explanation: The optimal solution is to remove the last two elements to reduce x to zero.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 104
# 	1 <= x <= 109
#

class Solution(object):
    def minOperations(self, nums, x):
        """
        :type nums: List[int]
        :type x: int
        :rtype: int
        """
        total = sum(nums)
        target = total - x
        if target < 0:
            return -1
        if target == 0:
            return len(nums)
        
        left = 0
        current_sum = 0
        max_length = -1
        
        for right in range(len(nums)):
            current_sum += nums[right]
            
            while current_sum > target and left <= right:
                current_sum -= nums[left]
                left += 1
            
            if current_sum == target:
                max_length = max(max_length, right - left + 1)
        
        return len(nums) - max_length if max_length != -1 else -1