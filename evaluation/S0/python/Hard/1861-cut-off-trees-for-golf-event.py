# Source: https://leetcode.com/problems/cut-off-trees-for-golf-event/   |   Difficulty: Hard
#
# Problem Description:
# You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an m x n matrix. In this matrix:
#
#
# 	0 means the cell cannot be walked through.
# 	1 represents an empty cell that can be walked through.
# 	A number greater than 1 represents a tree in a cell that can be walked through, and this number is the tree's height.
#
#
# In one step, you can walk in any of the four directions: north, east, south, and west. If you are standing in a cell with a tree, you can choose whether to cut it off.
#
# You must cut off the trees in order from shortest to tallest. When you cut off a tree, the value at its cell becomes 1 (an empty cell).
#
# Starting from the point (0, 0), return the minimum steps you need to walk to cut off all the trees. If you cannot cut off all the trees, return -1.
#
# Note: The input is generated such that no two trees have the same height, and there is at least one tree needs to be cut off.
#
# Example:
# Input: forest = [[1,2,3],[0,0,4],[7,6,5]]
# Output: 6
# Explanation: Following the path above allows you to cut off the trees from shortest to tallest in 6 steps.
#
# Constraints:
# m == forest.length
# 	n == forest[i].length
# 	1 <= m, n <= 50
# 	0 <= forest[i][j] <= 109
# 	Heights of all trees are distinct.
#

class Solution(object):
    def cutOffTree(self, forest):
        """
        :type forest: List[List[int]]
        :rtype: int
        """
        import collections
        import heapq

        def bfs(sx, sy, tx, ty):
            if sx == tx and sy == ty:
                return 0
            m, n = len(forest), len(forest[0])
            visited = set()
            visited.add((sx, sy))
            queue = collections.deque()
            queue.append((sx, sy, 0))

            while queue:
                x, y, steps = queue.popleft()
                for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < m and 0 <= ny < n and (nx, ny) not in visited and forest[nx][ny] != 0:
                        if nx == tx and ny == ty:
                            return steps + 1
                        visited.add((nx, ny))
                        queue.append((nx, ny, steps + 1))
            return -1

        trees = []
        for i in range(len(forest)):
            for j in range(len(forest[0])):
                if forest[i][j] > 1:
                    trees.append((forest[i][j], i, j))
        trees.sort()

        sx, sy = 0, 0
        total_steps = 0
        for height, tx, ty in trees:
            steps = bfs(sx, sy, tx, ty)
            if steps == -1:
                return -1
            total_steps += steps
            sx, sy = tx, ty

        return total_steps