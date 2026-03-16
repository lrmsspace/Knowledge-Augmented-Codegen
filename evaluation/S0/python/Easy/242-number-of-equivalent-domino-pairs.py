# Source: https://leetcode.com/problems/number-of-equivalent-domino-pairs/   |   Difficulty: Easy
#
# Problem Description:
# Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a == c and b == d), or (a == d and b == c) - that is, one domino can be rotated to be equal to another domino.
#
# Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].
#
# Example:
# Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
# Output: 1
#
# Constraints:
# 1 <= dominoes.length <= 4 * 104
# 	dominoes[i].length == 2
# 	1 <= dominoes[i][j] <= 9
#

class Solution(object):
    def numEquivDominoPairs(self, dominoes):
        """
        :type dominoes: List[List[int]]
        :rtype: int
        """
        count = {}
        for a, b in dominoes:
            key = (min(a, b), max(a, b))
            count[key] = count.get(key, 0) + 1
        
        result = 0
        for k in count:
            n = count[k]
            result += n * (n - 1) // 2
        
        return result