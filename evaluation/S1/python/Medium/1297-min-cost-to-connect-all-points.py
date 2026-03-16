# Source: https://leetcode.com/problems/min-cost-to-connect-all-points/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
#
# The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.
#
# Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.
#
# Example:
# Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
# Output: 20
# Explanation: 
#
# We can connect the points as shown above to get the minimum cost of 20.
# Notice that there is a unique path between every pair of points.
#
# Constraints:
# 1 <= points.length <= 1000
# 	-106 <= xi, yi <= 106
# 	All pairs (xi, yi) are distinct.
#
# Helpful references (internal KB):
# - Minimum spanning tree - Kruskal's algorithm (graph, array, mst-kruskal, union-find)
#   • When to use: Use when you need to find a minimum spanning tree in a graph, especially when the graph is sparse or when edge weights are the primary concern for selection.
#   • Idea: Kruskal's algorithm constructs a Minimum Spanning Tree by iteratively adding the lowest-weight edge that connects two previously disconnected components, avoiding cycles. It has a time complexity of O(E log E) or O(E log V) due to sorting edges and Union-Find operations.
#   • Invariants: The set of selected edges always forms a forest (no cycles).; Each component in the Union-Find structure represents a connected subtree of the potential MST.
#   • Tips: Always sort all edges by weight in non-decreasing order initially.; Use a Disjoint Set Union (Union-Find) data structure to efficiently track connected components and detect cycles.
#   • Pitfalls: Forgetting to sort edges or sorting them incorrectly (e.g., decreasing order for MST).; Not correctly implementing the Union-Find operations, leading to incorrect cycle detection or component merging.
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
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
    def minCostConnectPoints(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        import heapq

        n = len(points)
        min_e = [float('inf')] * n
        min_e[0] = 0
        used = [False] * n
        res = 0

        for _ in range(n):
            v = -1
            for u in range(n):
                if not used[u] and (v == -1 or min_e[u] < min_e[v]):
                    v = u

            used[v] = True
            res += min_e[v]

            for to in range(n):
                if not used[to]:
                    dist = abs(points[v][0] - points[to][0]) + abs(points[v][1] - points[to][1])
                    if dist < min_e[to]:
                        min_e[to] = dist

        return res