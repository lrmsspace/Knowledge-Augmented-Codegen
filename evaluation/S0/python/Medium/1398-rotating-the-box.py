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

class Solution(object):
    def rotateTheBox(self, boxGrid):
        """
        :type boxGrid: List[List[str]]
        :rtype: List[List[str]]
        """
        m, n = len(boxGrid), len(boxGrid[0])
        rotatedBox = [[''] * m for _ in range(n)]
        
        for i in range(m):
            empty = n - 1
            for j in range(n - 1, -1, -1):
                if boxGrid[i][j] == '*':
                    rotatedBox[j][m - 1 - i] = '*'
                    empty = j - 1
                elif boxGrid[i][j] == '#':
                    rotatedBox[empty][m - 1 - i] = '#'
                    empty -= 1
            for k in range(empty, -1, -1):
                rotatedBox[k][m - 1 - i] = '.'
        
        return rotatedBox