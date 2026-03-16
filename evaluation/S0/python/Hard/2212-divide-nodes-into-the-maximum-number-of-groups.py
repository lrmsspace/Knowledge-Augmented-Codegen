# Source: https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/   |   Difficulty: Hard
#
# Problem Description:
# You are given a positive integer n representing the number of nodes in an undirected graph. The nodes are labeled from 1 to n.
#
# You are also given a 2D integer array edges, where edges[i] = [ai, bi] indicates that there is a bidirectional edge between nodes ai and bi. Notice that the given graph may be disconnected.
#
# Divide the nodes of the graph into m groups (1-indexed) such that:
#
#
# 	Each node in the graph belongs to exactly one group.
# 	For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to the group with index x, and bi belongs to the group with index y, then |y - x| = 1.
#
#
# Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes. Return -1 if it is impossible to group the nodes with the given conditions.
#
# Example:
# Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
# Output: 4
# Explanation: As shown in the image we:
# - Add node 5 to the first group.
# - Add node 1 to the second group.
# - Add nodes 2 and 4 to the third group.
# - Add nodes 3 and 6 to the fourth group.
# We can see that every edge is satisfied.
# It can be shown that that if we create a fifth group and move any node from the third or fourth group to it, at least on of the edges will not be satisfied.
#
# Constraints:
# 1 <= n <= 500
# 	1 <= edges.length <= 104
# 	edges[i].length == 2
# 	1 <= ai, bi <= n
# 	ai != bi
# 	There is at most one edge between any pair of vertices.
#

class Solution(object):
    def magnificentSets(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        visited = [False] * (n + 1)

        def bfs(start):
            queue = deque([(start, 1)])
            levels = {}
            levels[start] = 1
            max_level = 1

            while queue:
                node, level = queue.popleft()
                for neighbor in graph[node]:
                    if neighbor not in levels:
                        levels[neighbor] = level + 1
                        max_level = max(max_level, level + 1)
                        queue.append((neighbor, level + 1))
                    elif abs(levels[neighbor] - level) != 1:
                        return -1
            return max_level

        total_groups = 0
        for i in range(1, n + 1):
            if not visited[i]:
                component_max = bfs(i)
                if component_max == -1:
                    return -1
                total_groups += component_max
                for node in range(1, n + 1):
                    if node in graph and not visited[node]:
                        visited[node] = True

        return total_groups