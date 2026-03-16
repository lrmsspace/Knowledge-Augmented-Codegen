# Source: https://leetcode.com/problems/minimum-division-operations-to-make-array-non-decreasing/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# Any positive divisor of a natural number x that is strictly less than x is called a proper divisor of x. For example, 2 is a proper divisor of 4, while 6 is not a proper divisor of 6.
#
# You are allowed to perform an operation any number of times on nums, where in each operation you select any one element from nums and divide it by its greatest proper divisor.
#
# Return the minimum number of operations required to make the array non-decreasing.
#
# If it is not possible to make the array non-decreasing using any number of operations, return -1.
#
# Example:
# Input: nums = [25,7]
#
# Output: 1
#
# Explanation:
#
# Using a single operation, 25 gets divided by 5 and nums becomes [5, 7].
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 106
#

class Solution(object):
    def minOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        operations = 0
        
        for i in range(n - 2, -1, -1):
            if nums[i] > nums[i + 1]:
                if nums[i + 1] == 1:
                    return -1
                
                count = 0
                while nums[i] > nums[i + 1]:
                    nums[i] //= self.greatest_proper_divisor(nums[i])
                    count += 1
                
                operations += count
        
        return operations