# Source: https://leetcode.com/problems/number-of-arithmetic-triplets/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed, strictly increasing integer array nums and a positive integer diff. A triplet (i, j, k) is an arithmetic triplet if the following conditions are met:
#
#
# 	i < j < k,
# 	nums[j] - nums[i] == diff, and
# 	nums[k] - nums[j] == diff.
#
#
# Return the number of unique arithmetic triplets.
#
# Example:
# Input: nums = [0,1,4,6,7,10], diff = 3
# Output: 2
# Explanation:
# (1, 2, 4) is an arithmetic triplet because both 7 - 4 == 3 and 4 - 1 == 3.
# (2, 4, 5) is an arithmetic triplet because both 10 - 7 == 3 and 7 - 4 == 3.
#
# Constraints:
# 3 <= nums.length <= 200
# 	0 <= nums[i] <= 200
# 	1 <= diff <= 50
# 	nums is strictly increasing.
#

class Solution(object):
    def arithmeticTriplets(self, nums, diff):
        """
        :type nums: List[int]
        :type diff: int
        :rtype: int
        """
        num_set = set(nums)
        count = 0
        
        for num in nums:
            if (num + diff) in num_set and (num + 2 * diff) in num_set:
                count += 1
                
        return count