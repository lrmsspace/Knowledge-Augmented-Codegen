# Source: https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integers, m and k, and an integer array nums.
# A sequence of integers seq is called magical if:
#
#
# 	seq has a size of m.
# 	0 <= seq[i] < nums.length
# 	The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1] has k set bits.
#
#
# The array product of this sequence is defined as prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).
#
# Return the sum of the array products for all valid magical sequences.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# A set bit refers to a bit in the binary representation of a number that has a value of 1.
#
# Example:
# Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
#
# Output: 991600007
#
# Explanation:
#
# All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an array product of 1013.
#
# Constraints:
# 1 <= k <= m <= 30
# 	1 <= nums.length <= 50
# 	1 <= nums[i] <= 108
#

class Solution(object):
    def magicalSum(self, m, k, nums):
        """
        :type m: int
        :type k: int
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)

        # Count of numbers with i-th bit set
        count = [0] * 31
        for num in nums:
            bits = bin(num).count('1')
            count[bits] += 1

        # dp[i][j]: number of ways to form sequences of length i with j set bits
        dp = [[0] * (k + 1) for _ in range(m + 1)]
        dp[0][0] = 1

        for length in range(1, m + 1):
            for set_bits in range(k + 1):
                for bits in range(31):
                    if set_bits >= bits:
                        dp[length][set_bits] += dp[length - 1][set_bits - bits] * count[bits]
                        dp[length][set_bits] %= MOD

        # Calculate the sum of products
        result = 0
        for length in range(1, m + 1):
            result += dp[length][k]
            result %= MOD

        return result