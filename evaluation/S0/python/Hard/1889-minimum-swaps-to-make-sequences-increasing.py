# Source: https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integer arrays of the same length nums1 and nums2. In one operation, you are allowed to swap nums1[i] with nums2[i].
#
#
# 	For example, if nums1 = [1,2,3,8], and nums2 = [5,6,7,4], you can swap the element at i = 3 to obtain nums1 = [1,2,3,4] and nums2 = [5,6,7,8].
#
#
# Return the minimum number of needed operations to make nums1 and nums2 strictly increasing. The test cases are generated so that the given input always makes it possible.
#
# An array arr is strictly increasing if and only if arr[0] < arr[1] < arr[2] < ... < arr[arr.length - 1].
#
# Example:
# Input: nums1 = [1,3,5,4], nums2 = [1,2,3,7]
# Output: 1
# Explanation: 
# Swap nums1[3] and nums2[3]. Then the sequences are:
# nums1 = [1, 3, 5, 7] and nums2 = [1, 2, 3, 4]
# which are both strictly increasing.
#
# Constraints:
# 2 <= nums1.length <= 105
# 	nums2.length == nums1.length
# 	0 <= nums1[i], nums2[i] <= 2 * 105
#

class Solution(object):
    def minSwap(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        n = len(nums1)
        keep = [float('inf')] * n
        swap = [float('inf')] * n
        
        keep[0] = 0
        swap[0] = 1
        
        for i in range(1, n):
            if nums1[i] > nums1[i-1] and nums2[i] > nums2[i-1]:
                keep[i] = keep[i-1]
                swap[i] = swap[i-1] + 1
            
            if nums1[i] > nums2[i-1] and nums2[i] > nums1[i-1]:
                keep[i] = min(keep[i], swap[i-1])
                swap[i] = min(swap[i], keep[i-1] + 1)
        
        return min(keep[-1], swap[-1])