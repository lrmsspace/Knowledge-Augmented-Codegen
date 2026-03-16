# Source: https://leetcode.com/problems/minimum-index-of-a-valid-split/   |   Difficulty: Medium
#
# Problem Description:
# An element x of an integer array arr of length m is dominant if more than half the elements of arr have a value of x.
#
# You are given a 0-indexed integer array nums of length n with one dominant element.
#
# You can split nums at an index i into two arrays nums[0, ..., i] and nums[i + 1, ..., n - 1], but the split is only valid if:
#
#
# 	0 <= i < n - 1
# 	nums[0, ..., i], and nums[i + 1, ..., n - 1] have the same dominant element.
#
#
# Here, nums[i, ..., j] denotes the subarray of nums starting at index i and ending at index j, both ends being inclusive. Particularly, if j < i then nums[i, ..., j] denotes an empty subarray.
#
# Return the minimum index of a valid split. If no valid split exists, return -1.
#
# Example:
# Input: nums = [1,2,2,2]
# Output: 2
# Explanation: We can split the array at index 2 to obtain arrays [1,2,2] and [2]. 
# In array [1,2,2], element 2 is dominant since it occurs twice in the array and 2 * 2 > 3. 
# In array [2], element 2 is dominant since it occurs once in the array and 1 * 2 > 1.
# Both [1,2,2] and [2] have the same dominant element as nums, so this is a valid split. 
# It can be shown that index 2 is the minimum index of a valid split.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	nums has exactly one dominant element.
#

class Solution(object):
    def minimumIndex(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import defaultdict

        n = len(nums)
        count = defaultdict(int)
        dominant = None
        dominant_count = 0

        # Find the dominant element and its count
        for num in nums:
            count[num] += 1
            if count[num] > dominant_count:
                dominant_count = count[num]
                dominant = num

        left_count = 0
        for i in range(n - 1):
            if nums[i] == dominant:
                left_count += 1
            left_size = i + 1
            right_size = n - left_size
            right_count = dominant_count - left_count

            if left_count * 2 > left_size and right_count * 2 > right_size:
                return i

        return -1