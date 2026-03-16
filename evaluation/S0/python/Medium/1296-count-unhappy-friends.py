# Source: https://leetcode.com/problems/count-unhappy-friends/   |   Difficulty: Medium
#
# Problem Description:
# You are given a list of preferences for n friends, where n is always even.
#
# For each person i, preferences[i] contains a list of friends sorted in the order of preference. In other words, a friend earlier in the list is more preferred than a friend later in the list. Friends in each list are denoted by integers from 0 to n-1.
#
# All the friends are divided into pairs. The pairings are given in a list pairs, where pairs[i] = [xi, yi] denotes xi is paired with yi and yi is paired with xi.
#
# However, this pairing may cause some of the friends to be unhappy. A friend x is unhappy if x is paired with y and there exists a friend u who is paired with v but:
#
#
# 	x prefers u over y, and
# 	u prefers x over v.
#
#
# Return the number of unhappy friends.
#
# Example:
# Input: n = 4, preferences = [[1, 2, 3], [3, 2, 0], [3, 1, 0], [1, 2, 0]], pairs = [[0, 1], [2, 3]]
# Output: 2
# Explanation:
# Friend 1 is unhappy because:
# - 1 is paired with 0 but prefers 3 over 0, and
# - 3 prefers 1 over 2.
# Friend 3 is unhappy because:
# - 3 is paired with 2 but prefers 1 over 2, and
# - 1 prefers 3 over 0.
# Friends 0 and 2 are happy.
#
# Constraints:
# 2 <= n <= 500
# 	n is even.
# 	preferences.length == n
# 	preferences[i].length == n - 1
# 	0 <= preferences[i][j] <= n - 1
# 	preferences[i] does not contain i.
# 	All values in preferences[i] are unique.
# 	pairs.length == n/2
# 	pairs[i].length == 2
# 	xi != yi
# 	0 <= xi, yi <= n - 1
# 	Each person is contained in exactly one pair.
#

class Solution(object):
    def unhappyFriends(self, n, preferences, pairs):
        """
        :type n: int
        :type preferences: List[List[int]]
        :type pairs: List[List[int]]
        :rtype: int
        """
        # Build a map to find each person's partner quickly
        partner = {}
        for x, y in pairs:
            partner[x] = y
            partner[y] = x

        # Build a rank map to find the preference order quickly
        rank = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n - 1):
                rank[i][preferences[i][j]] = j

        unhappy_count = 0

        # Check each person to see if they are unhappy
        for x in range(n):
            y = partner[x]
            # Check all friends that x prefers over y
            for u in preferences[x]:
                if u == y:
                    break  # Stop when we reach y in the preference list
                v = partner[u]
                # Check if u prefers x over v
                if rank[u][x] < rank[u][v]:
                    unhappy_count += 1
                    break  # No need to check further for this x

        return unhappy_count