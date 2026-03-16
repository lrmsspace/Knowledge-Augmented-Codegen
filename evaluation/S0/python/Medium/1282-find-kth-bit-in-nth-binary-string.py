# Source: https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/   |   Difficulty: Medium
#
# Problem Description:
# Given two positive integers n and k, the binary string Sn is formed as follows:
#
#
# 	S1 = "0"
# 	Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
#
#
# Where + denotes the concatenation operation, reverse(x) returns the reversed string x, and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).
#
# For example, the first four strings in the above sequence are:
#
#
# 	S1 = "0"
# 	S2 = "011"
# 	S3 = "0111001"
# 	S4 = "011100110110001"
#
#
# Return the kth bit in Sn. It is guaranteed that k is valid for the given n.
#
# Example:
# Input: n = 3, k = 1
# Output: "0"
# Explanation: S3 is "0111001".
# The 1st bit is "0".
#
# Constraints:
# 1 <= n <= 20
# 	1 <= k <= 2n - 1
#

class Solution(object):
    def findKthBit(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        if n == 1:
            return '0'
        
        length = 2 ** n - 1
        mid = (length // 2) + 1
        
        if k == mid:
            return '1'
        elif k < mid:
            return self.findKthBit(n - 1, k)
        else:
            mirrored_k = length - k + 1
            bit = self.findKthBit(n - 1, mirrored_k)
            return '0' if bit == '1' else '1'