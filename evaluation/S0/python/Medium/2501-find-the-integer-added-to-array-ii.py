# Source: https://leetcode.com/problems/find-the-integer-added-to-array-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integer arrays nums1 and nums2.
#
# From nums1 two elements have been removed, and all other elements have been increased (or decreased in the case of negative) by an integer, represented by the variable x.
#
# As a result, nums1 becomes equal to nums2. Two arrays are considered equal when they contain the same integers with the same frequencies.
#
# Return the minimum possible integer x that achieves this equivalence.
#
# Example:
# Input: nums1 = [4,20,16,12,8], nums2 = [14,18,10]
#
# Output: -2
#
# Explanation:
#
# After removing elements at indices [0,4] and adding -2, nums1 becomes [18,14,10].
#
# Constraints:
# 3 <= nums1.length <= 200
# 	nums2.length == nums1.length - 2
# 	0 <= nums1[i], nums2[i] <= 1000
# 	The test cases are generated in a way that there is an integer x such that nums1 can become equal to nums2 by removing two elements and adding x to each element of nums1.
#

class Solution(object):
    def minimumAddedInteger(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        nums1.sort()
        nums2.sort()
        n = len(nums1)
        m = len(nums2)
        res = float('inf')

        for i in range(n):
            for j in range(i + 1, n):
                x = nums2[0] - nums1[i]
                k = 0
                l = 0

                while k < n and l < m:
                    if k == i or k == j:
                        k += 1
                        continue

                    if nums1[k] + x == nums2[l]:
                        k += 1
                        l += 1
                    else:
                        break

                if l == m:
                    res = min(res, x)

        return res