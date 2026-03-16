# Source: https://leetcode.com/problems/sum-of-subarray-ranges/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums. The range of a subarray of nums is the difference between the largest and smallest element in the subarray.
#
# Return the sum of all subarray ranges of nums.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [1,2,3]
# Output: 4
# Explanation: The 6 subarrays of nums are the following:
# [1], range = largest - smallest = 1 - 1 = 0 
# [2], range = 2 - 2 = 0
# [3], range = 3 - 3 = 0
# [1,2], range = 2 - 1 = 1
# [2,3], range = 3 - 2 = 1
# [1,2,3], range = 3 - 1 = 2
# So the sum of all ranges is 0 + 0 + 0 + 1 + 1 + 2 = 4.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	-109 <= nums[i] <= 109
#
#
#  
# Follow-up: Could you find a solution with O(n) time complexity?
#

class Solution(object):
    def subArrayRanges(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        total_min = 0
        total_max = 0
        
        # Calculate contribution as minimum
        stack = []
        for i in range(n + 1):
            while stack and (i == n or nums[stack[-1]] > nums[i]):
                j = stack.pop()
                k = stack[-1] if stack else -1
                total_min += nums[j] * (i - j) * (j - k)
            stack.append(i)
        
        # Calculate contribution as maximum
        stack = []
        for i in range(n + 1):
            while stack and (i == n or nums[stack[-1]] < nums[i]):
                j = stack.pop()
                k = stack[-1] if stack else -1
                total_max += nums[j] * (i - j) * (j - k)
            stack.append(i)
        
        return total_max - total_min