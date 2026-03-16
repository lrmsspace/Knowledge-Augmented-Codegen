# Source: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D binary array grid. You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides such that all the 1's in grid lie inside these rectangles.
#
# Return the minimum possible sum of the area of these rectangles.
#
# Note that the rectangles are allowed to touch.
#
# Example:
# Input: grid = [[1,0,1],[1,1,1]]
#
# Output: 5
#
# Explanation:
#
#
#
#
# 	The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
# 	The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
# 	The 1 at (1, 1) is covered by a rectangle of area 1.
#
# Constraints:
# 1 <= grid.length, grid[i].length <= 30
# 	grid[i][j] is either 0 or 1.
# 	The input is generated such that there are at least three 1's in grid.
#

class Solution(object):
    def minimumSum(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        ones = [(i, j) for i in range(m) for j in range(n) if grid[i][j] == 1]

        if len(ones) < 3:
            return -1

        def area(r1, r2):
            if not r1 or not r2:
                return 0
            x1 = min(x for x, y in r1 + r2)
            x2 = max(x for x, y in r1 + r2)
            y1 = min(y for x, y in r1 + r2)
            y2 = max(y for x, y in r1 + r2)
            return (x2 - x1 + 1) * (y2 - y1 + 1)

        min_area_sum = float('inf')

        for i in range(len(ones)):
            for j in range(i + 1, len(ones)):
                for k in range(j + 1, len(ones)):
                    r1 = [ones[i]]
                    r2 = [ones[j]]
                    r3 = [ones[k]]

                    area_sum = area(r1, []) + area(r2, []) + area(r3, [])
                    min_area_sum = min(min_area_sum, area_sum)

        return min_area_sum