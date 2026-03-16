# Source: https://leetcode.com/problems/cyclically-rotating-a-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.
#
# The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:
#
#
#
# A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:
#
# Return the matrix after applying k cyclic rotations to it.
#
# Example:
# Input: grid = [[40,10],[30,20]], k = 1
# Output: [[10,20],[40,30]]
# Explanation: The figures above represent the grid at every state.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	2 <= m, n <= 50
# 	Both m and n are even integers.
# 	1 <= grid[i][j] <= 5000
# 	1 <= k <= 109
#

class Solution(object):

    def rotateGrid(self, grid, k):

        """

        :type grid: List[List[int]]

        :type k: int

        :rtype: List[List[int]]

        """
        m = len(grid)
        n = len(grid[0])
        layers = min(m, n) // 2

        for layer in range(layers):
            elements = []

            # Extract the layer elements
            for j in range(layer, n - layer):
                elements.append(grid[layer][j])
            for i in range(layer + 1, m - layer - 1):
                elements.append(grid[i][n - layer - 1])
            for j in range(n - layer - 1, layer - 1, -1):
                elements.append(grid[m - layer - 1][j])
            for i in range(m - layer - 2, layer, -1):
                elements.append(grid[i][layer])

            # Calculate effective rotations
            rotation = k % len(elements)
            rotated_elements = elements[rotation:] + elements[:rotation]

            # Place back the rotated elements
            index = 0
            for j in range(layer, n - layer):
                grid[layer][j] = rotated_elements[index]
                index += 1
            for i in range(layer + 1, m - layer - 1):
                grid[i][n - layer - 1] = rotated_elements[index]
                index += 1
            for j in range(n - layer - 1, layer - 1, -1):
                grid[m - layer - 1][j] = rotated_elements[index]
                index += 1
            for i in range(m - layer - 2, layer, -1):
                grid[i][layer] = rotated_elements[index]
                index += 1

        return grid