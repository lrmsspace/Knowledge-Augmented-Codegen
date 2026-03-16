# Source: https://leetcode.com/problems/minimum-cuts-to-divide-a-circle/   |   Difficulty: Easy
#
# Problem Description:
# A valid cut in a circle can be:
#
#
# 	A cut that is represented by a straight line that touches two points on the edge of the circle and passes through its center, or
# 	A cut that is represented by a straight line that touches one point on the edge of the circle and its center.
#
#
# Some valid and invalid cuts are shown in the figures below.
#
# Given the integer n, return the minimum number of cuts needed to divide a circle into n equal slices.
#
# Example:
# Input: n = 4
# Output: 2
# Explanation: 
# The above figure shows how cutting the circle twice through the middle divides it into 4 equal slices.
#
# Constraints:
# 1 <= n <= 100
#

class Solution(object):
    def numberOfCuts(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1:
            return 0
        elif n % 2 == 0:
            return n // 2
        else:
            return n