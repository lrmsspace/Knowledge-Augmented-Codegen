# Source: https://leetcode.com/problems/find-the-number-of-copy-arrays/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array original of length n and a 2D array bounds of length n x 2, where bounds[i] = [ui, vi].
#
# You need to find the number of possible arrays copy of length n such that:
#
#
# 	(copy[i] - copy[i - 1]) == (original[i] - original[i - 1]) for 1 <= i <= n - 1.
# 	ui <= copy[i] <= vi for 0 <= i <= n - 1.
#
#
# Return the number of such arrays.
#
# Example:
# Input: original = [1,2,3,4], bounds = [[1,2],[2,3],[3,4],[4,5]]
#
# Output: 2
#
# Explanation:
#
# The possible arrays are:
#
#
# 	[1, 2, 3, 4]
# 	[2, 3, 4, 5]
#
# Constraints:
# 2 <= n == original.length <= 105
# 	1 <= original[i] <= 109
# 	bounds.length == n
# 	bounds[i].length == 2
# 	1 <= bounds[i][0] <= bounds[i][1] <= 109
#

class Solution(object):
    def countArrays(self, original, bounds):
        """
        :type original: List[int]
        :type bounds: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(original)
        
        diff = [original[i] - original[i-1] for i in range(1, n)]
        
        min_first = bounds[0][0]
        max_first = bounds[0][1]
        
        for i in range(1, n):
            d = diff[i-1]
            min_first = max(min_first, bounds[i][0] - sum(diff[:i]))
            max_first = min(max_first, bounds[i][1] - sum(diff[:i]))
            if min_first > max_first:
                return 0
        
        return (max_first - min_first + 1) % MOD