# Source: https://leetcode.com/problems/count-pairs-of-connectable-servers-in-a-weighted-tree-network/   |   Difficulty: Medium
#
# Problem Description:
# You are given an unrooted weighted tree with n vertices representing servers numbered from 0 to n - 1, an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional edge between vertices ai and bi of weight weighti. You are also given an integer signalSpeed.
#
# Two servers a and b are connectable through a server c if:
#
#
# 	a < b, a != c and b != c.
# 	The distance from c to a is divisible by signalSpeed.
# 	The distance from c to b is divisible by signalSpeed.
# 	The path from c to b and the path from c to a do not share any edges.
#
#
# Return an integer array count of length n where count[i] is the number of server pairs that are connectable through the server i.
#
# Example:
# Input: edges = [[0,1,1],[1,2,5],[2,3,13],[3,4,9],[4,5,2]], signalSpeed = 1
# Output: [0,4,6,6,4,0]
# Explanation: Since signalSpeed is 1, count[c] is equal to the number of pairs of paths that start at c and do not share any edges.
# In the case of the given path graph, count[c] is equal to the number of servers to the left of c multiplied by the servers to the right of c.
#
# Constraints:
# 2 <= n <= 1000
# 	edges.length == n - 1
# 	edges[i].length == 3
# 	0 <= ai, bi < n
# 	edges[i] = [ai, bi, weighti]
# 	1 <= weighti <= 106
# 	1 <= signalSpeed <= 106
# 	The input is generated such that edges represents a valid tree.
#

class Solution(object):
    def countPairsOfConnectableServers(self, edges, signalSpeed):
        """
        :type edges: List[List[int]]
        :type signalSpeed: int
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        n = len(edges) + 1
        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))

        def bfs(start):
            dist = [-1] * n
            dist[start] = 0
            queue = deque([start])
            while queue:
                node = queue.popleft()
                for neighbor, weight in graph[node]:
                    if dist[neighbor] == -1:
                        dist[neighbor] = dist[node] + weight
                        queue.append(neighbor)
            return dist

        result = [0] * n
        for c in range(n):
            dist = bfs(c)
            count_mod = defaultdict(int)
            for server in range(n):
                if server != c:
                    mod_dist = dist[server] % signalSpeed
                    count_mod[mod_dist] += 1

            for count in count_mod.values():
                result[c] += count * (count - 1) // 2

        return result