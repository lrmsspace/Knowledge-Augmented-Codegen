# Source: https://leetcode.com/problems/shortest-path-in-a-weighted-tree/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n and an undirected, weighted tree rooted at node 1 with n nodes numbered from 1 to n. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an undirected edge from node ui to vi with weight wi.
#
# You are also given a 2D integer array queries of length q, where each queries[i] is either:
#
#
# 	[1, u, v, w'] – Update the weight of the edge between nodes u and v to w', where (u, v) is guaranteed to be an edge present in edges.
# 	[2, x] – Compute the shortest path distance from the root node 1 to node x.
#
#
# Return an integer array answer, where answer[i] is the shortest path distance from node 1 to x for the ith query of [2, x].
#
# Example:
# Input: n = 2, edges = [[1,2,7]], queries = [[2,2],[1,1,2,4],[2,2]]
#
# Output: [7,4]
#
# Explanation:
#
#
#
#
# 	Query [2,2]: The shortest path from root node 1 to node 2 is 7.
# 	Query [1,1,2,4]: The weight of edge (1,2) changes from 7 to 4.
# 	Query [2,2]: The shortest path from root node 1 to node 2 is 4.
#
# Constraints:
# 1 <= n <= 105
# 	edges.length == n - 1
# 	edges[i] == [ui, vi, wi]
# 	1 <= ui, vi <= n
# 	1 <= wi <= 104
# 	The input is generated such that edges represents a valid tree.
# 	1 <= queries.length == q <= 105
# 	queries[i].length == 2 or 4
# 	
# 		queries[i] == [1, u, v, w'] or,
# 		queries[i] == [2, x]
# 		1 <= u, v, x <= n
# 		(u, v) is always an edge from edges.
# 		1 <= w' <= 104
#

class Solution(object):
    def treeQueries(self, n, edges, queries):
        """
        :type n: int
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict
        import heapq

        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))

        def dijkstra(start):
            dist = {i: float('inf') for i in range(1, n + 1)}
            dist[start] = 0
            heap = [(0, start)]

            while heap:
                current_dist, node = heapq.heappop(heap)

                if current_dist > dist[node]:
                    continue

                for neighbor, weight in graph[node]:
                    distance = current_dist + weight
                    if distance < dist[neighbor]:
                        dist[neighbor] = distance
                        heapq.heappush(heap, (distance, neighbor))

            return dist

        dist_from_root = dijkstra(1)
        results = []

        for query in queries:
            if query[0] == 1:
                _, u, v, new_weight = query
                for i, (neighbor, weight) in enumerate(graph[u]):
                    if neighbor == v:
                        graph[u][i] = (v, new_weight)
                        break
                for i, (neighbor, weight) in enumerate(graph[v]):
                    if neighbor == u:
                        graph[v][i] = (u, new_weight)
                        break
                dist_from_root = dijkstra(1)
            else:
                _, x = query
                results.append(dist_from_root[x])

        return results