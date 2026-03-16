# Source: https://leetcode.com/problems/minimum-elements-to-add-to-form-a-given-sum/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and two integers limit and goal. The array nums has an interesting property that abs(nums[i]) <= limit.
#
# Return the minimum number of elements you need to add to make the sum of the array equal to goal. The array must maintain its property that abs(nums[i]) <= limit.
#
# Note that abs(x) equals x if x >= 0, and -x otherwise.
#
# Example:
# Input: nums = [1,-1,1], limit = 3, goal = -4
# Output: 2
# Explanation: You can add -2 and -3, then the sum of the array will be 1 - 1 + 1 - 2 - 3 = -4.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= limit <= 106
# 	-limit <= nums[i] <= limit
# 	-109 <= goal <= 109
#

class Solution(object):
    def minElements(self, nums, limit, goal):
        """
        :type nums: List[int]
        :type limit: int
        :type goal: int
        :rtype: int
        """
        current_sum = sum(nums)
        diff = abs(goal - current_sum)
        
        if diff == 0:
            return 0
        
        # Calculate the minimum number of elements needed
        num_elements = diff // limit
        if diff % limit != 0:
            num_elements += 1
            
        return num_elements