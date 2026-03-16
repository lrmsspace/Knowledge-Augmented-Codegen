# Source: https://leetcode.com/problems/advantage-shuffle/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integer arrays nums1 and nums2 both of the same length. The advantage of nums1 with respect to nums2 is the number of indices i for which nums1[i] > nums2[i].
#
# Return any permutation of nums1 that maximizes its advantage with respect to nums2.
#
# Example:
# Input: nums1 = [2,7,11,15], nums2 = [1,10,4,11]
# Output: [2,11,7,15]
#
# Constraints:
# 1 <= nums1.length <= 105
# 	nums2.length == nums1.length
# 	0 <= nums1[i], nums2[i] <= 109
#

class Solution(object):
    def advantageCount(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        sorted_nums1 = sorted(nums1)
        sorted_nums2 = sorted((num, i) for i, num in enumerate(nums2))
        
        result = [0] * len(nums1)
        left, right = 0, len(nums1) - 1
        
        for num in reversed(sorted_nums1):
            if num > sorted_nums2[right][0]:
                result[sorted_nums2[right][1]] = num
                right -= 1
            else:
                result[sorted_nums2[left][1]] = num
                left += 1
        
        return result