# Source: https://leetcode.com/problems/4sum-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given four integer arrays nums1, nums2, nums3, and nums4 all of length n, return the number of tuples (i, j, k, l) such that:
#
#
# 	0 <= i, j, k, l < n
# 	nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
#
# Example:
# Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
# Output: 2
# Explanation:
# The two tuples are:
# 1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
# 2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0
#
# Constraints:
# n == nums1.length
# 	n == nums2.length
# 	n == nums3.length
# 	n == nums4.length
# 	1 <= n <= 200
# 	-228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 228
#

class Solution(object):
    def fourSumCount(self, nums1, nums2, nums3, nums4):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type nums3: List[int]
        :type nums4: List[int]
        :rtype: int
        """
        from collections import defaultdict

        count_map = defaultdict(int)

        # Calculate all possible sums of pairs from nums1 and nums2
        for a in nums1:
            for b in nums2:
                count_map[a + b] += 1

        result = 0

        # For each possible sum of pairs from nums3 and nums4,
        # check if the negated sum exists in count_map
        for c in nums3:
            for d in nums4:
                target = -(c + d)
                if target in count_map:
                    result += count_map[target]

        return result