# Source: https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/   |   Difficulty: Hard
#
# Problem Description:
# A parentheses string is a non-empty string consisting only of '(' and ')'. It is valid if any of the following conditions is true:
#
#
# 	It is ().
# 	It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
# 	It can be written as (A), where A is a valid parentheses string.
#
#
# You are given an m x n matrix of parentheses grid. A valid parentheses string path in the grid is a path satisfying all of the following conditions:
#
#
# 	The path starts from the upper left cell (0, 0).
# 	The path ends at the bottom-right cell (m - 1, n - 1).
# 	The path only ever moves down or right.
# 	The resulting parentheses string formed by the path is valid.
#
#
# Return true if there exists a valid parentheses string path in the grid. Otherwise, return false.
#
# Example:
# Input: grid = [["(","(","("],[")","(",")"],["(","(",")"],["(","(",")"]]
# Output: true
# Explanation: The above diagram shows two possible paths that form valid parentheses strings.
# The first path shown results in the valid parentheses string "()(())".
# The second path shown results in the valid parentheses string "((()))".
# Note that there may be other valid parentheses string paths.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 100
# 	grid[i][j] is either '(' or ')'.
#

class Solution(object):
    def hasValidPath(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: bool
        """
        m, n = len(grid), len(grid[0])
        if (m + n - 1) % 2 != 0:
            return False
        
        from collections import defaultdict, deque
        
        dp = [defaultdict(set) for _ in range(m)]
        dp[0][0].add(1 if grid[0][0] == '(' else -1)
        
        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:
                    continue
                current_set = set()
                if i > 0:
                    for count in dp[i-1][j]:
                        if grid[i][j] == '(':
                            current_set.add(count + 1)
                        else:
                            if count > 0:
                                current_set.add(count - 1)
                if j > 0:
                    for count in dp[i][j-1]:
                        if grid[i][j] == '(':
                            current_set.add(count + 1)
                        else:
                            if count > 0:
                                current_set.add(count - 1)
                dp[i][j] = current_set
        
        return 0 in dp[m-1][n-1]