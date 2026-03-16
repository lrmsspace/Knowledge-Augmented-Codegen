# Source: https://leetcode.com/problems/properties-graph/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array properties having dimensions n x m and an integer k.
#
# Define a function intersect(a, b) that returns the number of distinct integers common to both arrays a and b.
#
# Construct an undirected graph where each index i corresponds to properties[i]. There is an edge between node i and node j if and only if intersect(properties[i], properties[j]) >= k, where i and j are in the range [0, n - 1] and i != j.
#
# Return the number of connected components in the resulting graph.
#
# Example:
# Input: properties = [[1,2],[1,1],[3,4],[4,5],[5,6],[7,7]], k = 1
#
# Output: 3
#
# Explanation:
#
# The graph formed has 3 connected components:
#
# Constraints:
# 1 <= n == properties.length <= 100
# 	1 <= m == properties[i].length <= 100
# 	1 <= properties[i][j] <= 100
# 	1 <= k <= m
#

class Solution(object):
    def numberOfComponents(self, properties, k):
        """
        :type properties: List[List[int]]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict, deque

        n = len(properties)
        graph = defaultdict(list)

        # Build the graph
        for i in range(n):
            for j in range(i + 1, n):
                if len(set(properties[i]) & set(properties[j])) >= k:
                    graph[i].append(j)
                    graph[j].append(i)

        visited = [False] * n
        components = 0

        def bfs(start):
            queue = deque([start])
            visited[start] = True
            while queue:
                node = queue.popleft()
                for neighbor in graph[node]:
                    if not visited[neighbor]:
                        visited[neighbor] = True
                        queue.append(neighbor)

        # Count connected components
        for i in range(n):
            if not visited[i]:
                bfs(i)
                components += 1

        return components