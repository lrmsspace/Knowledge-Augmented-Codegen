# Source: https://leetcode.com/problems/count-ways-to-build-rooms-in-an-ant-colony/   |   Difficulty: Hard
#
# Problem Description:
# You are an ant tasked with adding n new rooms numbered 0 to n-1 to your colony. You are given the expansion plan as a 0-indexed integer array of length n, prevRoom, where prevRoom[i] indicates that you must build room prevRoom[i] before building room i, and these two rooms must be connected directly. Room 0 is already built, so prevRoom[0] = -1. The expansion plan is given such that once all the rooms are built, every room will be reachable from room 0.
#
# You can only build one room at a time, and you can travel freely between rooms you have already built only if they are connected. You can choose to build any room as long as its previous room is already built.
#
# Return the number of different orders you can build all the rooms in. Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: prevRoom = [-1,0,1]
# Output: 1
# Explanation: There is only one way to build the additional rooms: 0 → 1 → 2
#
# Constraints:
# n == prevRoom.length
# 	2 <= n <= 105
# 	prevRoom[0] == -1
# 	0 <= prevRoom[i] < n for all 1 <= i < n
# 	Every room is reachable from room 0 once all the rooms are built.
#

class Solution(object):

    def waysToBuildRooms(self, prevRoom):

        """

        :type prevRoom: List[int]

        :rtype: int

        """
        MOD = 10**9 + 7
        n = len(prevRoom)

        # Precompute factorials and inverse factorials for combinations
        fact = [1] * (n + 1)
        inv_fact = [1] * (n + 1)
        for i in range(2, n + 1):
            fact[i] = fact[i - 1] * i % MOD
        inv_fact[n] = pow(fact[n], MOD - 2, MOD)
        for i in range(n - 1, 0, -1):
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD

        def comb(a, b):
            return fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD

        # Build the tree from prevRoom
        tree = [[] for _ in range(n)]
        for i in range(1, n):
            tree[prevRoom[i]].append(i)

        def dfs(node):
            total_ways = 1
            total_size = 0

            for child in tree[node]:
                child_ways, child_size = dfs(child)
                total_ways = total_ways * child_ways % MOD
                total_ways = total_ways * comb(total_size + child_size, child_size) % MOD
                total_size += child_size

            return total_ways, total_size + 1

        result, _ = dfs(0)
        return result