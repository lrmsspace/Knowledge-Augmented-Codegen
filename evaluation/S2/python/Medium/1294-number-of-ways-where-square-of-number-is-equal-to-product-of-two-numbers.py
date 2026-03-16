# Source: https://leetcode.com/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/   |   Difficulty: Medium
#
# Problem Description:
# Given two arrays of integers nums1 and nums2, return the number of triplets formed (type 1 and type 2) under the following rules:
#
#
# 	Type 1: Triplet (i, j, k) if nums1[i]2 == nums2[j] * nums2[k] where 0 <= i < nums1.length and 0 <= j < k < nums2.length.
# 	Type 2: Triplet (i, j, k) if nums2[i]2 == nums1[j] * nums1[k] where 0 <= i < nums2.length and 0 <= j < k < nums1.length.
#
# Example:
# Input: nums1 = [7,4], nums2 = [5,2,8,9]
# Output: 1
# Explanation: Type 1: (1, 1, 2), nums1[1]2 = nums2[1] * nums2[2]. (42 = 2 * 8).
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 1000
# 	1 <= nums1[i], nums2[i] <= 105
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numTriplets(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        from collections import Counter

        count1 = Counter(nums1)
        count2 = Counter(nums2)

        triplet_count = 0

        # Count type 1 triplets
        for num in count1:
            square = num * num
            for j in range(len(nums2)):
                for k in range(j + 1, len(nums2)):
                    if nums2[j] * nums2[k] == square:
                        triplet_count += count1[num]

        # Count type 2 triplets
        for num in count2:
            square = num * num
            for j in range(len(nums1)):
                for k in range(j + 1, len(nums1)):
                    if nums1[j] * nums1[k] == square:
                        triplet_count += count2[num]

        return triplet_count