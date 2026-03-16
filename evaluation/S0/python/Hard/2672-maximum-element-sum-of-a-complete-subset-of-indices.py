# Source: https://leetcode.com/problems/maximum-element-sum-of-a-complete-subset-of-indices/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 1-indexed array nums. Your task is to select a complete subset from nums where every pair of selected indices multiplied is a perfect square,. i. e. if you select ai and aj, i * j must be a perfect square.
#
# Return the sum of the complete subset with the maximum sum.
#
# Example:
# Input: nums = [8,7,3,5,7,2,4,9]
#
# Output: 16
#
# Explanation:
#
# We select elements at indices 2 and 8 and 2 * 8 is a perfect square.
#
# Constraints:
# 1 <= n == nums.length <= 104
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def maximumSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from math import gcd
        from collections import defaultdict

        def get_square_free_part(x):
            res = 1
            d = 2
            while d * d <= x:
                count = 0
                while x % d == 0:
                    x //= d
                    count += 1
                if count % 2 == 1:
                    res *= d
                d += 1
            if x > 1:
                res *= x
            return res

        square_free_map = defaultdict(int)
        for i, num in enumerate(nums):
            sfp = get_square_free_part(num)
            square_free_map[sfp] += num

        return max(square_free_map.values())