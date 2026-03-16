# Source: https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/   |   Difficulty: Hard
#
# Problem Description:
# Given two sorted 0-indexed integer arrays nums1 and nums2 as well as an integer k, return the kth (1-based) smallest product of nums1[i] * nums2[j] where 0 <= i < nums1.length and 0 <= j < nums2.length.
#
# Example:
# Input: nums1 = [2,5], nums2 = [3,4], k = 2
# Output: 8
# Explanation: The 2 smallest products are:
# - nums1[0] * nums2[0] = 2 * 3 = 6
# - nums1[0] * nums2[1] = 2 * 4 = 8
# The 2nd smallest product is 8.
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 5 * 104
# 	-105 <= nums1[i], nums2[j] <= 105
# 	1 <= k <= nums1.length * nums2.length
# 	nums1 and nums2 are sorted.
#

class Solution(object):
    def kthSmallestProduct(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: int
        """
        def count_no_greater_than(x):
            count = 0
            for num in nums1:
                if num >= 0:
                    l, r = 0, len(nums2)
                    while l < r:
                        mid = (l + r) // 2
                        if num * nums2[mid] <= x:
                            l = mid + 1
                        else:
                            r = mid
                    count += l
                else:
                    l, r = 0, len(nums2)
                    while l < r:
                        mid = (l + r) // 2
                        if num * nums2[mid] <= x:
                            r = mid
                        else:
                            l = mid + 1
                    count += len(nums2) - l
            return count

        left, right = -10**10, 10**10
        while left < right:
            mid = (left + right) // 2
            if count_no_greater_than(mid) < k:
                left = mid + 1
            else:
                right = mid
        return left