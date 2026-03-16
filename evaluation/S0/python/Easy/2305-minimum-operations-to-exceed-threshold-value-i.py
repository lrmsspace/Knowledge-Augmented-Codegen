# Source: https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed integer array nums, and an integer k.
#
# In one operation, you can remove one occurrence of the smallest element of nums.
#
# Return the minimum number of operations needed so that all elements of the array are greater than or equal to k.
#
# Example:
# Input: nums = [2,11,10,1,3], k = 10
# Output: 3
# Explanation: After one operation, nums becomes equal to [2, 11, 10, 3].
# After two operations, nums becomes equal to [11, 10, 3].
# After three operations, nums becomes equal to [11, 10].
# At this stage, all the elements of nums are greater than or equal to 10 so we can stop.
# It can be shown that 3 is the minimum number of operations needed so that all elements of the array are greater than or equal to 10.
#
# Constraints:
# 1 <= nums.length <= 50
# 	1 <= nums[i] <= 109
# 	1 <= k <= 109
# 	The input is generated such that there is at least one index i such that nums[i] >= k.
#

class Solution(object):
    def minOperations(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        nums.sort()
        operations = 0
        for num in nums:
            if num < k:
                operations += 1
            else:
                break
        return operations