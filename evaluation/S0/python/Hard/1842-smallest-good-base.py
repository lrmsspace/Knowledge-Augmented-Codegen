# Source: https://leetcode.com/problems/smallest-good-base/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer n represented as a string, return the smallest good base of n.
#
# We call k >= 2 a good base of n, if all digits of n base k are 1's.
#
# Example:
# Input: n = "13"
# Output: "3"
# Explanation: 13 base 3 is 111.
#
# Constraints:
# n is an integer in the range [3, 1018].
# 	n does not contain any leading zeros.
#

class Solution(object):
    def smallestGoodBase(self, n):
        """
        :type n: str
        :rtype: str
        """
        n = int(n)
        max_m = n.bit_length()  # 最大的 m 值
        
        for m in range(max_m, 1, -1):
            k = int(n**(1.0 / (m - 1)))
            if k < 2:
                continue
            
            # 计算等比数列的和
            total = (k**m - 1) // (k - 1)
            if total == n:
                return str(k)
        
        return str(n - 1)