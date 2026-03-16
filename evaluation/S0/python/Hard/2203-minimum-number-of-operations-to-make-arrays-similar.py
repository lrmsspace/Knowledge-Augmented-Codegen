# Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-arrays-similar/   |   Difficulty: Hard
#
# Problem Description:
# You are given two positive integer arrays nums and target, of the same length.
#
# In one operation, you can choose any two distinct indices i and j where 0 <= i, j < nums.length and:
#
#
# 	set nums[i] = nums[i] + 2 and
# 	set nums[j] = nums[j] - 2.
#
#
# Two arrays are considered to be similar if the frequency of each element is the same.
#
# Return the minimum number of operations required to make nums similar to target. The test cases are generated such that nums can always be similar to target.
#
# Example:
# Input: nums = [8,12,6], target = [2,14,10]
# Output: 2
# Explanation: It is possible to make nums similar to target in two operations:
# - Choose i = 0 and j = 2, nums = [10,12,4].
# - Choose i = 1 and j = 2, nums = [10,14,2].
# It can be shown that 2 is the minimum number of operations needed.
#
# Constraints:
# n == nums.length == target.length
# 	1 <= n <= 105
# 	1 <= nums[i], target[i] <= 106
# 	It is possible to make nums similar to target.
#

class Solution(object):
    def makeSimilar(self, nums, target):
        """
        :type nums: List[int]
        :type target: List[int]
        :rtype: int
        """
        even_nums = sorted([x for x in nums if x % 2 == 0])
        odd_nums = sorted([x for x in nums if x % 2 == 1])
        even_target = sorted([x for x in target if x % 2 == 0])
        odd_target = sorted([x for x in target if x % 2 == 1])
        
        operations = 0
        
        for n, t in zip(even_nums, even_target):
            if n < t:
                operations += (t - n) // 2
        
        for n, t in zip(odd_nums, odd_target):
            if n < t:
                operations += (t - n) // 2
        
        return operations