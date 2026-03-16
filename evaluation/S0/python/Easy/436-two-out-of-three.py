# Source: https://leetcode.com/problems/two-out-of-three/   |   Difficulty: Easy
#
# Problem Description:
# Given three integer arrays nums1, nums2, and nums3, return a distinct array containing all the values that are present in at least two out of the three arrays. You may return the values in any order.
#
# Example:
# Input: nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]
# Output: [3,2]
# Explanation: The values that are present in at least two arrays are:
# - 3, in all three arrays.
# - 2, in nums1 and nums2.
#
# Constraints:
# 1 <= nums1.length, nums2.length, nums3.length <= 100
# 	1 <= nums1[i], nums2[j], nums3[k] <= 100
#

class Solution(object):
    def twoOutOfThree(self, nums1, nums2, nums3):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type nums3: List[int]
        :rtype: List[int]
        """
        count = {}
        for num in set(nums1):
            count[num] = count.get(num, 0) + 1
        for num in set(nums2):
            count[num] = count.get(num, 0) + 1
        for num in set(nums3):
            count[num] = count.get(num, 0) + 1
        
        result = [num for num, cnt in count.items() if cnt >= 2]
        return result