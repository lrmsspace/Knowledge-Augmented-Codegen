# Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/   |   Difficulty: Medium
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
# The two possible stable binary arrays are [1,0] and [0,1], as both arrays have a single 0 and a single 1, and no subarray has a length greater than 2.
#
# Constraints:
# 1 <= zero, one, limit <= 200
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

        # dp[i][j] 表示长度为 i，且以 j 结尾的稳定数组数量
        dp = [[0, 0] for _ in range(zero + one + 1)]
        dp[0][0] = 1  # 空数组视为以 0 结尾的稳定数组
        dp[0][1] = 1  # 空数组视为以 1 结尾的稳定数组

        for length in range(1, zero + one + 1):
            for end in [0, 1]:
                for k in range(1, limit + 1):
                    if length - k < 0:
                        break
                    dp[length][end] += dp[length - k][1 - end]
                    dp[length][end] %= MOD

        return (dp[zero + one][0] + dp[zero + one][1]) % MOD