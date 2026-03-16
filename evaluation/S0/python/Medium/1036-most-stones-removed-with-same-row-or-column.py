# Source: https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/   |   Difficulty: Medium
#
# Problem Description:
# On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone.
#
# A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.
#
# Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, return the largest possible number of stones that can be removed.
#
# Example:
# Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
# Output: 5
# Explanation: One way to remove 5 stones is as follows:
# 1. Remove stone [2,2] because it shares the same row as [2,1].
# 2. Remove stone [2,1] because it shares the same column as [0,1].
# 3. Remove stone [1,2] because it shares the same row as [1,0].
# 4. Remove stone [1,0] because it shares the same column as [0,0].
# 5. Remove stone [0,1] because it shares the same row as [0,0].
# Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.
#
# Constraints:
# 1 <= stones.length <= 1000
# 	0 <= xi, yi <= 104
# 	No two stones are at the same coordinate point.
#

class Solution(object):
    def removeStones(self, stones):
        """
        :type stones: List[List[int]]
        :rtype: int
        """
        parent = {}
        
        def find(x):
            if parent.setdefault(x, x) != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            parent[find(x)] = find(y)
        
        for x, y in stones:
            union(x, ~y)
        
        return len(stones) - len({find(x) for x in parent})