# Source: https://leetcode.com/problems/minimum-absolute-sum-difference/   |   Difficulty: Medium
#
# Problem Description:
# You are given two positive integer arrays nums1 and nums2, both of length n.
#
# The absolute sum difference of arrays nums1 and nums2 is defined as the sum of |nums1[i] - nums2[i]| for each 0 <= i < n (0-indexed).
#
# You can replace at most one element of nums1 with any other element in nums1 to minimize the absolute sum difference.
#
# Return the minimum absolute sum difference after replacing at most one element in the array nums1. Since the answer may be large, return it modulo 109 + 7.
#
# |x| is defined as:
#
#
# 	x if x >= 0, or
# 	-x if x < 0.
#
# Example:
# Input: nums1 = [1,7,5], nums2 = [2,3,5]
# Output: 3
# Explanation: There are two possible optimal solutions:
# - Replace the second element with the first: [1,7,5] => [1,1,5], or
# - Replace the second element with the third: [1,7,5] => [1,5,5].
# Both will yield an absolute sum difference of |1-2| + (|1-3| or |5-3|) + |5-5| = 3.
#
# Constraints:
# n == nums1.length
# 	n == nums2.length
# 	1 <= n <= 105
# 	1 <= nums1[i], nums2[i] <= 105
#

class Solution(object):
    def minAbsoluteSumDiff(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums1)
        sorted_nums1 = sorted(nums1)
        
        total_diff = 0
        max_improvement = 0
        
        for i in range(n):
            diff = abs(nums1[i] - nums2[i])
            total_diff += diff
            
            # Binary search to find the closest value in sorted_nums1 to nums2[i]
            left, right = 0, n - 1
            while left < right:
                mid = (left + right) // 2
                if sorted_nums1[mid] < nums2[i]:
                    left = mid + 1
                else:
                    right = mid
            
            # Check the closest value found
            for j in [left, left - 1]:
                if 0 <= j < n:
                    new_diff = abs(sorted_nums1[j] - nums2[i])
                    improvement = diff - new_diff
                    max_improvement = max(max_improvement, improvement)
        
        return (total_diff - max_improvement) % MOD