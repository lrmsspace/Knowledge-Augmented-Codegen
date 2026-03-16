# Source: https://leetcode.com/problems/check-if-the-rectangle-corner-is-reachable/   |   Difficulty: Hard
#
# Problem Description:
# You are given two positive integers xCorner and yCorner, and a 2D array circles, where circles[i] = [xi, yi, ri] denotes a circle with center at (xi, yi) and radius ri.
#
# There is a rectangle in the coordinate plane with its bottom left corner at the origin and top right corner at the coordinate (xCorner, yCorner). You need to check whether there is a path from the bottom left corner to the top right corner such that the entire path lies inside the rectangle, does not touch or lie inside any circle, and touches the rectangle only at the two corners.
#
# Return true if such a path exists, and false otherwise.
#
# Example:
# Input: xCorner = 3, yCorner = 4, circles = [[2,1,1]]
#
# Output: true
#
# Explanation:
#
#
#
# The black curve shows a possible path between (0, 0) and (3, 4).
#
# Constraints:
# 3 <= xCorner, yCorner <= 109
# 	1 <= circles.length <= 1000
# 	circles[i].length == 3
# 	1 <= xi, yi, ri <= 109
#

class Solution(object):
    def canReachCorner(self, xCorner, yCorner, circles):
        """
        :type xCorner: int
        :type yCorner: int
        :type circles: List[List[int]]
        :rtype: bool
        """
        from collections import deque

        def is_inside_circle(x, y):
            for cx, cy, r in circles:
                if (x - cx) ** 2 + (y - cy) ** 2 <= r ** 2:
                    return True
            return False

        directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
        visited = set()
        queue = deque([(0, 0)])
        visited.add((0, 0))

        while queue:
            x, y = queue.popleft()

            if x == xCorner and y == yCorner:
                return True

            for dx, dy in directions:
                nx, ny = x + dx, y + dy

                if 0 <= nx <= xCorner and 0 <= ny <= yCorner and (nx, ny) not in visited and not is_inside_circle(nx, ny):
                    visited.add((nx, ny))
                    queue.append((nx, ny))

        return False