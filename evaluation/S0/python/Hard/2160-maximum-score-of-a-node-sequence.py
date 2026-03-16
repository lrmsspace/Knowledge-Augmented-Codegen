# Source: https://leetcode.com/problems/maximum-score-of-a-node-sequence/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected graph with n nodes, numbered from 0 to n - 1.
#
# You are given a 0-indexed integer array scores of length n where scores[i] denotes the score of node i. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
#
# A node sequence is valid if it meets the following conditions:
#
#
# 	There is an edge connecting every pair of adjacent nodes in the sequence.
# 	No node appears more than once in the sequence.
#
#
# The score of a node sequence is defined as the sum of the scores of the nodes in the sequence.
#
# Return the maximum score of a valid node sequence with a length of 4. If no such sequence exists, return -1.
#
# Example:
# Input: scores = [5,2,9,8,4], edges = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
# Output: 24
# Explanation: The figure above shows the graph and the chosen node sequence [0,1,2,3].
# The score of the node sequence is 5 + 2 + 9 + 8 = 24.
# It can be shown that no other node sequence has a score of more than 24.
# Note that the sequences [3,1,2,0] and [1,0,2,3] are also valid and have a score of 24.
# The sequence [0,3,2,4] is not valid since no edge connects nodes 0 and 3.
#
# Constraints:
# n == scores.length
# 	4 <= n <= 5 * 104
# 	1 <= scores[i] <= 108
# 	0 <= edges.length <= 5 * 104
# 	edges[i].length == 2
# 	0 <= ai, bi <= n - 1
# 	ai != bi
# 	There are no duplicate edges.
#

class Solution(object):
    def maximumScore(self, scores, edges):
        """
        :type scores: List[int]
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict
        import heapq

        n = len(scores)
        graph = defaultdict(list)

        # Build the graph with top 3 neighbors for each node based on scores
        for u, v in edges:
            heapq.heappush(graph[u], (scores[v], v))
            if len(graph[u]) > 3:
                heapq.heappop(graph[u])
            heapq.heappush(graph[v], (scores[u], u))
            if len(graph[v]) > 3:
                heapq.heappop(graph[v])

        max_score = -1

        # Check all edges and calculate the maximum score of valid sequences
        for u, v in edges:
            u_neighbors = [node for score, node in graph[u] if node != v]
            v_neighbors = [node for score, node in graph[v] if node != u]

            for a in u_neighbors:
                for b in v_neighbors:
                    if a != b:
                        current_score = scores[u] + scores[v] + scores[a] + scores[b]
                        max_score = max(max_score, current_score)

        return max_score