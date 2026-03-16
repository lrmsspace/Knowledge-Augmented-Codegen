# Source: https://leetcode.com/problems/delete-and-earn/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums. You want to maximize the number of points you get by performing the following operation any number of times:
#
#
# 	Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
#
#
# Return the maximum number of points you can earn by applying the above operation some number of times.
#
# Example:
# Input: nums = [3,4,2]
# Output: 6
# Explanation: You can perform the following operations:
# - Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
# - Delete 2 to earn 2 points. nums = [].
# You earn a total of 6 points.
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	1 <= nums[i] <= 104
#

class Solution(object):
    def deleteAndEarn(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums:
            return 0
        
        max_num = max(nums)
        points = [0] * (max_num + 1)
        
        for num in nums:
            points[num] += num
        
        take, skip = 0, 0
        
        for point in points:
            take_i = skip + point
            skip_i = max(take, skip)
            
            take, skip = take_i, skip_i
        
        return max(take, skip)