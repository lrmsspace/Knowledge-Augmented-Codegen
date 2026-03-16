# Source: https://leetcode.com/problems/count-of-sub-multisets-with-bounded-sum/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed array nums of non-negative integers, and two integers l and r.
#
# Return the count of sub-multisets within nums where the sum of elements in each subset falls within the inclusive range of [l, r].
#
# Since the answer may be large, return it modulo 109 + 7.
#
# A sub-multiset is an unordered collection of elements of the array in which a given value x can occur 0, 1, ..., occ[x] times, where occ[x] is the number of occurrences of x in the array.
#
# Note that:
#
#
# 	Two sub-multisets are the same if sorting both sub-multisets results in identical multisets.
# 	The sum of an empty multiset is 0.
#
# Example:
# Input: nums = [1,2,2,3], l = 6, r = 6
# Output: 1
# Explanation: The only subset of nums that has a sum of 6 is {1, 2, 3}.
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	0 <= nums[i] <= 2 * 104
# 	Sum of nums does not exceed 2 * 104.
# 	0 <= l <= r <= 2 * 104
#

class Solution(object):
    def countSubMultisets(self, nums, l, r):
        """
        :type nums: List[int]
        :type l: int
        :type r: int
        :rtype: int
        """
        MOD = 10**9 + 7
        max_sum = sum(nums)
        dp = [0] * (max_sum + 1)
        dp[0] = 1

        from collections import Counter
        count = Counter(nums)

        for num, freq in count.items():
            new_dp = dp[:]
            for s in range(max_sum + 1):
                if dp[s]:
                    for k in range(1, freq + 1):
                        new_sum = s + num * k
                        if new_sum <= max_sum:
                            new_dp[new_sum] = (new_dp[new_sum] + dp[s]) % MOD
                        else:
                            break
            dp = new_dp

        result = sum(dp[l:r+1]) % MOD
        return result