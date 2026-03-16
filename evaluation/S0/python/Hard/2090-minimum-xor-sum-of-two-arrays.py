# Source: https://leetcode.com/problems/minimum-xor-sum-of-two-arrays/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integer arrays nums1 and nums2 of length n.
#
# The XOR sum of the two integer arrays is (nums1[0] XOR nums2[0]) + (nums1[1] XOR nums2[1]) + ... + (nums1[n - 1] XOR nums2[n - 1]) (0-indexed).
#
#
# 	For example, the XOR sum of [1,2,3] and [3,2,1] is equal to (1 XOR 3) + (2 XOR 2) + (3 XOR 1) = 2 + 0 + 2 = 4.
#
#
# Rearrange the elements of nums2 such that the resulting XOR sum is minimized.
#
# Return the XOR sum after the rearrangement.
#
# Example:
# Input: nums1 = [1,2], nums2 = [2,3]
# Output: 2
# Explanation: Rearrange nums2 so that it becomes [3,2].
# The XOR sum is (1 XOR 3) + (2 XOR 2) = 2 + 0 = 2.
#
# Constraints:
# n == nums1.length
# 	n == nums2.length
# 	1 <= n <= 14
# 	0 <= nums1[i], nums2[i] <= 107
#

class Solution(object):
    def minimumXORSum(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        from functools import lru_cache

        n = len(nums1)

        @lru_cache(None)
        def dp(mask, i):
            if i == n:
                return 0

            res = float('inf')
            for j in range(n):
                if mask & (1 << j) == 0:
                    res = min(res, (nums1[i] ^ nums2[j]) + dp(mask | (1 << j), i + 1))
            return res

        return dp(0, 0)