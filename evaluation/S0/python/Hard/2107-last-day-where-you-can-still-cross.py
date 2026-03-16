# Source: https://leetcode.com/problems/last-day-where-you-can-still-cross/   |   Difficulty: Hard
#
# Problem Description:
# There is a 1-based binary matrix where 0 represents land and 1 represents water. You are given integers row and col representing the number of rows and columns in the matrix, respectively.
#
# Initially on day 0, the entire matrix is land. However, each day a new cell becomes flooded with water. You are given a 1-based 2D array cells, where cells[i] = [ri, ci] represents that on the ith day, the cell on the rith row and cith column (1-based coordinates) will be covered with water (i.e., changed to 1).
#
# You want to find the last day that it is possible to walk from the top to the bottom by only walking on land cells. You can start from any cell in the top row and end at any cell in the bottom row. You can only travel in the four cardinal directions (left, right, up, and down).
#
# Return the last day where it is possible to walk from the top to the bottom by only walking on land cells.
#
# Example:
# Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
# Output: 2
# Explanation: The above image depicts how the matrix changes each day starting from day 0.
# The last day where it is possible to cross from top to bottom is on day 2.
#
# Constraints:
# 2 <= row, col <= 2 * 104
# 	4 <= row * col <= 2 * 104
# 	cells.length == row * col
# 	1 <= ri <= row
# 	1 <= ci <= col
# 	All the values of cells are unique.
#

class Solution(object):
    def latestDayToCross(self, row, col, cells):
        """
        :type row: int
        :type col: int
        :type cells: List[List[int]]
        :rtype: int
        """
        def can_cross(day):
            grid = [[0] * col for _ in range(row)]
            for r, c in cells[:day]:
                grid[r - 1][c - 1] = 1

            visited = [[False] * col for _ in range(row)]

            def dfs(r, c):
                if r < 0 or r >= row or c < 0 or c >= col or grid[r][c] == 1 or visited[r][c]:
                    return False
                if r == row - 1:
                    return True
                visited[r][c] = True
                return (dfs(r + 1, c) or dfs(r - 1, c) or
                        dfs(r, c + 1) or dfs(r, c - 1))

            for c in range(col):
                if grid[0][c] == 0 and dfs(0, c):
                    return True
            return False

        left, right = 1, len(cells)
        result = 0
        while left <= right:
            mid = (left + right) // 2
            if can_cross(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        return result