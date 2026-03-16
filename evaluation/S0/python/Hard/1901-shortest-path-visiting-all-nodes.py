# Source: https://leetcode.com/problems/shortest-path-visiting-all-nodes/   |   Difficulty: Hard
#
# Problem Description:
# You have an undirected, connected graph of n nodes labeled from 0 to n - 1. You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.
#
# Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
#
# Example:
# Input: graph = [[1,2,3],[0],[0],[0]]
# Output: 4
# Explanation: One possible path is [1,0,2,0,3]
#
# Constraints:
# n == graph.length
# 	1 <= n <= 12
# 	0 <= graph[i].length < n
# 	graph[i] does not contain i.
# 	If graph[a] contains b, then graph[b] contains a.
# 	The input graph is always connected.
#

class Solution(object):
    def shortestPathLength(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: int
        """
        from collections import deque

        n = len(graph)
        final_state = (1 << n) - 1
        queue = deque()
        visited = set()

        for i in range(n):
            state = 1 << i
            queue.append((i, state, 0))
            visited.add((i, state))

        while queue:
            node, state, dist = queue.popleft()

            if state == final_state:
                return dist

            for neighbor in graph[node]:
                next_state = state | (1 << neighbor)
                if (neighbor, next_state) not in visited:
                    visited.add((neighbor, next_state))
                    queue.append((neighbor, next_state, dist + 1))

        return -1