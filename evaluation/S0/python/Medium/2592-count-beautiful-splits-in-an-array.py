# Source: https://leetcode.com/problems/count-beautiful-splits-in-an-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums.
#
# A split of an array nums is beautiful if:
#
#
# 	The array nums is split into three subarrays: nums1, nums2, and nums3, such that nums can be formed by concatenating nums1, nums2, and nums3 in that order.
# 	The subarray nums1 is a prefix of nums2 OR nums2 is a prefix of nums3.
#
#
# Return the number of ways you can make this split.
#
# Example:
# Input: nums = [1,1,2,1]
#
# Output: 2
#
# Explanation:
#
# The beautiful splits are:
#
#
# 	A split with nums1 = [1], nums2 = [1,2], nums3 = [1].
# 	A split with nums1 = [1], nums2 = [1], nums3 = [2,1].
#
# Constraints:
# 1 <= nums.length <= 5000
# 	0 <= nums[i] <= 50
#

class Solution(object):
    def beautifulSplits(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        prefix_count = [0] * n
        suffix_count = [0] * n
        
        freq = {}
        unique_count = 0
        
        # Count unique elements in prefix
        for i in range(n):
            if nums[i] not in freq:
                freq[nums[i]] = 0
                unique_count += 1
            freq[nums[i]] += 1
            prefix_count[i] = unique_count
        
        freq.clear()
        unique_count = 0
        
        # Count unique elements in suffix
        for i in range(n-1, -1, -1):
            if nums[i] not in freq:
                freq[nums[i]] = 0
                unique_count += 1
            freq[nums[i]] += 1
            suffix_count[i] = unique_count
        
        beautiful_splits = 0
        
        # Count beautiful splits
        for i in range(n-1):
            if prefix_count[i] == suffix_count[i+1]:
                beautiful_splits += 1
        
        return beautiful_splits