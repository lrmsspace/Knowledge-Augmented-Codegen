# Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given 3 positive integers zero, one, and limit.
#
# A binary array arr is called stable if:
#
#
# 	The number of occurrences of 0 in arr is exactly zero.
# 	The number of occurrences of 1 in arr is exactly one.
# 	Each subarray of arr with a size greater than limit must contain both 0 and 1.
#
#
# Return the total number of stable binary arrays.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: zero = 1, one = 1, limit = 2
#
# Output: 2
#
# Explanation:
#
# The two possible stable binary arrays are [1,0] and [0,1].
#
# Constraints:
# 1 <= zero, one, limit <= 1000
#

class Solution(object):
    def numberOfStableArrays(self, zero, one, limit):
        """
        :type zero: int
        :type one: int
        :type limit: int
        :rtype: int
        """
        MOD = 10**9 + 7

        # dp[i][j] 表示长度为 i，且最后连续 1 的个数不超过 j 的数组数量
        dp = [[0] * (limit + 1) for _ in range(one + 1)]
        dp[0][0] = 1

        for i in range(1, one + 1):
            for j in range(1, limit + 1):
                dp[i][j] = (dp[i - 1][j - 1] + dp[i][j - 1]) % MOD

        total_arrays = sum(dp[one]) % MOD
        return total_arrays