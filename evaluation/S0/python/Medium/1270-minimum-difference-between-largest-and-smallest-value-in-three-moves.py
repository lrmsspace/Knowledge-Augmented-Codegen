# Source: https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# In one move, you can choose one element of nums and change it to any value.
#
# Return the minimum difference between the largest and smallest value of nums after performing at most three moves.
#
# Example:
# Input: nums = [5,3,2,4]
# Output: 0
# Explanation: We can make at most 3 moves.
# In the first move, change 2 to 3. nums becomes [5,3,3,4].
# In the second move, change 4 to 3. nums becomes [5,3,3,3].
# In the third move, change 5 to 3. nums becomes [3,3,3,3].
# After performing 3 moves, the difference between the minimum and maximum is 3 - 3 = 0.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
#

class Solution(object):
    def minDifference(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n <= 4:
            return 0
        
        nums.sort()
        res = float('inf')
        
        for i in range(4):
            res = min(res, nums[n - 4 + i] - nums[i])
        
        return res