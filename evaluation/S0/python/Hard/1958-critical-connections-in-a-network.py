# Source: https://leetcode.com/problems/critical-connections-in-a-network/   |   Difficulty: Hard
#
# Problem Description:
# There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.
#
# A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
#
# Return all critical connections in the network in any order.
#
# Example:
# Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
# Output: [[1,3]]
# Explanation: [[3,1]] is also accepted.
#
# Constraints:
# 2 <= n <= 105
# 	n - 1 <= connections.length <= 105
# 	0 <= ai, bi <= n - 1
# 	ai != bi
# 	There are no repeated connections.
#

class Solution(object):
    def criticalConnections(self, n, connections):
        """
        :type n: int
        :type connections: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict

        graph = defaultdict(list)
        for u, v in connections:
            graph[u].append(v)
            graph[v].append(u)

        disc = [-1] * n
        low = [-1] * n
        time = [0]
        bridges = []

        def dfs(u, parent):
            disc[u] = low[u] = time[0]
            time[0] += 1

            for v in graph[u]:
                if disc[v] == -1:
                    dfs(v, u)
                    low[u] = min(low[u], low[v])
                    if low[v] > disc[u]:
                        bridges.append([u, v])
                elif v != parent:
                    low[u] = min(low[u], disc[v])

        for i in range(n):
            if disc[i] == -1:
                dfs(i, -1)

        return bridges