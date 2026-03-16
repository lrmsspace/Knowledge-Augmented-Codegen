# Source: https://leetcode.com/problems/network-delay-time/   |   Difficulty: Medium
#
# Problem Description:
# You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.
#
# We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.
#
# Example:
# Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
# Output: 2
#
# Constraints:
# 1 <= k <= n <= 100
# 	1 <= times.length <= 6000
# 	times[i].length == 3
# 	1 <= ui, vi <= n
# 	ui != vi
# 	0 <= wi <= 100
# 	All the pairs (ui, vi) are unique. (i.e., no multiple edges.)
#

class Solution(object):
    def networkDelayTime(self, times, n, k):
        """
        :type times: List[List[int]]
        :type n: int
        :type k: int
        :rtype: int
        """
        import heapq
        from collections import defaultdict

        graph = defaultdict(list)
        for u, v, w in times:
            graph[u].append((v, w))

        min_heap = [(0, k)]  # (time, node)
        dist = {}

        while min_heap:
            time, node = heapq.heappop(min_heap)
            if node in dist:
                continue
            dist[node] = time
            for neighbor, weight in graph[node]:
                if neighbor not in dist:
                    heapq.heappush(min_heap, (time + weight, neighbor))

        if len(dist) == n:
            return max(dist.values())
        return -1