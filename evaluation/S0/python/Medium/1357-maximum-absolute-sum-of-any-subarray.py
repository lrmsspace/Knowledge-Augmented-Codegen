# Source: https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).
#
# Return the maximum absolute sum of any (possibly empty) subarray of nums.
#
# Note that abs(x) is defined as follows:
#
#
# 	If x is a negative integer, then abs(x) = -x.
# 	If x is a non-negative integer, then abs(x) = x.
#
# Example:
# Input: nums = [1,-3,2,3,-4]
# Output: 5
# Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-104 <= nums[i] <= 104
#

class Solution(object):
    def maxAbsoluteSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_sum = 0
        min_sum = 0
        current_max = 0
        current_min = 0
        
        for num in nums:
            current_max += num
            current_min += num
            
            if current_max < 0:
                current_max = 0
            if current_min > 0:
                current_min = 0
            
            max_sum = max(max_sum, current_max)
            min_sum = min(min_sum, current_min)
        
        return max(max_sum, abs(min_sum))