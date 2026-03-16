# Source: https://leetcode.com/problems/max-points-on-a-line/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.
#
# Example:
# Input: points = [[1,1],[2,2],[3,3]]
# Output: 3
#
# Constraints:
# 1 <= points.length <= 300
# 	points[i].length == 2
# 	-104 <= xi, yi <= 104
# 	All the points are unique.
#

class Solution(object):
    def maxPoints(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        if len(points) <= 2:
            return len(points)
        
        def gcd(a, b):
            while b:
                a, b = b, a % b
            return a
        
        max_points = 0
        
        for i in range(len(points)):
            slopes = {}
            duplicate = 1
            
            for j in range(i + 1, len(points)):
                if points[i] == points[j]:
                    duplicate += 1
                else:
                    dy = points[j][1] - points[i][1]
                    dx = points[j][0] - points[i][0]
                    
                    if dx == 0:
                        slope = ('inf', 0)
                    elif dy == 0:
                        slope = (0, 'inf')
                    else:
                        g = gcd(dy, dx)
                        slope = (dy // g, dx // g)
                    
                    if slope in slopes:
                        slopes[slope] += 1
                    else:
                        slopes[slope] = 1
            
            current_max = duplicate
            for count in slopes.values():
                current_max = max(current_max, count + duplicate)
            
            max_points = max(max_points, current_max)
        
        return max_points