# Source: https://leetcode.com/problems/rotating-the-box/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n matrix of characters boxGrid representing a side-view of a box. Each cell of the box is one of the following:
#
#
# 	A stone '#'
# 	A stationary obstacle '*'
# 	Empty '.'
#
#
# The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and the inertia from the box's rotation does not affect the stones' horizontal positions.
#
# It is guaranteed that each stone in boxGrid rests on an obstacle, another stone, or the bottom of the box.
#
# Return an n x m matrix representing the box after the rotation described above.
#
# Example:
# Input: boxGrid = [["#",".","#"]]
# Output: [["."],
#          ["#"],
#          ["#"]]
#
# Constraints:
# m == boxGrid.length
# 	n == boxGrid[i].length
# 	1 <= m, n <= 500
# 	boxGrid[i][j] is either '#', '*', or '.'.
#
# Helpful references (internal KB):
# - Convex Hull construction (geometry, array, enumeration)
#   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
#   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
#   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
#   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
#   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
# - Gauss method for solving system of linea (bitset, matrix, simulation)
#   • When to use: Use when determining the number of solutions (zero, one, or infinite) for a system of linear equations, or to find the unique solution if it exists. It is suitable for solving systems represented as an augmented matrix.
#   • Idea: Gaussian elimination systematically transforms an augmented matrix into row echelon form using elementary row operations to solve a system of linear equations. It determines the existence and values of solutions in O(N^3) time for an N x N system.
#   • Invariants: The submatrix formed by rows 0 to current_row - 1 is in row echelon form.; For the current column, all elements below the pivot in previous columns are zero.
#   • Tips: Use a small epsilon for floating-point comparisons to handle precision issues.; Implement partial pivoting to enhance numerical stability by selecting the largest absolute value.
#   • Pitfalls: Failing to account for floating-point precision errors can lead to incorrect results.; Improper handling of free variables can misrepresent infinite solution sets.
# - Minimum Enclosing Circle (geometry, number, simulation)
#   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
#   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
#   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
#   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
#   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def rotateTheBox(self, boxGrid):
        """
        :type boxGrid: List[List[str]]
        :rtype: List[List[str]]
        """
        m = len(boxGrid)
        n = len(boxGrid[0]) if m > 0 else 0
        
        # Step 1: Simulate gravity for each row
        for i in range(m):
            empty_pos = n - 1  # Start from the rightmost position
            for j in range(n - 1, -1, -1):
                if boxGrid[i][j] == '*':
                    empty_pos = j - 1  # Reset empty position to left of obstacle
                elif boxGrid[i][j] == '#':
                    if j != empty_pos:
                        boxGrid[i][empty_pos], boxGrid[i][j] = boxGrid[i][j], '.'
                    empty_pos -= 1  # Move empty position left
        
        # Step 2: Rotate the box 90 degrees clockwise
        rotated_box = [[''] * m for _ in range(n)]
        for i in range(m):
            for j in range(n):
                rotated_box[j][m - 1 - i] = boxGrid[i][j]
        
        return rotated_box