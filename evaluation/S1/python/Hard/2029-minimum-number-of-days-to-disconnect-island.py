# Source: https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n binary grid grid where 1 represents land and 0 represents water. An island is a maximal 4-directionally (horizontal or vertical) connected group of 1's.
#
# The grid is said to be connected if we have exactly one island, otherwise is said disconnected.
#
# In one day, we are allowed to change any single land cell (1) into a water cell (0).
#
# Return the minimum number of days to disconnect the grid.
#
# Example:
# Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
#
# Output: 2
# Explanation: We need at least 2 days to get a disconnected grid.
# Change land grid[1][1] and grid[0][2] to water and get 2 disconnected island.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 30
# 	grid[i][j] is either 0 or 1.
#
# Helpful references (internal KB):
# - Breadth-first search (graph, array, bfs, counting)
#   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
#   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
#   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
#   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
# - Search for connected components in a graph (graph, dfs, bfs, enumeration)
#   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
#   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
#   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
#   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
#   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
# - Scheduling jobs on two machines (array, greedy)
#   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
#   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
#   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
#   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
#   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minDays(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        def count_islands(g):
            visited = [[False] * len(g[0]) for _ in range(len(g))]
            count = 0

            def bfs(start_x, start_y):
                queue = [(start_x, start_y)]
                visited[start_x][start_y] = True
                while queue:
                    x, y = queue.pop(0)
                    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                        nx, ny = x + dx, y + dy
                        if 0 <= nx < len(g) and 0 <= ny < len(g[0]) and not visited[nx][ny] and g[nx][ny] == 1:
                            visited[nx][ny] = True
                            queue.append((nx, ny))

            for i in range(len(g)):
                for j in range(len(g[0])):
                    if g[i][j] == 1 and not visited[i][j]:
                        bfs(i, j)
                        count += 1
            return count

        # Check initial number of islands
        if count_islands(grid) != 1:
            return 0

        # Try removing one land cell
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1:
                    grid[i][j] = 0
                    if count_islands(grid) != 1:
                        return 1
                    grid[i][j] = 1

        return 2