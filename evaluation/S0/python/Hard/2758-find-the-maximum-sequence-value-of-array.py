# Source: https://leetcode.com/problems/find-the-maximum-sequence-value-of-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and a positive integer k.
#
# The value of a sequence seq of size 2 * x is defined as:
#
#
# 	(seq[0] OR seq[1] OR ... OR seq[x - 1]) XOR (seq[x] OR seq[x + 1] OR ... OR seq[2 * x - 1]).
#
#
# Return the maximum value of any subsequence of nums having size 2 * k.
#
# Example:
# Input: nums = [2,6,7], k = 1
#
# Output: 5
#
# Explanation:
#
# The subsequence [2, 7] has the maximum value of 2 XOR 7 = 5.
#
# Constraints:
# 2 <= nums.length <= 400
# 	1 <= nums[i] < 27
# 	1 <= k <= nums.length / 2
#

class Solution(object):
    def maxValue(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        from functools import lru_cache

        @lru_cache(None)
        def dp(i, k):
            if k == 0:
                return 0
            if i >= n:
                return float('-inf')

            or1 = 0
            max_val = float('-inf')
            for j in range(i, n):
                or1 |= nums[j]
                or2 = 0
                for l in range(j + 1, n):
                    or2 |= nums[l]
                    val = or1 ^ or2
                    val += dp(l + 1, k - 1)
                    max_val = max(max_val, val)
            return max_val

        return dp(0, k)