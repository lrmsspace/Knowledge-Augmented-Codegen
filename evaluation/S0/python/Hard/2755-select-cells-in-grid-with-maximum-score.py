# Source: https://leetcode.com/problems/select-cells-in-grid-with-maximum-score/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D matrix grid consisting of positive integers.
#
# You have to select one or more cells from the matrix such that the following conditions are satisfied:
#
#
# 	No two selected cells are in the same row of the matrix.
# 	The values in the set of selected cells are unique.
#
#
# Your score will be the sum of the values of the selected cells.
#
# Return the maximum score you can achieve.
#
# Example:
# Input: grid = [[1,2,3],[4,3,2],[1,1,1]]
#
# Output: 8
#
# Explanation:
#
#
#
# We can select the cells with values 1, 3, and 4 that are colored above.
#
# Constraints:
# 1 <= grid.length, grid[i].length <= 10
# 	1 <= grid[i][j] <= 100
#

class Solution(object):
    def maxScore(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from itertools import combinations

        rows, cols = len(grid), len(grid[0])
        max_score = 0

        def backtrack(row, used, current_sum):
            nonlocal max_score
            if row == rows:
                max_score = max(max_score, current_sum)
                return

            for col in range(cols):
                val = grid[row][col]
                if val not in used:
                    used.add(val)
                    backtrack(row + 1, used, current_sum + val)
                    used.remove(val)

            # Also consider skipping the current row
            backtrack(row + 1, used, current_sum)

        backtrack(0, set(), 0)
        return max_score