# Source: https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/   |   Difficulty: Easy
#
# Problem Description:
# Given an array nums, you can perform the following operation any number of times:
#
#
# 	Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
# 	Replace the pair with their sum.
#
#
# Return the minimum number of operations needed to make the array non-decreasing.
#
# An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).
#
# Example:
# Input: nums = [5,2,3,1]
#
# Output: 2
#
# Explanation:
#
#
# 	The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
# 	The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
#
#
# The array nums became non-decreasing in two operations.
#
# Constraints:
# 1 <= nums.length <= 50
# 	-1000 <= nums[i] <= 1000
#

class Solution(object):
    def minimumPairRemoval(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        count = 0
        
        while not self.is_non_decreasing(nums):
            min_sum = float('inf')
            min_index = -1
            
            for i in range(n - 1):
                pair_sum = nums[i] + nums[i + 1]
                if pair_sum < min_sum:
                    min_sum = pair_sum
                    min_index = i
            
            # Replace the adjacent pair with their sum
            nums[min_index] = min_sum
            del nums[min_index + 1]
            n -= 1
            count += 1
        
        return count