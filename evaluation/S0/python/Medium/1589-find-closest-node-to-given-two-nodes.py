# Source: https://leetcode.com/problems/find-closest-node-to-given-two-nodes/   |   Difficulty: Medium
#
# Problem Description:
# You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.
#
# The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from node i to node edges[i]. If there is no outgoing edge from i, then edges[i] == -1.
#
# You are also given two integers node1 and node2.
#
# Return the index of the node that can be reached from both node1 and node2, such that the maximum between the distance from node1 to that node, and from node2 to that node is minimized. If there are multiple answers, return the node with the smallest index, and if no possible answer exists, return -1.
#
# Note that edges may contain cycles.
#
# Example:
# Input: edges = [2,2,3,-1], node1 = 0, node2 = 1
# Output: 2
# Explanation: The distance from node 0 to node 2 is 1, and the distance from node 1 to node 2 is 1.
# The maximum of those two distances is 1. It can be proven that we cannot get a node with a smaller maximum distance than 1, so we return node 2.
#
# Constraints:
# n == edges.length
# 	2 <= n <= 105
# 	-1 <= edges[i] < n
# 	edges[i] != i
# 	0 <= node1, node2 < n
#

class Solution(object):
    def closestMeetingNode(self, edges, node1, node2):
        """
        :type edges: List[int]
        :type node1: int
        :type node2: int
        :rtype: int
        """
        def dfs(node, dist, distances):
            if node == -1 or distances[node] != -1:
                return
            distances[node] = dist
            dfs(edges[node], dist + 1, distances)

        n = len(edges)
        distances1 = [-1] * n
        distances2 = [-1] * n

        dfs(node1, 0, distances1)
        dfs(node2, 0, distances2)

        min_distance = float('inf')
        result_node = -1

        for i in range(n):
            if distances1[i] != -1 and distances2[i] != -1:
                max_dist = max(distances1[i], distances2[i])
                if max_dist < min_distance:
                    min_distance = max_dist
                    result_node = i

        return result_node