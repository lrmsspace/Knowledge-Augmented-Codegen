# Source: https://leetcode.com/problems/destroy-sequential-targets/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array nums consisting of positive integers, representing targets on a number line. You are also given an integer space.
#
# You have a machine which can destroy targets. Seeding the machine with some nums[i] allows it to destroy all targets with values that can be represented as nums[i] + c * space, where c is any non-negative integer. You want to destroy the maximum number of targets in nums.
#
# Return the minimum value of nums[i] you can seed the machine with to destroy the maximum number of targets.
#
# Example:
# Input: nums = [3,7,8,1,1,5], space = 2
# Output: 1
# Explanation: If we seed the machine with nums[3], then we destroy all targets equal to 1,3,5,7,9,... 
# In this case, we would destroy 5 total targets (all except for nums[2]). 
# It is impossible to destroy more than 5 targets, so we return nums[3].
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	1 <= space <= 109
#

class Solution(object):
    def destroyTargets(self, nums, space):
        """
        :type nums: List[int]
        :type space: int
        :rtype: int
        """
        mod_count = {}
        for num in nums:
            mod = num % space
            if mod not in mod_count:
                mod_count[mod] = []
            mod_count[mod].append(num)
        
        max_count = 0
        result = float('inf')
        
        for mod, numbers in mod_count.items():
            count = len(numbers)
            if count > max_count:
                max_count = count
                result = min(numbers)
            elif count == max_count:
                result = min(result, min(numbers))
        
        return result