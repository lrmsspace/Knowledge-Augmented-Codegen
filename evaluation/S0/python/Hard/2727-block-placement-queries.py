# Source: https://leetcode.com/problems/block-placement-queries/   |   Difficulty: Hard
#
# Problem Description:
# There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.
#
# You are given a 2D array queries, which contains two types of queries:
#
#
# 	For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
# 	For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.
#
#
# Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.
#
# Example:
# Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]
#
# Output: [false,true,true]
#
# Explanation:
#
#
#
# For query 0, place an obstacle at x = 2. A block of size at most 2 can be placed before x = 3.
#
# Constraints:
# 1 <= queries.length <= 15 * 104
# 	2 <= queries[i].length <= 3
# 	1 <= queries[i][0] <= 2
# 	1 <= x, sz <= min(5 * 104, 3 * queries.length)
# 	The input is generated such that for queries of type 1, no obstacle exists at distance x when the query is asked.
# 	The input is generated such that there is at least one query of type 2.
#

class Solution(object):
    def getResults(self, queries):
        """
        :type queries: List[List[int]]
        :rtype: List[bool]
        """
        import bisect
        obstacles = []
        results = []
        
        for query in queries:
            if query[0] == 1:
                # Place an obstacle
                bisect.insort(obstacles, query[1])
            else:
                # Check if block can be placed
                x, sz = query[1], query[2]
                idx = bisect.bisect_right(obstacles, x)
                
                # Determine the leftmost position to place the block
                left_bound = 0
                if idx > 0:
                    left_bound = obstacles[idx - 1]
                
                if x - left_bound >= sz:
                    results.append(True)
                else:
                    results.append(False)
        
        return results