# Source: https://leetcode.com/problems/find-the-score-of-all-prefixes-of-an-array/   |   Difficulty: Medium
#
# Problem Description:
# We define the conversion array conver of an array arr as follows:
#
#
# 	conver[i] = arr[i] + max(arr[0..i]) where max(arr[0..i]) is the maximum value of arr[j] over 0 <= j <= i.
#
#
# We also define the score of an array arr as the sum of the values of the conversion array of arr.
#
# Given a 0-indexed integer array nums of length n, return an array ans of length n where ans[i] is the score of the prefix nums[0..i].
#
# Example:
# Input: nums = [2,3,7,5,10]
# Output: [4,10,24,36,56]
# Explanation: 
# For the prefix [2], the conversion array is [4] hence the score is 4
# For the prefix [2, 3], the conversion array is [4, 6] hence the score is 10
# For the prefix [2, 3, 7], the conversion array is [4, 6, 14] hence the score is 24
# For the prefix [2, 3, 7, 5], the conversion array is [4, 6, 14, 12] hence the score is 36
# For the prefix [2, 3, 7, 5, 10], the conversion array is [4, 6, 14, 12, 20] hence the score is 56
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def findPrefixScore(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        n = len(nums)
        res = [0] * n
        max_so_far = 0
        current_sum = 0
        
        for i in range(n):
            max_so_far = max(max_so_far, nums[i])
            converted_value = nums[i] + max_so_far
            current_sum += converted_value
            res[i] = current_sum
            
        return res