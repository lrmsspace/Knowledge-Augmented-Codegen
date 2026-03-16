# Source: https://leetcode.com/problems/modify-graph-edge-weights/   |   Difficulty: Hard
#
# Problem Description:
# You are given an undirected weighted connected graph containing n nodes labeled from 0 to n - 1, and an integer array edges where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.
#
# Some edges have a weight of -1 (wi = -1), while others have a positive weight (wi > 0).
#
# Your task is to modify all edges with a weight of -1 by assigning them positive integer values in the range [1, 2 * 109] so that the shortest distance between the nodes source and destination becomes equal to an integer target. If there are multiple modifications that make the shortest distance between source and destination equal to target, any of them will be considered correct.
#
# Return an array containing all edges (even unmodified ones) in any order if it is possible to make the shortest distance from source to destination equal to target, or an empty array if it's impossible.
#
# Note: You are not allowed to modify the weights of edges with initial positive weights.
#
# Example:
# Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
# Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
# Explanation: The graph above shows a possible modification to the edges, making the distance from 0 to 1 equal to 5.
#
# Constraints:
# 1 <= n <= 100
# 	1 <= edges.length <= n * (n - 1) / 2
# 	edges[i].length == 3
# 	0 <= ai, bi < n
# 	wi = -1 or 1 <= wi <= 107
# 	ai != bi
# 	0 <= source, destination < n
# 	source != destination
# 	1 <= target <= 109
# 	The graph is connected, and there are no self-loops or repeated edges
#
# Helpful references (internal KB):
# - Shortest Paths (array, graph, dp-1d)
#   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
#   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
#   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
#   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
#   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
# - Minimum-cost flow - Successive shortest path algorithm (graph, array, number, greedy, dijkstra, bellman-ford)
#   • When to use: When you need to find a flow of a certain amount (or maximum possible flow) through a network while minimizing the total cost associated with sending flow along edges. It is suitable for problems involving resource allocation with varying costs.
#   • Idea: The successive shortest path algorithm finds a minimum-cost flow by repeatedly finding a shortest augmenting path in the residual graph and pushing flow along it. Its complexity depends on the shortest path algorithm used (Bellman-Ford for general costs, Dijkstra with potentials for non-negative residual costs).
#   • Invariants: At the start of each iteration, the current flow is a valid flow from source to sink.; The residual graph correctly represents remaining capacities and reverse edges for the current flow.
#   • Tips: Use potentials (reduced costs) with Dijkstra to efficiently handle non-negative edge costs in the residual graph.; Initialize potentials to zero and update them after each shortest path computation.
#   • Pitfalls: Incorrectly updating residual capacities or reverse edge costs can lead to wrong results.; Failing to use potentials with Dijkstra can lead to incorrect shortest paths in graphs with negative edges.
# - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
#   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
#   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
#   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
#   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
#   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def modifiedGraphEdges(self, n, edges, source, destination, target):
        """
        :type n: int
        :type edges: List[List[int]]
        :type source: int
        :type destination: int
        :type target: int
        :rtype: List[List[int]]
        """
        import heapq
        from collections import defaultdict

        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))

        def dijkstra(start):
            dist = {i: float('inf') for i in range(n)}
            dist[start] = 0
            heap = [(0, start)]
            while heap:
                d, node = heapq.heappop(heap)
                if d > dist[node]:
                    continue
                for neighbor, weight in graph[node]:
                    new_dist = d + (weight if weight != -1 else 1)
                    if new_dist < dist[neighbor]:
                        dist[neighbor] = new_dist
                        heapq.heappush(heap, (new_dist, neighbor))
            return dist

        # Step 1: Calculate shortest path with all -1 treated as 1
        initial_dist = dijkstra(source)
        if initial_dist[destination] > target:
            return []
        
        # Step 2: Calculate shortest path with all -1 treated as 2*10^9
        for u, v, w in edges:
            if w == -1:
                graph[u] = [(nb, 2 * 10**9 if nb == v else w) for nb, w in graph[u]]
                graph[v] = [(nb, 2 * 10**9 if nb == u else w) for nb, w in graph[v]]
        
        max_dist = dijkstra(source)
        if max_dist[destination] < target:
            return []

        # Step 3: Binary search to find the correct weight for -1 edges
        low, high = 1, 2 * 10**9
        while low < high:
            mid = (low + high) // 2
            for u, v, w in edges:
                if w == -1:
                    graph[u] = [(nb, mid if nb == v else w) for nb, w in graph[u]]
                    graph[v] = [(nb, mid if nb == u else w) for nb, w in graph[v]]
            
            current_dist = dijkstra(source)
            if current_dist[destination] < target:
                low = mid + 1
            else:
                high = mid

        # Step 4: Update the edges with the found weight
        for i in range(len(edges)):
            u, v, w = edges[i]
            if w == -1:
                edges[i][2] = low
        return edges    