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
# Helpful references (internal KB):
# - Topological Sorting (graph, array, dfs, topo)
#   • When to use: Use for graph or tree traversal, pathfinding, cycle detection, or topological sorting in DAGs. It's also suitable for exploring all states in a search space.
#   • Idea: DFS explores as far as possible along each branch before backtracking, typically using recursion or an explicit stack. Topological sort orders nodes in a DAG such that for every directed edge u -> v, u comes before v, achievable with DFS in O(V+E) time.
#   • Invariants: All nodes reachable from the current path have been explored or are in the recursion stack.; A node is marked 'visited' only after all its descendants have been fully explored.
#   • Tips: Use a visited set/array to prevent infinite loops in graphs and redundant computations.; Recursion is natural for DFS, but an explicit stack can avoid recursion depth limits.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect results.; Exceeding recursion depth limits for very deep graphs or trees.
# - Directed Graphs (graph, stack, dfs, topo)
#   • When to use: Use when you need to traverse all reachable vertices in a directed graph, find specific vertex orderings, or determine a valid linear ordering of vertices based on dependencies. It's also used for cycle detection in directed graphs.
#   • Idea: Depth-First Search (DFS) explores as far as possible along each branch before backtracking. When applied to directed graphs, it can determine reachability, detect cycles, and compute topological orderings in O(V + E) time.
#   • Invariants: A vertex is marked visited only after all its descendants in the DFS tree have been fully explored.; If a back-edge is encountered (to a vertex currently in the recursion stack), a cycle is detected.
#   • Tips: Use a visited array/set to prevent infinite loops and redundant work.; Maintain a recursion stack or visiting array to detect cycles during DFS.
#   • Pitfalls: Forgetting to handle disconnected components in the graph.; Incorrectly implementing cycle detection, especially in directed graphs.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isPrintable(self, targetGrid):
        """
        :type targetGrid: List[List[int]]
        :rtype: bool
        """
        from collections import defaultdict, deque

        m, n = len(targetGrid), len(targetGrid[0])
        colors = set()
        color_bounds = defaultdict(lambda: [m, n, -1, -1])  # color: [min_row, min_col, max_row, max_col]

        # Step 1: Determine the bounding box for each color
        for i in range(m):
            for j in range(n):
                color = targetGrid[i][j]
                colors.add(color)
                bounds = color_bounds[color]
                bounds[0] = min(bounds[0], i)
                bounds[1] = min(bounds[1], j)
                bounds[2] = max(bounds[2], i)
                bounds[3] = max(bounds[3], j)

        # Step 2: Build the dependency graph
        graph = defaultdict(set)
        in_degree = defaultdict(int)

        for color in colors:
            min_row, min_col, max_row, max_col = color_bounds[color]
            for i in range(min_row, max_row + 1):
                for j in range(min_col, max_col + 1):
                    if targetGrid[i][j] != color:
                        if targetGrid[i][j] not in graph[color]:
                            graph[color].add(targetGrid[i][j])
                            in_degree[targetGrid[i][j]] += 1

        # Step 3: Topological sort using Kahn's algorithm
        zero_in_degree = deque([color for color in colors if in_degree[color] == 0])
        printed_colors = 0

        while zero_in_degree:
            current_color = zero_in_degree.popleft()
            printed_colors += 1
            for neighbor in graph[current_color]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    zero_in_degree.append(neighbor)

        return printed_colors == len(colors)
            