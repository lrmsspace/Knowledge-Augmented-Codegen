# Source: https://leetcode.com/problems/intersection-of-two-arrays/   |   Difficulty: Easy
#
# Problem Description:
# Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.
#
# Example:
# Input: nums1 = [1,2,2,1], nums2 = [2,2]
# Output: [2]
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 1000
# 	0 <= nums1[i], nums2[i] <= 1000
#

class Solution(object):
    def intersection(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        set1 = set(nums1)
        set2 = set(nums2)
        return list(set1 & set2)