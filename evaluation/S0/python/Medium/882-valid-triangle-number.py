# Source: https://leetcode.com/problems/valid-triangle-number/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, return the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.
#
# Example:
# Input: nums = [2,2,3,4]
# Output: 3
# Explanation: Valid combinations are: 
# 2,3,4 (using the first 2)
# 2,3,4 (using the second 2)
# 2,2,3
#
# Constraints:
# 1 <= nums.length <= 1000
# 	0 <= nums[i] <= 1000
#

class Solution(object):
    def triangleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        count = 0
        n = len(nums)
        
        for i in range(n - 2):
            k = i + 2
            for j in range(i + 1, n - 1):
                while k < n and nums[i] + nums[j] > nums[k]:
                    k += 1
                count += k - j - 1
                
        return count