# Source: https://leetcode.com/problems/minimum-time-to-visit-disappearing-nodes/   |   Difficulty: Medium
#
# Problem Description:
# There is an undirected graph of n nodes. You are given a 2D array edges, where edges[i] = [ui, vi, lengthi] describes an edge between node ui and node vi with a traversal time of lengthi units.
#
# Additionally, you are given an array disappear, where disappear[i] denotes the time when the node i disappears from the graph and you won't be able to visit it.
#
# Note that the graph might be disconnected and might contain multiple edges.
#
# Return the array answer, with answer[i] denoting the minimum units of time required to reach node i from node 0. If node i is unreachable from node 0 then answer[i] is -1.
#
# Example:
# Input: n = 3, edges = [[0,1,2],[1,2,1],[0,2,4]], disappear = [1,1,5]
#
# Output: [0,-1,4]
#
# Explanation:
#
#
#
# We are starting our journey from node 0, and our goal is to find the minimum time required to reach each node before it disappears.
#
#
# 	For node 0, we don't need any time as it is our starting point.
# 	For node 1, we need at least 2 units of time to traverse edges[0]. Unfortunately, it disappears at that moment, so we won't be able to visit it.
# 	For node 2, we need at least 4 units of time to traverse edges[2].
#
# Constraints:
# 1 <= n <= 5 * 104
# 	0 <= edges.length <= 105
# 	edges[i] == [ui, vi, lengthi]
# 	0 <= ui, vi <= n - 1
# 	1 <= lengthi <= 105
# 	disappear.length == n
# 	1 <= disappear[i] <= 105
#

class Solution(object):
    def minimumTime(self, n, edges, disappear):
        """
        :type n: int
        :type edges: List[List[int]]
        :type disappear: List[int]
        :rtype: List[int]
        """
        import heapq
        from collections import defaultdict

        graph = defaultdict(list)
        for u, v, length in edges:
            graph[u].append((v, length))
            graph[v].append((u, length))

        min_time = [float('inf')] * n
        min_time[0] = 0
        pq = [(0, 0)]  # (time, node)

        while pq:
            curr_time, node = heapq.heappop(pq)

            if curr_time > disappear[node]:
                continue

            for neighbor, length in graph[node]:
                new_time = curr_time + length
                if new_time < min_time[neighbor] and new_time <= disappear[neighbor]:
                    min_time[neighbor] = new_time
                    heapq.heappush(pq, (new_time, neighbor))

        return [time if time != float('inf') else -1 for time in min_time]