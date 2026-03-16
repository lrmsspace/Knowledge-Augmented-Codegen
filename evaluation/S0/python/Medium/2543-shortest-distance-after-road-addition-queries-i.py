# Source: https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n and a 2D integer array queries.
#
# There are n cities numbered from 0 to n - 1. Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.
#
# queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi. After each query, you need to find the length of the shortest path from city 0 to city n - 1.
#
# Return an array answer where for each i in the range [0, queries.length - 1], answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.
#
# Example:
# Input: n = 5, queries = [[2,4],[0,2],[0,4]]
#
# Output: [3,2,1]
#
# Explanation: 
#
#
#
# After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.
#
#
#
# After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.
#
#
#
# After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.
#
# Constraints:
# 3 <= n <= 500
# 	1 <= queries.length <= 500
# 	queries[i].length == 2
# 	0 <= queries[i][0] < queries[i][1] < n
# 	1 < queries[i][1] - queries[i][0]
# 	There are no repeated roads among the queries.
#

class Solution(object):
    def shortestDistanceAfterQueries(self, n, queries):
        """
        :type n: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        res = []
        dist = n - 1  # Initial distance from city 0 to city n-1
        for u, v in queries:
            # The new road can potentially shorten the path
            new_dist = u + 1 + (n - 1 - v)
            dist = min(dist, new_dist)
            res.append(dist)
        return res