# Source: https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n integer matrix grid​​​.
#
# A rhombus sum is the sum of the elements that form the border of a regular rhombus shape in grid​​​. The rhombus must have the shape of a square rotated 45 degrees with each of the corners centered in a grid cell. Below is an image of four valid rhombus shapes with the corresponding colored cells that should be included in each rhombus sum:
#
# Note that the rhombus can have an area of 0, which is depicted by the purple rhombus in the bottom right corner.
#
# Return the biggest three distinct rhombus sums in the grid in descending order. If there are less than three distinct values, return all of them.
#
# Example:
# Input: grid = [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
# Output: [228,216,211]
# Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
# - Blue: 20 + 3 + 200 + 5 = 228
# - Red: 200 + 2 + 10 + 4 = 216
# - Green: 5 + 200 + 4 + 2 = 211
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 50
# 	1 <= grid[i][j] <= 105
#

class Solution(object):
    def getBiggestThree(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: List[int]
        """
        m, n = len(grid), len(grid[0])
        rhombus_sums = set()

        for i in range(m):
            for j in range(n):
                # Single cell rhombus
                rhombus_sums.add(grid[i][j])

                # Larger rhombuses
                for size in range(1, min(m, n)):
                    if i - size < 0 or i + size >= m or j - size < 0 or j + size >= n:
                        break

                    total = 0
                    # Top to right
                    for k in range(size):
                        total += grid[i - k][j + k]
                    # Right to bottom
                    for k in range(size):
                        total += grid[i + k][j + k]
                    # Bottom to left
                    for k in range(size):
                        total += grid[i + k][j - k]
                    # Left to top
                    for k in range(size):
                        total += grid[i - k][j - k]

                    # Subtract the corners as they are added twice
                    total -= (grid[i - size][j] + grid[i + size][j] + grid[i][j - size] + grid[i][j + size])

                    rhombus_sums.add(total)

        return sorted(rhombus_sums, reverse=True)[:3]