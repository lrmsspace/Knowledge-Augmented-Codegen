# Source: https://leetcode.com/problems/minimum-common-value/   |   Difficulty: Easy
#
# Problem Description:
# Given two integer arrays nums1 and nums2, sorted in non-decreasing order, return the minimum integer common to both arrays. If there is no common integer amongst nums1 and nums2, return -1.
#
# Note that an integer is said to be common to nums1 and nums2 if both arrays have at least one occurrence of that integer.
#
# Example:
# Input: nums1 = [1,2,3], nums2 = [2,4]
# Output: 2
# Explanation: The smallest element common to both arrays is 2, so we return 2.
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 105
# 	1 <= nums1[i], nums2[j] <= 109
# 	Both nums1 and nums2 are sorted in non-decreasing order.
#

class Solution(object):
    def getCommon(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        i, j = 0, 0
        while i < len(nums1) and j < len(nums2):
            if nums1[i] == nums2[j]:
                return nums1[i]
            elif nums1[i] < nums2[j]:
                i += 1
            else:
                j += 1
        return -1