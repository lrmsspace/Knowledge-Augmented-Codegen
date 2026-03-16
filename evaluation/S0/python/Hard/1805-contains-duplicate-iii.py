# Source: https://leetcode.com/problems/contains-duplicate-iii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and two integers indexDiff and valueDiff.
#
# Find a pair of indices (i, j) such that:
#
#
# 	i != j,
# 	abs(i - j) <= indexDiff.
# 	abs(nums[i] - nums[j]) <= valueDiff, and
#
#
# Return true if such pair exists or false otherwise.
#
# Example:
# Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
# Output: true
# Explanation: We can choose (i, j) = (0, 3).
# We satisfy the three conditions:
# i != j --> 0 != 3
# abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
# abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0
#
# Constraints:
# 2 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
# 	1 <= indexDiff <= nums.length
# 	0 <= valueDiff <= 109
#

class Solution(object):
    def containsNearbyAlmostDuplicate(self, nums, indexDiff, valueDiff):
        """
        :type nums: List[int]
        :type indexDiff: int
        :type valueDiff: int
        :rtype: bool
        """
        if indexDiff <= 0 or valueDiff < 0:
            return False
        
        bucket = {}
        bucket_size = valueDiff + 1
        
        for i, num in enumerate(nums):
            bucket_id = num // bucket_size
            
            if bucket_id in bucket:
                return True
            
            if (bucket_id - 1 in bucket and abs(num - bucket[bucket_id - 1]) <= valueDiff):
                return True
            
            if (bucket_id + 1 in bucket and abs(num - bucket[bucket_id + 1]) <= valueDiff):
                return True
            
            bucket[bucket_id] = num
            
            if i >= indexDiff:
                old_bucket_id = nums[i - indexDiff] // bucket_size
                del bucket[old_bucket_id]
        
        return False