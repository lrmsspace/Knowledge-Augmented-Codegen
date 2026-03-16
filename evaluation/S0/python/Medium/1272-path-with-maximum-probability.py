# Source: https://leetcode.com/problems/path-with-maximum-probability/   |   Difficulty: Medium
#
# Problem Description:
# You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success of traversing that edge succProb[i].
#
# Given two nodes start and end, find the path with the maximum probability of success to go from start to end and return its success probability.
#
# If there is no path from start to end, return 0. Your answer will be accepted if it differs from the correct answer by at most 1e-5.
#
# Example:
# Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
# Output: 0.25000
# Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.
#
# Constraints:
# 2 <= n <= 10^4
# 	0 <= start, end < n
# 	start != end
# 	0 <= a, b < n
# 	a != b
# 	0 <= succProb.length == edges.length <= 2*10^4
# 	0 <= succProb[i] <= 1
# 	There is at most one edge between every two nodes.
#

class Solution(object):
    def maxProbability(self, n, edges, succProb, start_node, end_node):
        """
        :type n: int
        :type edges: List[List[int]]
        :type succProb: List[float]
        :type start_node: int
        :type end_node: int
        :rtype: float
        """
        import heapq
        from collections import defaultdict

        graph = defaultdict(list)
        for (a, b), prob in zip(edges, succProb):
            graph[a].append((b, prob))
            graph[b].append((a, prob))

        max_heap = [(-1.0, start_node)]
        probabilities = [0.0] * n
        probabilities[start_node] = 1.0

        while max_heap:
            curr_prob, node = heapq.heappop(max_heap)
            curr_prob = -curr_prob

            if node == end_node:
                return curr_prob

            for neighbor, edge_prob in graph[node]:
                new_prob = curr_prob * edge_prob
                if new_prob > probabilities[neighbor]:
                    probabilities[neighbor] = new_prob
                    heapq.heappush(max_heap, (-new_prob, neighbor))

        return 0.0