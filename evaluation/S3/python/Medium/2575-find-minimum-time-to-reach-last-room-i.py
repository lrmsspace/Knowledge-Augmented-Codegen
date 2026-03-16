# Source: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/   |   Difficulty: Medium
#
# Problem Description:
# There is a dungeon with n x m rooms arranged as a grid.
#
# You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds after which the room opens and can be moved to. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes exactly one second.
#
# Return the minimum time to reach the room (n - 1, m - 1).
#
# Two rooms are adjacent if they share a common wall, either horizontally or vertically.
#
# Example:
# Input: moveTime = [[0,4],[4,4]]
#
# Output: 6
#
# Explanation:
#
# The minimum time required is 6 seconds.
#
#
# 	At time t == 4, move from room (0, 0) to room (1, 0) in one second.
# 	At time t == 5, move from room (1, 0) to room (1, 1) in one second.
#
# Constraints:
# 2 <= n == moveTime.length <= 50
# 	2 <= m == moveTime[i].length <= 50
# 	0 <= moveTime[i][j] <= 109
#
# Helpful references (internal KB):
# - Dijkstra on sparse graphs (heap, dijkstra)
#   • When to use: When finding the shortest paths from a single source to all other nodes in a graph with non-negative edge weights, especially when the graph is sparse. It offers optimal time complexity for such scenarios.
#   • Idea: This algorithm finds the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights. By using a priority queue (like a Fibonacci heap), it achieves an optimal time complexity of O(E + V log V) for sparse graphs.
#   • Invariants: All vertices in the priority queue have a tentative distance from the source.; For any vertex already extracted from the priority queue, its distance is finalized and represents the shortest path.
#   • Tips: Use a priority queue (min-heap) to efficiently extract the minimum distance vertex.; Initialize distances to infinity and source distance to zero.
#   • Pitfalls: Does not work correctly with negative edge weights.; Incorrectly updating distances can lead to suboptimal paths.
# - Dijkstra on sparse graphs (heap, queue, dijkstra)
#   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
#   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
#   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
#   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
#   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
# - Minimum spanning tree - Prim's algorithm (graph, heap, array, mst-prim, greedy, heap-select)
#   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, weighted graph. It is efficient for both dense graphs (O(V^2)) and sparse graphs (O(E log V)) depending on the implementation.
#   • Idea: Prim's algorithm is a greedy algorithm that builds an MST by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside the tree. It has a time complexity of O(V^2) for dense graphs using an adjacency matrix or O(E log V) for sparse graphs using a priority queue.
#   • Invariants: All selected vertices and edges form a connected component of the final MST.; For any unselected vertex `v`, `min_e[v]` stores the minimum weight of an edge connecting `v` to the currently selected component.
#   • Tips: For dense graphs, an O(V^2) implementation using an an adjacency matrix and simple array scans is efficient.; For sparse graphs, use a priority queue (min-heap) with an adjacency list to achieve O(E log V) complexity.
#   • Pitfalls: Incorrectly updating the `min_e` array or priority queue entries can lead to an incorrect MST or performance issues.; Forgetting to mark vertices as 'selected' can lead to cycles or infinite loops.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minTimeToReach(self, moveTime):
        """
        :type moveTime: List[List[int]]
        :rtype: int
        """
        import heapq

        n, m = len(moveTime), len(moveTime[0])
        directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
        min_heap = [(0, 0, 0)]  # (time, x, y)
        visited = set()

        while min_heap:
            time, x, y = heapq.heappop(min_heap)

            if (x, y) in visited:
                continue
            visited.add((x, y))

            if (x, y) == (n - 1, m - 1):
                return time

            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < n and 0 <= ny < m and (nx, ny) not in visited:
                    next_time = max(time + 1, moveTime[nx][ny])
                    heapq.heappush(min_heap, (next_time, nx, ny))

        return -1  # In case there is no valid path