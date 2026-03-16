# Source: https://leetcode.com/problems/form-smallest-number-from-two-digit-arrays/   |   Difficulty: Easy
#
# Problem Description:
# Given two arrays of unique digits nums1 and nums2, return the smallest number that contains at least one digit from each array.
#
# Example:
# Input: nums1 = [4,1,3], nums2 = [5,7]
# Output: 15
# Explanation: The number 15 contains the digit 1 from nums1 and the digit 5 from nums2. It can be proven that 15 is the smallest number we can have.
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 9
# 	1 <= nums1[i], nums2[i] <= 9
# 	All digits in each array are unique.
#

class Solution(object):
    def minNumber(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        set1 = set(nums1)
        set2 = set(nums2)
        
        common_digits = set1.intersection(set2)
        if common_digits:
            return min(common_digits)
        
        min_num1 = min(nums1)
        min_num2 = min(nums2)
        
        if min_num1 < min_num2:
            return int(str(min_num1) + str(min_num2))
        else:
            return int(str(min_num2) + str(min_num1))