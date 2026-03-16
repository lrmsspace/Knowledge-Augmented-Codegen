# Source: https://leetcode.com/problems/maximize-score-after-n-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.
#
# In the ith operation (1-indexed), you will:
#
#
# 	Choose two elements, x and y.
# 	Receive a score of i * gcd(x, y).
# 	Remove x and y from nums.
#
#
# Return the maximum score you can receive after performing n operations.
#
# The function gcd(x, y) is the greatest common divisor of x and y.
#
# Example:
# Input: nums = [1,2]
# Output: 1
# Explanation: The optimal choice of operations is:
# (1 * gcd(1, 2)) = 1
#
# Constraints:
# 1 <= n <= 7
# 	nums.length == 2 * n
# 	1 <= nums[i] <= 106
#

class Solution(object):
    def maxScore(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from math import gcd
        from functools import lru_cache

        n = len(nums) // 2
        full_mask = (1 << (2 * n)) - 1

        @lru_cache(None)
        def dp(mask):
            if mask == full_mask:
                return 0

            operation = bin(mask).count('1') // 2 + 1
            max_score = 0

            for i in range(2 * n):
                if mask & (1 << i):
                    continue
                for j in range(i + 1, 2 * n):
                    if mask & (1 << j):
                        continue
                    new_mask = mask | (1 << i) | (1 << j)
                    score = operation * gcd(nums[i], nums[j]) + dp(new_mask)
                    max_score = max(max_score, score)

            return max_score

        return dp(0)