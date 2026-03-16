# Source: https://leetcode.com/problems/distribute-repeating-integers/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities, quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:
#
#
# 	The ith customer gets exactly quantity[i] integers,
# 	The integers the ith customer gets are all equal, and
# 	Every customer is satisfied.
#
#
# Return true if it is possible to distribute nums according to the above conditions.
#
# Example:
# Input: nums = [1,2,3,4], quantity = [2]
# Output: false
# Explanation: The 0th customer cannot be given two different integers.
#
# Constraints:
# n == nums.length
# 	1 <= n <= 105
# 	1 <= nums[i] <= 1000
# 	m == quantity.length
# 	1 <= m <= 10
# 	1 <= quantity[i] <= 105
# 	There are at most 50 unique values in nums.
#

class Solution(object):
    def canDistribute(self, nums, quantity):
        """
        :type nums: List[int]
        :type quantity: List[int]
        :rtype: bool
        """
        from collections import Counter
        from functools import lru_cache

        count = list(Counter(nums).values())
        m = len(quantity)
        full_mask = (1 << m) - 1

        @lru_cache(None)
        def backtrack(index, mask):
            if mask == full_mask:
                return True
            if index == len(count):
                return False

            if backtrack(index + 1, mask):
                return True

            for submask in range(1, full_mask + 1):
                if (submask & mask) == 0:
                    total = sum(quantity[i] for i in range(m) if (submask >> i) & 1)
                    if total <= count[index]:
                        if backtrack(index + 1, mask | submask):
                            return True

            return False

        return backtrack(0, 0)