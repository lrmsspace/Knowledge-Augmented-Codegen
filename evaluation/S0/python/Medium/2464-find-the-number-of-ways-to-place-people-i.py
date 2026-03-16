# Source: https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].
#
# Count the number of pairs of points (A, B), where
#
#
# 	A is on the upper left side of B, and
# 	there are no other points in the rectangle (or line) they make (including the border), except for the points A and B.
#
#
# Return the count.
#
# Example:
# Input: points = [[1,1],[2,2],[3,3]]
#
# Output: 0
#
# Explanation:
#
#
#
# There is no way to choose A and B such that A is on the upper left side of B.
#
# Constraints:
# 2 <= n <= 50
# 	points[i].length == 2
# 	0 <= points[i][0], points[i][1] <= 50
# 	All points[i] are distinct.
#

class Solution(object):
    def numberOfPairs(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        count = 0
        n = len(points)
        
        for i in range(n):
            for j in range(n):
                if i != j:
                    if points[i][0] < points[j][0] and points[i][1] > points[j][1]:
                        # Check if there are no other points in the rectangle
                        is_valid = True
                        for k in range(n):
                            if k != i and k != j:
                                if (points[i][0] <= points[k][0] <= points[j][0] and
                                    points[j][1] <= points[k][1] <= points[i][1]):
                                    is_valid = False
                                    break
                        if is_valid:
                            count += 1
        
        return count