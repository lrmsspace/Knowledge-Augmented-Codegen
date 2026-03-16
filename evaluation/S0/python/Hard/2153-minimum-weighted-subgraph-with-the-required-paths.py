# Source: https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n denoting the number of nodes of a weighted directed graph. The nodes are numbered from 0 to n - 1.
#
# You are also given a 2D integer array edges where edges[i] = [fromi, toi, weighti] denotes that there exists a directed edge from fromi to toi with weight weighti.
#
# Lastly, you are given three distinct integers src1, src2, and dest denoting three distinct nodes of the graph.
#
# Return the minimum weight of a subgraph of the graph such that it is possible to reach dest from both src1 and src2 via a set of edges of this subgraph. In case such a subgraph does not exist, return -1.
#
# A subgraph is a graph whose vertices and edges are subsets of the original graph. The weight of a subgraph is the sum of weights of its constituent edges.
#
# Example:
# Input: n = 6, edges = [[0,2,2],[0,5,6],[1,0,3],[1,4,5],[2,1,1],[2,3,3],[2,3,4],[3,4,2],[4,5,1]], src1 = 0, src2 = 1, dest = 5
# Output: 9
# Explanation:
# The above figure represents the input graph.
# The blue edges represent one of the subgraphs that yield the optimal answer.
# Note that the subgraph [[1,0,3],[0,5,6]] also yields the optimal answer. It is not possible to get a subgraph with less weight satisfying all the constraints.
#
# Constraints:
# 3 <= n <= 105
# 	0 <= edges.length <= 105
# 	edges[i].length == 3
# 	0 <= fromi, toi, src1, src2, dest <= n - 1
# 	fromi != toi
# 	src1, src2, and dest are pairwise distinct.
# 	1 <= weight[i] <= 105
#

class Solution(object):
    def minimumWeight(self, n, edges, src1, src2, dest):
        """
        :type n: int
        :type edges: List[List[int]]
        :type src1: int
        :type src2: int
        :type dest: int
        :rtype: int
        """
        import heapq
        from collections import defaultdict

        graph = defaultdict(list)
        rev_graph = defaultdict(list)

        for u, v, w in edges:
            graph[u].append((v, w))
            rev_graph[v].append((u, w))

        def dijkstra(start, graph):
            dist = [float('inf')] * n
            dist[start] = 0
            heap = [(0, start)]

            while heap:
                curr_dist, u = heapq.heappop(heap)

                if curr_dist > dist[u]:
                    continue

                for v, w in graph[u]:
                    if dist[u] + w < dist[v]:
                        dist[v] = dist[u] + w
                        heapq.heappush(heap, (dist[v], v))

            return dist

        dist_from_src1 = dijkstra(src1, graph)
        dist_from_src2 = dijkstra(src2, graph)
        dist_to_dest = dijkstra(dest, rev_graph)

        min_weight = float('inf')
        for i in range(n):
            if dist_from_src1[i] != float('inf') and dist_from_src2[i] != float('inf') and dist_to_dest[i] != float('inf'):
                total_weight = dist_from_src1[i] + dist_from_src2[i] + dist_to_dest[i]
                min_weight = min(min_weight, total_weight)

        return min_weight if min_weight != float('inf') else -1