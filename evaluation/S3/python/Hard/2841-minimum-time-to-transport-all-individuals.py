# Source: https://leetcode.com/problems/minimum-time-to-transport-all-individuals/   |   Difficulty: Hard
#
# Problem Description:
# You are given n individuals at a base camp who need to cross a river to reach a destination using a single boat. The boat can carry at most k people at a time. The trip is affected by environmental conditions that vary cyclically over m stages.
#
# Each stage j has a speed multiplier mul[j]:
#
#
# 	If mul[j] > 1, the trip slows down.
# 	If mul[j] < 1, the trip speeds up.
#
#
# Each individual i has a rowing strength represented by time[i], the time (in minutes) it takes them to cross alone in neutral conditions.
#
# Rules:
#
#
# 	A group g departing at stage j takes time equal to the maximum time[i] among its members, multiplied by mul[j] minutes to reach the destination.
# 	After the group crosses the river in time d, the stage advances by floor(d) % m steps.
# 	If individuals are left behind, one person must return with the boat. Let r be the index of the returning person, the return takes time[r] × mul[current_stage], defined as return_time, and the stage advances by floor(return_time) % m.
#
#
# Return the minimum total time required to transport all individuals. If it is not possible to transport all individuals to the destination, return -1.
#
# Example:
# Input: n = 1, k = 1, m = 2, time = [5], mul = [1.0,1.3]
#
# Output: 5.00000
#
# Explanation:
#
#
# 	Individual 0 departs from stage 0, so crossing time = 5 × 1.00 = 5.00 minutes.
# 	All team members are now at the destination. Thus, the total time taken is 5.00 minutes.
#
# Constraints:
# 1 <= n == time.length <= 12
# 	1 <= k <= 5
# 	1 <= m <= 5
# 	1 <= time[i] <= 100
# 	m == mul.length
# 	0.5 <= mul[i] <= 2.0
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
# - Floyd-Warshall Algorithm (graph, matrix, floyd-warshall, dp-2d)
#   • When to use: Use when needing to find the shortest paths between all pairs of vertices in a weighted graph, especially if negative edge weights are present but no negative cycles.
#   • Idea: The Floyd-Warshall algorithm is a dynamic programming approach that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path lengths, achieving an O(N^3) time complexity.
#   • Invariants: After k iterations, d[i][j] stores the shortest path from i to j using only vertices {1, ..., k} as intermediate nodes.; d[i][j] always represents a valid path length or infinity, never an invalid negative value unless a negative cycle is detected.
#   • Tips: Initialize direct edge weights and infinity for non-existent edges.; Set distance from a vertex to itself to zero initially.
#   • Pitfalls: Incorrect loop order (k must be outermost) will yield incorrect results.; Improper handling of 'infinity' values can lead to overflow or incorrect comparisons.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minTime(self, n, k, m, time, mul):
        """
        :type n: int
        :type k: int
        :type m: int
        :type time: List[int]
        :type mul: List[float]
        :rtype: float
        """
        from math import floor
        from functools import lru_cache

        @lru_cache(None)
        def dfs(remaining, stage):
            if remaining == 0:
                return 0.0

            min_time = float('inf')
            for group in combinations(range(n), min(k, remaining)):
                max_time = max(time[i] for i in group)
                trip_time = max_time * mul[stage]
                next_stage = (stage + floor(trip_time)) % m
                return_time = time[group[0]] * mul[next_stage] if remaining > len(group) else 0
                next_stage = (next_stage + floor(return_time)) % m
                min_time = min(min_time, trip_time + return_time + dfs(remaining - len(group), next_stage))

            return min_time

        result = dfs(n, 0)
        return result if result != float('inf') else -1