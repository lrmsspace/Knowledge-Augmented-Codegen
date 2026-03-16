# Source: https://leetcode.com/problems/flood-fill/   |   Difficulty: Easy
#
# Problem Description:
# You are given an image represented by an m x n grid of integers image, where image[i][j] represents the pixel value of the image. You are also given three integers sr, sc, and color. Your task is to perform a flood fill on the image starting from the pixel image[sr][sc].
#
# To perform a flood fill:
#
#
# 	Begin with the starting pixel and change its color to color.
# 	Perform the same process for each pixel that is directly adjacent (pixels that share a side with the original pixel, either horizontally or vertically) and shares the same color as the starting pixel.
# 	Keep repeating this process by checking neighboring pixels of the updated pixels and modifying their color if it matches the original color of the starting pixel.
# 	The process stops when there are no more adjacent pixels of the original color to update.
#
#
# Return the modified image after performing the flood fill.
#
# Example:
# Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
#
# Output: [[2,2,2],[2,2,0],[2,0,1]]
#
# Explanation:
#
#
#
# From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
#
# Note the bottom corner is not colored 2, because it is not horizontally or vertically connected to the starting pixel.
#
# Constraints:
# m == image.length
# 	n == image[i].length
# 	1 <= m, n <= 50
# 	0 <= image[i][j], color < 216
# 	0 <= sr < m
# 	0 <= sc < n
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
    def floodFill(self, image, sr, sc, color):
        """
        :type image: List[List[int]]
        :type sr: int
        :type sc: int
        :type color: int
        :rtype: List[List[int]]
        """
        if image[sr][sc] == color:
            return image
        
        original_color = image[sr][sc]
        rows, cols = len(image), len(image[0])
        
        def dfs(r, c):
            if r < 0 or r >= rows or c < 0 or c >= cols:
                return
            if image[r][c] != original_color:
                return
            
            image[r][c] = color
            
            dfs(r + 1, c)  # down
            dfs(r - 1, c)  # up
            dfs(r, c + 1)  # right
            dfs(r, c - 1)  # left
        
        dfs(sr, sc)
        return image