# Source: https://leetcode.com/problems/intersection-of-two-arrays-ii/   |   Difficulty: Easy
#
# Problem Description:
# Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must appear as many times as it shows in both arrays and you may return the result in any order.
#
# Example:
# Input: nums1 = [1,2,2,1], nums2 = [2,2]
# Output: [2,2]
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 1000
# 	0 <= nums1[i], nums2[i] <= 1000
#
#
#  
# Follow up:
#
#
# 	What if the given array is already sorted? How would you optimize your algorithm?
# 	What if nums1's size is small compared to nums2's size? Which algorithm is better?
# 	What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
#

class Solution(object):
    def intersect(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        from collections import Counter
        counts = Counter(nums1)
        intersection = []
        
        for num in nums2:
            if counts[num] > 0:
                intersection.append(num)
                counts[num] -= 1
                
        return intersection