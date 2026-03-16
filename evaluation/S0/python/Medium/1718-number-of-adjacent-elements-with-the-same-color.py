# Source: https://leetcode.com/problems/number-of-adjacent-elements-with-the-same-color/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n representing an array colors of length n where all elements are set to 0's meaning uncolored. You are also given a 2D integer array queries where queries[i] = [indexi, colori]. For the ith query:
#
#
# 	Set colors[indexi] to colori.
# 	Count the number of adjacent pairs in colors which have the same color (regardless of colori).
#
#
# Return an array answer of the same length as queries where answer[i] is the answer to the ith query.
#
# Example:
# Input: n = 4, queries = [[0,2],[1,2],[3,1],[1,1],[2,1]]
#
# Output: [0,1,1,0,2]
#
# Explanation:
#
#
# 	Initially array colors = [0,0,0,0], where 0 denotes uncolored elements of the array.
# 	After the 1st query colors = [2,0,0,0]. The count of adjacent pairs with the same color is 0.
# 	After the 2nd query colors = [2,2,0,0]. The count of adjacent pairs with the same color is 1.
# 	After the 3rd query colors = [2,2,0,1]. The count of adjacent pairs with the same color is 1.
# 	After the 4th query colors = [2,1,0,1]. The count of adjacent pairs with the same color is 0.
# 	After the 5th query colors = [2,1,1,1]. The count of adjacent pairs with the same color is 2.
#
# Constraints:
# 1 <= n <= 105
# 	1 <= queries.length <= 105
# 	queries[i].length == 2
# 	0 <= indexi <= n - 1
# 	1 <=  colori <= 105
#

class Solution(object):
    def colorTheArray(self, n, queries):
        """
        :type n: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        colors = [0] * n
        result = []
        adjacent_count = 0

        for index, color in queries:
            # Check left neighbor
            if index > 0:
                if colors[index] != 0 and colors[index] == colors[index - 1]:
                    adjacent_count -= 1
                if color == colors[index - 1]:
                    adjacent_count += 1

            # Check right neighbor
            if index < n - 1:
                if colors[index] != 0 and colors[index] == colors[index + 1]:
                    adjacent_count -= 1
                if color == colors[index + 1]:
                    adjacent_count += 1

            colors[index] = color
            result.append(adjacent_count)

        return result