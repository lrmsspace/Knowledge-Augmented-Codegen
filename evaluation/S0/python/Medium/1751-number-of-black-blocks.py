# Source: https://leetcode.com/problems/number-of-black-blocks/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers m and n representing the dimensions of a 0-indexed m x n grid.
#
# You are also given a 0-indexed 2D integer matrix coordinates, where coordinates[i] = [x, y] indicates that the cell with coordinates [x, y] is colored black. All cells in the grid that do not appear in coordinates are white.
#
# A block is defined as a 2 x 2 submatrix of the grid. More formally, a block with cell [x, y] as its top-left corner where 0 <= x < m - 1 and 0 <= y < n - 1 contains the coordinates [x, y], [x + 1, y], [x, y + 1], and [x + 1, y + 1].
#
# Return a 0-indexed integer array arr of size 5 such that arr[i] is the number of blocks that contains exactly i black cells.
#
# Example:
# Input: m = 3, n = 3, coordinates = [[0,0]]
# Output: [3,1,0,0,0]
# Explanation: The grid looks like this:
#
# There is only 1 block with one black cell, and it is the block starting with cell [0,0].
# The other 3 blocks start with cells [0,1], [1,0] and [1,1]. They all have zero black cells. 
# Thus, we return [3,1,0,0,0].
#
# Constraints:
# 2 <= m <= 105
# 	2 <= n <= 105
# 	0 <= coordinates.length <= 104
# 	coordinates[i].length == 2
# 	0 <= coordinates[i][0] < m
# 	0 <= coordinates[i][1] < n
# 	It is guaranteed that coordinates contains pairwise distinct coordinates.
#

class Solution(object):
    def countBlackBlocks(self, m, n, coordinates):
        """
        :type m: int
        :type n: int
        :type coordinates: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict

        block_count = defaultdict(int)
        directions = [(0, 0), (0, -1), (-1, 0), (-1, -1)]

        for x, y in coordinates:
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m - 1 and 0 <= ny < n - 1:
                    block_count[(nx, ny)] += 1

        result = [0] * 5
        total_blocks = (m - 1) * (n - 1)
        counted_blocks = sum(block_count.values())

        for count in block_count.values():
            result[count] += 1

        result[0] = total_blocks - counted_blocks

        return result