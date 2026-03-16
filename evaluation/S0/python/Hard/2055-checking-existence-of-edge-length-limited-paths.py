# Source: https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/   |   Difficulty: Hard
#
# Problem Description:
# An undirected graph of n nodes is defined by edgeList, where edgeList[i] = [ui, vi, disi] denotes an edge between nodes ui and vi with distance disi. Note that there may be multiple edges between two nodes.
#
# Given an array queries, where queries[j] = [pj, qj, limitj], your task is to determine for each queries[j] whether there is a path between pj and qj such that each edge on the path has a distance strictly less than limitj .
#
# Return a boolean array answer, where answer.length == queries.length and the jth value of answer is true if there is a path for queries[j] is true, and false otherwise.
#
# Example:
# Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
# Output: [false,true]
# Explanation: The above figure shows the given graph. Note that there are two overlapping edges between 0 and 1 with distances 2 and 16.
# For the first query, between 0 and 1 there is no path where each distance is less than 2, thus we return false for this query.
# For the second query, there is a path (0 -> 1 -> 2) of two edges with distances less than 5, thus we return true for this query.
#
# Constraints:
# 2 <= n <= 105
# 	1 <= edgeList.length, queries.length <= 105
# 	edgeList[i].length == 3
# 	queries[j].length == 3
# 	0 <= ui, vi, pj, qj <= n - 1
# 	ui != vi
# 	pj != qj
# 	1 <= disi, limitj <= 109
# 	There may be multiple edges between two nodes.
#

class Solution(object):
    def distanceLimitedPathsExist(self, n, edgeList, queries):
        """
        :type n: int
        :type edgeList: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[bool]
        """
        parent = list(range(n))
        rank = [1] * n

        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                if rank[rootX] > rank[rootY]:
                    parent[rootY] = rootX
                elif rank[rootX] < rank[rootY]:
                    parent[rootX] = rootY
                else:
                    parent[rootY] = rootX
                    rank[rootX] += 1

        edgeList.sort(key=lambda x: x[2])
        queries = sorted(enumerate(queries), key=lambda x: x[1][2])
        res = [False] * len(queries)
        edgeIndex = 0

        for i, (p, q, limit) in queries:
            while edgeIndex < len(edgeList) and edgeList[edgeIndex][2] < limit:
                u, v, _ = edgeList[edgeIndex]
                union(u, v)
                edgeIndex += 1
            if find(p) == find(q):
                res[i] = True

        return res