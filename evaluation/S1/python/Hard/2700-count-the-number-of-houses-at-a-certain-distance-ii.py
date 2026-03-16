# Source: https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given three positive integers n, x, and y.
#
# In a city, there exist houses numbered 1 to n connected by n streets. There is a street connecting the house numbered i with the house numbered i + 1 for all 1 <= i <= n - 1 . An additional street connects the house numbered x with the house numbered y.
#
# For each k, such that 1 <= k <= n, you need to find the number of pairs of houses (house1, house2) such that the minimum number of streets that need to be traveled to reach house2 from house1 is k.
#
# Return a 1-indexed array result of length n where result[k] represents the total number of pairs of houses such that the minimum streets required to reach one house from the other is k.
#
# Note that x and y can be equal.
#
# Example:
# Input: n = 3, x = 1, y = 3
# Output: [6,0,0]
# Explanation: Let's look at each pair of houses:
# - For the pair (1, 2), we can go from house 1 to house 2 directly.
# - For the pair (2, 1), we can go from house 2 to house 1 directly.
# - For the pair (1, 3), we can go from house 1 to house 3 directly.
# - For the pair (3, 1), we can go from house 3 to house 1 directly.
# - For the pair (2, 3), we can go from house 2 to house 3 directly.
# - For the pair (3, 2), we can go from house 3 to house 2 directly.
#
# Constraints:
# 2 <= n <= 105
# 	1 <= x, y <= n
#
# Helpful references (internal KB):
# - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
#   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
#   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
#   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
#   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
#   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countOfPairs(self, n, x, y):
        """
        :type n: int
        :type x: int
        :type y: int
        :rtype: List[int]
        """
        from collections import defaultdict
        
        # Step 1: Build the graph
        graph = defaultdict(list)
        for i in range(1, n):
            graph[i].append(i + 1)
            graph[i + 1].append(i)
        graph[x].append(y)
        graph[y].append(x)

        # Step 2: BFS to find shortest paths
        def bfs(start):
            visited = [False] * (n + 1)
            distance = [0] * (n + 1)
            queue = [start]
            visited[start] = True
            
            while queue:
                node = queue.pop(0)
                for neighbor in graph[node]:
                    if not visited[neighbor]:
                        visited[neighbor] = True
                        distance[neighbor] = distance[node] + 1
                        queue.append(neighbor)
            return distance

        # Step 3: Count pairs by distance
        result = [0] * n
        for i in range(1, n + 1):
            dist = bfs(i)
            for j in range(1, n + 1):
                if i != j:
                    result[dist[j]] += 1

        # Each pair is counted twice (i, j) and (j, i), so divide by 2
        return [count // 2 for count in result]