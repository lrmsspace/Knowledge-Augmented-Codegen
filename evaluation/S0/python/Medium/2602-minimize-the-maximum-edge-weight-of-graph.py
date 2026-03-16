# Source: https://leetcode.com/problems/minimize-the-maximum-edge-weight-of-graph/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers, n and threshold, as well as a directed weighted graph of n nodes numbered from 0 to n - 1. The graph is represented by a 2D integer array edges, where edges[i] = [Ai, Bi, Wi] indicates that there is an edge going from node Ai to node Bi with weight Wi.
#
# You have to remove some edges from this graph (possibly none), so that it satisfies the following conditions:
#
#
# 	Node 0 must be reachable from all other nodes.
# 	The maximum edge weight in the resulting graph is minimized.
# 	Each node has at most threshold outgoing edges.
#
#
# Return the minimum possible value of the maximum edge weight after removing the necessary edges. If it is impossible for all conditions to be satisfied, return -1.
#
# Example:
# Input: n = 5, edges = [[1,0,1],[2,0,2],[3,0,1],[4,3,1],[2,1,1]], threshold = 2
#
# Output: 1
#
# Explanation:
#
#
#
# Remove the edge 2 -> 0. The maximum weight among the remaining edges is 1.
#
# Constraints:
# 2 <= n <= 105
# 	1 <= threshold <= n - 1
# 	1 <= edges.length <= min(105, n * (n - 1) / 2).
# 	edges[i].length == 3
# 	0 <= Ai, Bi < n
# 	Ai != Bi
# 	1 <= Wi <= 106
# 	There may be multiple edges between a pair of nodes, but they must have unique weights.
#

class Solution(object):
    def minMaxWeight(self, n, edges, threshold):
        """
        :type n: int
        :type edges: List[List[int]]
        :type threshold: int
        :rtype: int
        """
        from collections import defaultdict, deque
        import heapq

        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))

        def canReachAll(maxWeight):
            outDegree = [0] * n
            visited = [False] * n
            queue = deque([0])
            visited[0] = True

            while queue:
                node = queue.popleft()
                neighbors = [(v, w) for v, w in graph[node] if w <= maxWeight]
                neighbors.sort(key=lambda x: x[1])

                for v, w in neighbors[:threshold]:
                    outDegree[node] += 1
                    if not visited[v]:
                        visited[v] = True
                        queue.append(v)

            return all(visited)

        left, right = 1, max(w for _, _, w in edges)
        result = -1

        while left <= right:
            mid = (left + right) // 2
            if canReachAll(mid):
                result = mid
                right = mid - 1
            else:
                left = mid + 1

        return result