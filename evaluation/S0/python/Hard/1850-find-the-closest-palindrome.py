# Source: https://leetcode.com/problems/find-the-closest-palindrome/   |   Difficulty: Hard
#
# Problem Description:
# Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
#
# The closest is defined as the absolute difference minimized between two integers.
#
# Example:
# Input: n = "123"
# Output: "121"
#
# Constraints:
# 1 <= n.length <= 18
# 	n consists of only digits.
# 	n does not have leading zeros.
# 	n is representing an integer in the range [1, 1018 - 1].
#

class Solution(object):
    def nearestPalindromic(self, n):
        """
        :type n: str
        :rtype: str
        """
        length = len(n)
        candidates = set()

        # Edge cases: 10..01 and 9..9
        candidates.add(str(10**length + 1))
        candidates.add(str(10**(length - 1) - 1))

        prefix = int(n[:(length + 1) // 2])

        for i in [-1, 0, 1]:
            new_prefix = str(prefix + i)
            if length % 2 == 0:
                palin = new_prefix + new_prefix[::-1]
            else:
                palin = new_prefix + new_prefix[-2::-1]
            candidates.add(palin)

        candidates.discard(n)

        closest = None
        min_diff = float('inf')

        for candidate in candidates:
            diff = abs(int(candidate) - int(n))
            if diff < min_diff or (diff == min_diff and int(candidate) < int(closest)):
                min_diff = diff
                closest = candidate

        return closest