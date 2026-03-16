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
        import collections

        graph = collections.defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))

        def dijkstra(modified):
            dist = [float('inf')] * n
            dist[source] = 0
            heap = [(0, source)]

            while heap:
                d, node = heapq.heappop(heap)
                if d > dist[node]:
                    continue
                for neighbor, weight in graph[node]:
                    w = modified.get((node, neighbor), weight)
                    if w == -1:
                        w = 1
                    if dist[node] + w < dist[neighbor]:
                        dist[neighbor] = dist[node] + w
                        heapq.heappush(heap, (dist[neighbor], neighbor))
            return dist[destination]

        modified = {}
        low, high = 1, 2 * 10**9

        while low <= high:
            mid = (low + high) // 2
            modified.clear()
            for u, v, w in edges:
                if w == -1:
                    modified[(u, v)] = mid
                    modified[(v, u)] = mid
            shortest_path = dijkstra(modified)
            if shortest_path < target:
                low = mid + 1
            elif shortest_path > target:
                high = mid - 1
            else:
                break

        if dijkstra(modified) != target:
            return []

        result = []
        for u, v, w in edges:
            if w == -1:
                w = modified[(u, v)]
            result.append([u, v, w])
        return result