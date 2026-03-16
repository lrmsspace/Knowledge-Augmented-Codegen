# Source: https://leetcode.com/problems/di-string-match/   |   Difficulty: Easy
#
# Problem Description:
# A permutation perm of n + 1 integers of all the integers in the range [0, n] can be represented as a string s of length n where:
#
#
# 	s[i] == 'I' if perm[i] < perm[i + 1], and
# 	s[i] == 'D' if perm[i] > perm[i + 1].
#
#
# Given a string s, reconstruct the permutation perm and return it. If there are multiple valid permutations perm, return any of them.
#
# Example:
# Input: s = "IDID"
# Output: [0,4,1,3,2]
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is either 'I' or 'D'.
#

class Solution(object):
    def diStringMatch(self, s):
        """
        :type s: str
        :rtype: List[int]
        """
        n = len(s)
        low, high = 0, n
        result = []
        
        for char in s:
            if char == 'I':
                result.append(low)
                low += 1
            else:  # char == 'D'
                result.append(high)
                high -= 1
        
        result.append(low)  # At the end, low == high
        
        return result