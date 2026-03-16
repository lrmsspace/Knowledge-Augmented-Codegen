# Source: https://leetcode.com/problems/time-taken-to-mark-all-nodes/   |   Difficulty: Hard
#
# Problem Description:
# There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
#
# Initially, all nodes are unmarked. For each node i:
#
#
# 	If i is odd, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 1.
# 	If i is even, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 2.
#
#
# Return an array times where times[i] is the time when all nodes get marked in the tree, if you mark node i at time t = 0.
#
# Note that the answer for each times[i] is independent, i.e. when you mark node i all other nodes are unmarked.
#
# Example:
# Input: edges = [[0,1],[0,2]]
#
# Output: [2,4,3]
#
# Explanation:
#
#
#
#
# 	For i = 0:
#
# 	
# 		Node 1 is marked at t = 1, and Node 2 at t = 2.
# 	
# 	
# 	For i = 1:
# 	
# 		Node 0 is marked at t = 2, and Node 2 at t = 4.
# 	
# 	
# 	For i = 2:
# 	
# 		Node 0 is marked at t = 2, and Node 1 at t = 3.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= edges[i][0], edges[i][1] <= n - 1
# 	The input is generated such that edges represents a valid tree.
#

class Solution(object):
    def timeTaken(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        n = len(edges) + 1
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        def bfs(start):
            times = [-1] * n
            times[start] = 0
            queue = deque([start])

            while queue:
                node = queue.popleft()
                for neighbor in graph[node]:
                    if times[neighbor] == -1:
                        if neighbor % 2 == 0:
                            times[neighbor] = times[node] + 2
                        else:
                            times[neighbor] = times[node] + 1
                        queue.append(neighbor)
            return max(times)

        result = []
        for i in range(n):
            result.append(bfs(i))

        return result