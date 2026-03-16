# Source: https://leetcode.com/problems/median-of-two-sorted-arrays/   |   Difficulty: Hard
#
# Problem Description:
# Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
#
# The overall run time complexity should be O(log (m+n)).
#
# Example:
# Input: nums1 = [1,3], nums2 = [2]
# Output: 2.00000
# Explanation: merged array = [1,2,3] and median is 2.
#
# Constraints:
# nums1.length == m
# 	nums2.length == n
# 	0 <= m <= 1000
# 	0 <= n <= 1000
# 	1 <= m + n <= 2000
# 	-106 <= nums1[i], nums2[i] <= 106
#

class Solution(object):
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        merged = sorted(nums1 + nums2)
        length = len(merged)
        
        if length % 2 == 1:
            return float(merged[length // 2])
        else:
            mid1 = merged[length // 2 - 1]
            mid2 = merged[length // 2]
            return (mid1 + mid2) / 2.0