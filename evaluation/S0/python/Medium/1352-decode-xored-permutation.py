# Source: https://leetcode.com/problems/decode-xored-permutation/   |   Difficulty: Medium
#
# Problem Description:
# There is an integer array perm that is a permutation of the first n positive integers, where n is always odd.
#
# It was encoded into another integer array encoded of length n - 1, such that encoded[i] = perm[i] XOR perm[i + 1]. For example, if perm = [1,3,2], then encoded = [2,1].
#
# Given the encoded array, return the original array perm. It is guaranteed that the answer exists and is unique.
#
# Example:
# Input: encoded = [3,1]
# Output: [1,2,3]
# Explanation: If perm = [1,2,3], then encoded = [1 XOR 2,2 XOR 3] = [3,1]
#
# Constraints:
# 3 <= n < 105
# 	n is odd.
# 	encoded.length == n - 1
#

class Solution(object):
    def decode(self, encoded):
        """
        :type encoded: List[int]
        :rtype: List[int]
        """
        n = len(encoded) + 1
        total = 0
        for i in range(1, n + 1):
            total ^= i
        
        odd = 0
        for i in range(1, n - 1, 2):
            odd ^= encoded[i]
        
        perm = [0] * n
        perm[0] = total ^ odd
        
        for i in range(1, n):
            perm[i] = perm[i - 1] ^ encoded[i - 1]
        
        return perm