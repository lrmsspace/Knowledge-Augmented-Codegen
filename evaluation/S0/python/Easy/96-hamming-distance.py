# Source: https://leetcode.com/problems/hamming-distance/   |   Difficulty: Easy
#
# Problem Description:
# The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
#
# Given two integers x and y, return the Hamming distance between them.
#
# Example:
# Input: x = 1, y = 4
# Output: 2
# Explanation:
# 1   (0 0 0 1)
# 4   (0 1 0 0)
#        ↑   ↑
# The above arrows point to positions where the corresponding bits are different.
#
# Constraints:
# 0 <= x, y <= 231 - 1
#
#
#  
# Note: This question is the same as  2220: Minimum Bit Flips to Convert Number.
#

class Solution(object):
    def hammingDistance(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        return bin(x ^ y).count('1')