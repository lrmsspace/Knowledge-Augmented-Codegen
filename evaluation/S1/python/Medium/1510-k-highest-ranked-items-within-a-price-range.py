# Source: https://leetcode.com/problems/k-highest-ranked-items-within-a-price-range/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed 2D integer array grid of size m x n that represents a map of the items in a shop. The integers in the grid represent the following:
#
#
# 	0 represents a wall that you cannot pass through.
# 	1 represents an empty cell that you can freely move to and from.
# 	All other positive integers represent the price of an item in that cell. You may also freely move to and from these item cells.
#
#
# It takes 1 step to travel between adjacent grid cells.
#
# You are also given integer arrays pricing and start where pricing = [low, high] and start = [row, col] indicates that you start at the position (row, col) and are interested only in items with a price in the range of [low, high] (inclusive). You are further given an integer k.
#
# You are interested in the positions of the k highest-ranked items whose prices are within the given price range. The rank is determined by the first of these criteria that is different:
#
#
# 	Distance, defined as the length of the shortest path from the start (shorter distance has a higher rank).
# 	Price (lower price has a higher rank, but it must be in the price range).
# 	The row number (smaller row number has a higher rank).
# 	The column number (smaller column number has a higher rank).
#
#
# Return the k highest-ranked items within the price range sorted by their rank (highest to lowest). If there are fewer than k reachable items within the price range, return all of them.
#
# Example:
# Input: grid = [[1,2,0,1],[1,3,0,1],[0,2,5,1]], pricing = [2,5], start = [0,0], k = 3
# Output: [[0,1],[1,1],[2,1]]
# Explanation: You start at (0,0).
# With a price range of [2,5], we can take items from (0,1), (1,1), (2,1) and (2,2).
# The ranks of these items are:
# - (0,1) with distance 1
# - (1,1) with distance 2
# - (2,1) with distance 3
# - (2,2) with distance 4
# Thus, the 3 highest ranked items in the price range are (0,1), (1,1), and (2,1).
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 105
# 	1 <= m * n <= 105
# 	0 <= grid[i][j] <= 105
# 	pricing.length == 2
# 	2 <= low <= high <= 105
# 	start.length == 2
# 	0 <= row <= m - 1
# 	0 <= col <= n - 1
# 	grid[row][col] > 0
# 	1 <= k <= m * n
#
# Helpful references (internal KB):
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
#   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Priority Queues (heap, stack, heap-select)
#   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
#   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
#   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
#   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
#   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def highestRankedKItems(self, grid, pricing, start, k):
        """
        :type grid: List[List[int]]
        :type pricing: List[int]
        :type start: List[int]
        :type k: int
        :rtype: List[List[int]]
        """
        from collections import deque
        import heapq

        m, n = len(grid), len(grid[0])
        low, high = pricing
        start_row, start_col = start

        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        visited = [[False] * n for _ in range(m)]
        visited[start_row][start_col] = True

        queue = deque([(start_row, start_col, 0)])  # (row, col, distance)
        items = []

        while queue:
            row, col, dist = queue.popleft()

            if low <= grid[row][col] <= high:
                items.append((dist, grid[row][col], row, col))

            for dr, dc in directions:
                new_row, new_col = row + dr, col + dc
                if 0 <= new_row < m and 0 <= new_col < n and not visited[new_row][new_col] and grid[new_row][new_col] != 0:
                    visited[new_row][new_col] = True
                    queue.append((new_row, new_col, dist + 1))

        # Sort items based on the defined criteria
        items.sort()

        # Extract the top k items' positions
        result = [[row, col] for _, _, row, col in items[:k]]

        return result