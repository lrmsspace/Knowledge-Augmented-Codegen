# Source: https://leetcode.com/problems/number-of-operations-to-make-network-connected/   |   Difficulty: Medium
#
# Problem Description:
# There are n computers numbered from 0 to n - 1 connected by ethernet cables connections forming a network where connections[i] = [ai, bi] represents a connection between computers ai and bi. Any computer can reach any other computer directly or indirectly through the network.
#
# You are given an initial computer network connections. You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them directly connected.
#
# Return the minimum number of times you need to do this in order to make all the computers connected. If it is not possible, return -1.
#
# Example:
# Input: n = 4, connections = [[0,1],[0,2],[1,2]]
# Output: 1
# Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.
#
# Constraints:
# 1 <= n <= 105
# 	1 <= connections.length <= min(n * (n - 1) / 2, 105)
# 	connections[i].length == 2
# 	0 <= ai, bi < n
# 	ai != bi
# 	There are no repeated connections.
# 	No two computers are connected by more than one cable.
#

class Solution(object):
    def makeConnected(self, n, connections):
        """
        :type n: int
        :type connections: List[List[int]]
        :rtype: int
        """
        if len(connections) < n - 1:
            return -1

        parent = [i for i in range(n)]
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

        for a, b in connections:
            union(a, b)

        components = len(set(find(i) for i in range(n)))
        return components - 1