# Source: https://leetcode.com/problems/image-smoother/   |   Difficulty: Easy
#
# Problem Description:
# An image smoother is a filter of the size 3 x 3 that can be applied to each cell of an image by rounding down the average of the cell and the eight surrounding cells (i.e., the average of the nine cells in the blue smoother). If one or more of the surrounding cells of a cell is not present, we do not consider it in the average (i.e., the average of the four cells in the red smoother).
#
# Given an m x n integer matrix img representing the grayscale of an image, return the image after applying the smoother on each cell of it.
#
# Example:
# Input: img = [[1,1,1],[1,0,1],[1,1,1]]
# Output: [[0,0,0],[0,0,0],[0,0,0]]
# Explanation:
# For the points (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
# For the points (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
# For the point (1,1): floor(8/9) = floor(0.88888889) = 0
#
# Constraints:
# m == img.length
# 	n == img[i].length
# 	1 <= m, n <= 200
# 	0 <= img[i][j] <= 255
#

class Solution(object):
    def imageSmoother(self, img):
        """
        :type img: List[List[int]]
        :rtype: List[List[int]]
        """
        import math
        rows = len(img)
        cols = len(img[0])
        result = [[0 for _ in range(cols)] for _ in range(rows)]
        
        directions = [(-1, -1), (-1, 0), (-1, 1),
                      (0, -1),  (0, 0),  (0, 1),
                      (1, -1),  (1, 0),  (1, 1)]
        
        for r in range(rows):
            for c in range(cols):
                total = 0
                count = 0
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < rows and 0 <= nc < cols:
                        total += img[nr][nc]
                        count += 1
                result[r][c] = math.floor(total / count)
        
        return result