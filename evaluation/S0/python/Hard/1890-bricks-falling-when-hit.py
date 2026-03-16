# Source: https://leetcode.com/problems/bricks-falling-when-hit/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n binary grid, where each 1 represents a brick and 0 represents an empty space. A brick is stable if:
#
#
# 	It is directly connected to the top of the grid, or
# 	At least one other brick in its four adjacent cells is stable.
#
#
# You are also given an array hits, which is a sequence of erasures we want to apply. Each time we want to erase the brick at the location hits[i] = (rowi, coli). The brick on that location (if it exists) will disappear. Some other bricks may no longer be stable because of that erasure and will fall. Once a brick falls, it is immediately erased from the grid (i.e., it does not land on other stable bricks).
#
# Return an array result, where each result[i] is the number of bricks that will fall after the ith erasure is applied.
#
# Note that an erasure may refer to a location with no brick, and if it does, no bricks drop.
#
# Example:
# Input: grid = [[1,0,0,0],[1,1,1,0]], hits = [[1,0]]
# Output: [2]
# Explanation: Starting with the grid:
# [[1,0,0,0],
#  [1,1,1,0]]
# We erase the underlined brick at (1,0), resulting in the grid:
# [[1,0,0,0],
#  [0,1,1,0]]
# The two underlined bricks are no longer stable as they are no longer connected to the top nor adjacent to another stable brick, so they will fall. The resulting grid is:
# [[1,0,0,0],
#  [0,0,0,0]]
# Hence the result is [2].
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 200
# 	grid[i][j] is 0 or 1.
# 	1 <= hits.length <= 4 * 104
# 	hits[i].length == 2
# 	0 <= xi <= m - 1
# 	0 <= yi <= n - 1
# 	All (xi, yi) are unique.
#

class Solution(object):
    def hitBricks(self, grid, hits):
        """
        :type grid: List[List[int]]
        :type hits: List[List[int]]
        :rtype: List[int]
        """
        m, n = len(grid), len(grid[0])
        copy = [row[:] for row in grid]
        
        for x, y in hits:
            copy[x][y] = 0
            
        def index(x, y):
            return x * n + y
        
        parent = [i for i in range(m * n + 1)]
        size = [1] * (m * n + 1)
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            rootX, rootY = find(x), find(y)
            if rootX != rootY:
                parent[rootX] = rootY
                size[rootY] += size[rootX]
        
        for j in range(n):
            if copy[0][j] == 1:
                union(index(0, j), m * n)
        
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        
        for i in range(1, m):
            for j in range(n):
                if copy[i][j] == 1:
                    for dx, dy in directions:
                        ni, nj = i + dx, j + dy
                        if 0 <= ni < m and 0 <= nj < n and copy[ni][nj] == 1:
                            union(index(i, j), index(ni, nj))
        
        result = []
        
        for x, y in reversed(hits):
            if grid[x][y] == 0:
                result.append(0)
                continue
            
            preSize = size[find(m * n)]
            copy[x][y] = 1
            
            for dx, dy in directions:
                ni, nj = x + dx, y + dy
                if 0 <= ni < m and 0 <= nj < n and copy[ni][nj] == 1:
                    union(index(x, y), index(ni, nj))
            
            if x == 0:
                union(index(x, y), m * n)
            
            postSize = size[find(m * n)]
            result.append(max(0, postSize - preSize - 1))
        
        return result[::-1]