# Source: https://leetcode.com/problems/find-the-difference-of-two-arrays/   |   Difficulty: Easy
#
# Problem Description:
# Given two 0-indexed integer arrays nums1 and nums2, return a list answer of size 2 where:
#
#
# 	answer[0] is a list of all distinct integers in nums1 which are not present in nums2.
# 	answer[1] is a list of all distinct integers in nums2 which are not present in nums1.
#
#
# Note that the integers in the lists may be returned in any order.
#
# Example:
# Input: nums1 = [1,2,3], nums2 = [2,4,6]
# Output: [[1,3],[4,6]]
# Explanation:
# For nums1, nums1[1] = 2 is present at index 0 of nums2, whereas nums1[0] = 1 and nums1[2] = 3 are not present in nums2. Therefore, answer[0] = [1,3].
# For nums2, nums2[0] = 2 is present at index 1 of nums1, whereas nums2[1] = 4 and nums2[2] = 6 are not present in nums1. Therefore, answer[1] = [4,6].
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 1000
# 	-1000 <= nums1[i], nums2[i] <= 1000
#

class Solution(object):
    def findDifference(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[List[int]]
        """
        set1 = set(nums1)
        set2 = set(nums2)
        
        diff1 = list(set1 - set2)
        diff2 = list(set2 - set1)
        
        return [diff1, diff2]