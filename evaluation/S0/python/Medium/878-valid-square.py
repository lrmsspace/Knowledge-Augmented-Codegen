# Source: https://leetcode.com/problems/valid-square/   |   Difficulty: Medium
#
# Problem Description:
# Given the coordinates of four points in 2D space p1, p2, p3 and p4, return true if the four points construct a square.
#
# The coordinate of a point pi is represented as [xi, yi]. The input is not given in any order.
#
# A valid square has four equal sides with positive length and four equal angles (90-degree angles).
#
# Example:
# Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
# Output: true
#
# Constraints:
# p1.length == p2.length == p3.length == p4.length == 2
# 	-104 <= xi, yi <= 104
#

class Solution(object):
    def validSquare(self, p1, p2, p3, p4):
        """
        :type p1: List[int]
        :type p2: List[int]
        :type p3: List[int]
        :type p4: List[int]
        :rtype: bool
        """
        def dist_sq(a, b):
            return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2

        points = [p1, p2, p3, p4]
        dists = []

        for i in range(4):
            for j in range(i + 1, 4):
                dists.append(dist_sq(points[i], points[j]))

        dists.sort()
        
        side = dists[0]
        
        if side == 0:
            return False
        
        for i in range(1, 4):
            if dists[i] != side:
                return False
        
        for i in range(4, 6):
            if dists[i] != 2 * side:
                return False
        
        return True