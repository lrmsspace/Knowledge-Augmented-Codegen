# Source: https://leetcode.com/problems/maximum-sum-of-edge-values-in-a-graph/   |   Difficulty: Hard
#
# Problem Description:
# You are given an undirected connected graph of n nodes, numbered from 0 to n - 1. Each node is connected to at most 2 other nodes.
#
# The graph consists of m edges, represented by a 2D array edges, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi.
#
# You have to assign a unique value from 1 to n to each node. The value of an edge will be the product of the values assigned to the two nodes it connects.
#
# Your score is the sum of the values of all edges in the graph.
#
# Return the maximum score you can achieve.
#
# Example:
# Input: n = 4, edges = [[0,1],[1,2],[2,3]]
#
# Output: 23
#
# Explanation:
#
# The diagram above illustrates an optimal assignment of values to nodes. The sum of the values of the edges is: (1 * 3) + (3 * 4) + (4 * 2) = 23.
#
# Constraints:
# 1 <= n <= 5 * 104
# 	m == edges.length
# 	1 <= m <= n
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	ai != bi
# 	There are no repeated edges.
# 	The graph is connected.
# 	Each node is connected to at most 2 other nodes.
#

class Solution(object):
    def maxScore(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        degree = [0] * n

        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
            degree[u] += 1
            degree[v] += 1

        visited = [False] * n
        values = list(range(n, 0, -1))
        value_index = 0
        total_score = 0

        for i in range(n):
            if not visited[i]:
                component_nodes = []
                queue = deque([i])
                visited[i] = True

                while queue:
                    node = queue.popleft()
                    component_nodes.append(node)

                    for neighbor in graph[node]:
                        if not visited[neighbor]:
                            visited[neighbor] = True
                            queue.append(neighbor)

                component_nodes.sort(key=lambda x: degree[x], reverse=True)

                for node in component_nodes:
                    assigned_value = values[value_index]
                    value_index += 1

                    for neighbor in graph[node]:
                        if neighbor in component_nodes:
                            total_score += assigned_value * values[value_index - 1]

        return total_score