# Source: https://leetcode.com/problems/shortest-path-with-alternating-colors/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.
#
# You are given two arrays redEdges and blueEdges where:
#
#
# 	redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
# 	blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.
#
#
# Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
#
# Example:
# Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
# Output: [0,1,-1]
#
# Constraints:
# 1 <= n <= 100
# 	0 <= redEdges.length, blueEdges.length <= 400
# 	redEdges[i].length == blueEdges[j].length == 2
# 	0 <= ai, bi, uj, vj < n
#

class Solution(object):
    def shortestAlternatingPaths(self, n, redEdges, blueEdges):
        """
        :type n: int
        :type redEdges: List[List[int]]
        :type blueEdges: List[List[int]]
        :rtype: List[int]
        """
        from collections import deque, defaultdict

        graph = defaultdict(lambda: {'red': [], 'blue': []})
        for u, v in redEdges:
            graph[u]['red'].append(v)
        for u, v in blueEdges:
            graph[u]['blue'].append(v)

        result = [-1] * n
        result[0] = 0

        queue = deque([(0, 'red'), (0, 'blue')])
        visited = set((0, 'red'), (0, 'blue'))
        steps = 0

        while queue:
            size = len(queue)
            for _ in range(size):
                node, color = queue.popleft()
                next_color = 'blue' if color == 'red' else 'red'
                for neighbor in graph[node][next_color]:
                    if (neighbor, next_color) not in visited:
                        visited.add((neighbor, next_color))
                        queue.append((neighbor, next_color))
                        if result[neighbor] == -1:
                            result[neighbor] = steps + 1
            steps += 1

        return result