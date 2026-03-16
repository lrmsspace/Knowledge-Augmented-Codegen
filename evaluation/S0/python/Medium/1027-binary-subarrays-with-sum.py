# Source: https://leetcode.com/problems/binary-subarrays-with-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.
#
# A subarray is a contiguous part of the array.
#
# Example:
# Input: nums = [1,0,1,0,1], goal = 2
# Output: 4
# Explanation: The 4 subarrays are bolded and underlined below:
# [1,0,1,0,1]
# [1,0,1,0,1]
# [1,0,1,0,1]
# [1,0,1,0,1]
#
# Constraints:
# 1 <= nums.length <= 3 * 104
# 	nums[i] is either 0 or 1.
# 	0 <= goal <= nums.length
#

class Solution(object):
    def numSubarraysWithSum(self, nums, goal):
        """
        :type nums: List[int]
        :type goal: int
        :rtype: int
        """
        count = {0: 1}
        current_sum = 0
        result = 0
        
        for num in nums:
            current_sum += num
            if current_sum - goal in count:
                result += count[current_sum - goal]
            count[current_sum] = count.get(current_sum, 0) + 1
        
        return result