# Source: https://leetcode.com/problems/find-common-elements-between-two-arrays/   |   Difficulty: Easy
#
# Problem Description:
# You are given two integer arrays nums1 and nums2 of sizes n and m, respectively. Calculate the following values:
#
#
# 	answer1 : the number of indices i such that nums1[i] exists in nums2.
# 	answer2 : the number of indices i such that nums2[i] exists in nums1.
#
#
# Return [answer1,answer2].
#
# Example:
# Input: nums1 = [2,3,2], nums2 = [1,2]
#
# Output: [2,1]
#
# Explanation:
#
# Constraints:
# n == nums1.length
# 	m == nums2.length
# 	1 <= n, m <= 100
# 	1 <= nums1[i], nums2[i] <= 100
#

class Solution(object):
    def findIntersectionValues(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        set1 = set(nums1)
        set2 = set(nums2)
        
        answer1 = sum(1 for num in nums1 if num in set2)
        answer2 = sum(1 for num in nums2 if num in set1)
        
        return [answer1, answer2]