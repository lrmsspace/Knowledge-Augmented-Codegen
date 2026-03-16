# Source: https://leetcode.com/problems/find-a-good-subset-of-the-matrix/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed m x n binary matrix grid.
#
# Let us call a non-empty subset of rows good if the sum of each column of the subset is at most half of the length of the subset.
#
# More formally, if the length of the chosen subset of rows is k, then the sum of each column should be at most floor(k / 2).
#
# Return an integer array that contains row indices of a good subset sorted in ascending order.
#
# If there are multiple good subsets, you can return any of them. If there are no good subsets, return an empty array.
#
# A subset of rows of the matrix grid is any matrix that can be obtained by deleting some (possibly none or all) rows from grid.
#
# Example:
# Input: grid = [[0,1,1,0],[0,0,0,1],[1,1,1,1]]
# Output: [0,1]
# Explanation: We can choose the 0th and 1st rows to create a good subset of rows.
# The length of the chosen subset is 2.
# - The sum of the 0th column is 0 + 0 = 0, which is at most half of the length of the subset.
# - The sum of the 1st column is 1 + 0 = 1, which is at most half of the length of the subset.
# - The sum of the 2nd column is 1 + 0 = 1, which is at most half of the length of the subset.
# - The sum of the 3rd column is 0 + 1 = 1, which is at most half of the length of the subset.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m <= 104
# 	1 <= n <= 5
# 	grid[i][j] is either 0 or 1.
#

class Solution(object):
    def goodSubsetofBinaryMatrix(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict

        n = len(grid[0])
        pattern_to_rows = defaultdict(list)

        for i, row in enumerate(grid):
            pattern = tuple(row)
            pattern_to_rows[pattern].append(i)

        # Check for single row patterns with all 0s
        zero_pattern = tuple([0] * n)
        if zero_pattern in pattern_to_rows:
            return [pattern_to_rows[zero_pattern][0]]

        patterns = list(pattern_to_rows.keys())

        # Check for pairs of patterns that complement each other
        for i in range(len(patterns)):
            for j in range(i + 1, len(patterns)):
                p1 = patterns[i]
                p2 = patterns[j]
                if all(p1[k] + p2[k] <= 1 for k in range(n)):
                    return [pattern_to_rows[p1][0], pattern_to_rows[p2][0]]

        return []