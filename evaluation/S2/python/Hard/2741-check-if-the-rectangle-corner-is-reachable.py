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
    def canReachCorner(self, xCorner, yCorner, circles):
        """
        :type xCorner: int
        :type yCorner: int
        :type circles: List[List[int]]
        :rtype: bool
        """
        from collections import deque
        
        # Directions for moving up, down, left, right
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        
        # Function to check if a point is inside any circle
        def is_inside_circle(x, y):
            for cx, cy, r in circles:
                if (x - cx) ** 2 + (y - cy) ** 2 < r ** 2:
                    return True
            return False
        
        # BFS initialization
        queue = deque([(0, 0)])
        visited = set((0, 0))
        
        while queue:
            x, y = queue.popleft()
            
            # Check if we have reached the target corner
            if (x, y) == (xCorner, yCorner):
                return True
            
            # Explore neighbors
            for dx, dy in directions:
                new_x, new_y = x + dx, y + dy
                
                # Check boundaries and if the new point is not inside any circle and not visited
                if 0 <= new_x <= xCorner and 0 <= new_y <= yCorner and not is_inside_circle(new_x, new_y) and (new_x, new_y) not in visited:
                    visited.add((new_x, new_y))
                    queue.append((new_x, new_y))
        
        return False