# Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array nums consisiting of positive integers. You can do the following operation on the array any number of times:
#
#
# 	Select an index i such that 0 <= i < n - 1 and replace either of nums[i] or nums[i+1] with their gcd value.
#
#
# Return the minimum number of operations to make all elements of nums equal to 1. If it is impossible, return -1.
#
# The gcd of two integers is the greatest common divisor of the two integers.
#
# Example:
# Input: nums = [2,6,3,4]
# Output: 4
# Explanation: We can do the following operations:
# - Choose index i = 2 and replace nums[2] with gcd(3,4) = 1. Now we have nums = [2,6,1,4].
# - Choose index i = 1 and replace nums[1] with gcd(6,1) = 1. Now we have nums = [2,1,1,4].
# - Choose index i = 0 and replace nums[0] with gcd(2,1) = 1. Now we have nums = [1,1,1,4].
# - Choose index i = 2 and replace nums[3] with gcd(1,4) = 1. Now we have nums = [1,1,1,1].
#
# Constraints:
# 2 <= nums.length <= 50
# 	1 <= nums[i] <= 106
#

class Solution(object):
    def minOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        count_ones = nums.count(1)
        
        if count_ones > 0:
            return n - count_ones
        
        min_gcd_length = float('inf')
        
        for i in range(n):
            current_gcd = nums[i]
            for j in range(i + 1, n):
                current_gcd = self.gcd(current_gcd, nums[j])
                if current_gcd == 1:
                    min_gcd_length = min(min_gcd_length, j - i)
                    break
        
        if min_gcd_length == float('inf'):
            return -1
        
        return min_gcd_length + n - 1