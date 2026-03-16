# Source: https://leetcode.com/problems/strange-printer-ii/   |   Difficulty: Hard
#
# Problem Description:
# There is a strange printer with the following two special requirements:
#
#
# 	On each turn, the printer will print a solid rectangular pattern of a single color on the grid. This will cover up the existing colors in the rectangle.
# 	Once the printer has used a color for the above operation, the same color cannot be used again.
#
#
# You are given a m x n matrix targetGrid, where targetGrid[row][col] is the color in the position (row, col) of the grid.
#
# Return true if it is possible to print the matrix targetGrid, otherwise, return false.
#
# Example:
# Input: targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
# Output: true
#
# Constraints:
# m == targetGrid.length
# 	n == targetGrid[i].length
# 	1 <= m, n <= 60
# 	1 <= targetGrid[row][col] <= 60
#

class Solution(object):
    def isPrintable(self, targetGrid):
        """
        :type targetGrid: List[List[int]]
        :rtype: bool
        """
        m, n = len(targetGrid), len(targetGrid[0])
        colors = {}
        
        for i in range(m):
            for j in range(n):
                c = targetGrid[i][j]
                if c not in colors:
                    colors[c] = [i, i, j, j]
                else:
                    colors[c][0] = min(colors[c][0], i)
                    colors[c][1] = max(colors[c][1], i)
                    colors[c][2] = min(colors[c][2], j)
                    colors[c][3] = max(colors[c][3], j)
        
        graph = {c: set() for c in colors}
        indegree = {c: 0 for c in colors}
        
        for c, (x1, x2, y1, y2) in colors.items():
            for i in range(x1, x2 + 1):
                for j in range(y1, y2 + 1):
                    if targetGrid[i][j] != c:
                        if targetGrid[i][j] not in graph[c]:
                            graph[c].add(targetGrid[i][j])
                            indegree[targetGrid[i][j]] += 1
        
        queue = [c for c in indegree if indegree[c] == 0]
        visited = 0
        
        while queue:
            curr = queue.pop(0)
            visited += 1
            for nei in graph[curr]:
                indegree[nei] -= 1
                if indegree[nei] == 0:
                    queue.append(nei)
        
        return visited == len(colors)