# Source: https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D integer array edges representing an undirected graph having n nodes, where edges[i] = [ui, vi] denotes an edge between nodes ui and vi.
#
# Construct a 2D grid that satisfies these conditions:
#
#
# 	The grid contains all nodes from 0 to n - 1 in its cells, with each node appearing exactly once.
# 	Two nodes should be in adjacent grid cells (horizontally or vertically) if and only if there is an edge between them in edges.
#
#
# It is guaranteed that edges can form a 2D grid that satisfies the conditions.
#
# Return a 2D integer array satisfying the conditions above. If there are multiple solutions, return any of them.
#
# Example:
# Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]]
#
# Output: [[3,1],[2,0]]
#
# Explanation:
#
# Constraints:
# 2 <= n <= 5 * 104
# 	1 <= edges.length <= 105
# 	edges[i] = [ui, vi]
# 	0 <= ui < vi < n
# 	All the edges are distinct.
# 	The input is generated such that edges can form a 2D grid that satisfies the conditions.
#

class Solution(object):
    def constructGridLayout(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        # Find grid dimensions
        rows, cols = 0, 0
        for i in range(n):
            deg = len(graph[i])
            if deg > cols:
                cols = deg
        rows = n // cols

        grid = [[-1] * cols for _ in range(rows)]
        visited = [False] * n

        def bfs(start):
            queue = deque([start])
            visited[start] = True
            r, c = 0, 0
            while queue:
                node = queue.popleft()
                grid[r][c] = node
                c += 1
                if c == cols:
                    c = 0
                    r += 1
                for neighbor in graph[node]:
                    if not visited[neighbor]:
                        visited[neighbor] = True
                        queue.append(neighbor)

        bfs(0)
        return grid