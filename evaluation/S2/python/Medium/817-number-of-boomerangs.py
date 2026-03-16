# Source: https://leetcode.com/problems/number-of-boomerangs/   |   Difficulty: Medium
#
# Problem Description:
# You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
#
# Return the number of boomerangs.
#
# Example:
# Input: points = [[0,0],[1,0],[2,0]]
# Output: 2
# Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
#
# Constraints:
# n == points.length
# 	1 <= n <= 500
# 	points[i].length == 2
# 	-104 <= xi, yi <= 104
# 	All the points are unique.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfBoomerangs(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict
        count = 0
        for i in range(len(points)):
            dist_count = defaultdict(int)
            for j in range(len(points)):
                if i != j:
                    dx = points[i][0] - points[j][0]
                    dy = points[i][1] - points[j][1]
                    dist = dx * dx + dy * dy
                    dist_count[dist] += 1
            
            for k in dist_count:
                c = dist_count[k]
                count += c * (c - 1)  # P(c, 2) = c! / (c-2)! = c * (c-1)
        
        return count