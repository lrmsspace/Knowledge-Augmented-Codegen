# Source: https://leetcode.com/problems/count-special-quadruplets/   |   Difficulty: Easy
#
# Problem Description:
# Given a 0-indexed integer array nums, return the number of distinct quadruplets (a, b, c, d) such that:
#
#
# 	nums[a] + nums[b] + nums[c] == nums[d], and
# 	a < b < c < d
#
# Example:
# Input: nums = [1,2,3,6]
# Output: 1
# Explanation: The only quadruplet that satisfies the requirement is (0, 1, 2, 3) because 1 + 2 + 3 == 6.
#
# Constraints:
# 4 <= nums.length <= 50
# 	1 <= nums[i] <= 100
#

class Solution(object):
    def countQuadruplets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        count = 0
        n = len(nums)
        
        for a in range(n):
            for b in range(a + 1, n):
                for c in range(b + 1, n):
                    for d in range(c + 1, n):
                        if nums[a] + nums[b] + nums[c] == nums[d]:
                            count += 1
        
        return count