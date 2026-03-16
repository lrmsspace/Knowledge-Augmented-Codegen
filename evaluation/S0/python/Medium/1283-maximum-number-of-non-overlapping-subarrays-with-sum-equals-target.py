# Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/   |   Difficulty: Medium
#
# Problem Description:
# Given an array nums and an integer target, return the maximum number of non-empty non-overlapping subarrays such that the sum of values in each subarray is equal to target.
#
# Example:
# Input: nums = [1,1,1,1,1], target = 2
# Output: 2
# Explanation: There are 2 non-overlapping subarrays [1,1,1,1,1] with sum equals to target(2).
#
# Constraints:
# 1 <= nums.length <= 105
# 	-104 <= nums[i] <= 104
# 	0 <= target <= 106
#

class Solution(object):
    def maxNonOverlapping(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        count = 0
        current_sum = 0
        seen_sums = set([0])
        
        for num in nums:
            current_sum += num
            
            if (current_sum - target) in seen_sums:
                count += 1
                current_sum = 0
                seen_sums = set([0])
            else:
                seen_sums.add(current_sum)
        
        return count