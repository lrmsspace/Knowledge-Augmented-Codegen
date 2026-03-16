# Source: https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-i/   |   Difficulty: Medium
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
# 2 <= n <= 100
# 	1 <= x, y <= n
#
# Helpful references (internal KB):
# - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
#   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
#   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
#   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
#   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
#   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
# - Floyd-Warshall Algorithm (number, simulation)
#   • When to use: When you need to find the shortest paths between all possible pairs of vertices in a graph. It is particularly suitable for dense graphs or when negative edge weights are present, as long as no negative cycles are reachable.
#   • Idea: Floyd-Warshall is a dynamic programming algorithm that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path distances, achieving an O(V^3) time complexity.
#   • Invariants: After the k-th iteration, dist[i][j] contains the shortest path from i to j considering only vertices 0 to k-1 as intermediate nodes.; For any pair (i, j), dist[i][j] is always greater than or equal to the true shortest path distance from i to j (or infinity if unreachable).
#   • Tips: Initialize distances: direct edge weights, infinity for no direct edge, zero for self-loops.; The outermost loop must iterate through intermediate vertices (k).
#   • Pitfalls: Incorrect loop order (k not outermost) leads to incorrect results.; Integer overflow with large path sums if not using appropriate data types.
# - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, floyd-warshall)
#   • When to use: Use when finding the number or shortest length of paths between all pairs of vertices that consist of exactly a given number of edges. It's suitable for problems requiring path properties over a fixed number of steps.
#   • Idea: This technique extends matrix multiplication to find path properties (count or shortest length) of a fixed number of edges in a graph. It leverages binary exponentiation on an adjacency matrix with a modified 'min-plus' or 'sum-product' operation, achieving O(N^3 log K) complexity.
#   • Invariants: After k matrix multiplications, L_k[i][j] stores the shortest path length (or count) from i to j using exactly k edges.; The original adjacency matrix G remains unchanged throughout the exponentiation process.
#   • Tips: For shortest paths, initialize non-existent edges with infinity in the adjacency matrix.; For counting paths, initialize non-existent edges with zero in the adjacency matrix.
#   • Pitfalls: Incorrectly handling the identity matrix for base cases, especially for k=0 paths.; Off-by-one errors when defining the base matrix or the number of matrix multiplications.
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
        # Floyd-Warshall Algorithm
        dist = [[float('inf')] * n for _ in range(n)]
        
        for i in range(n):
            dist[i][i] = 0
            if i < n - 1:
                dist[i][i + 1] = 1
                dist[i + 1][i] = 1
        
        dist[x - 1][y - 1] = 1
        dist[y - 1][x - 1] = 1
        
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    if dist[i][j] > dist[i][k] + dist[k][j]:
                        dist[i][j] = dist[i][k] + dist[k][j]
        
        result = [0] * n
        for i in range(n):
            for j in range(i + 1, n):
                d = dist[i][j]
                if d <= n:
                    result[d - 1] += 2
        
        return result