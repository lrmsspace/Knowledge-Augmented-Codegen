# Source: https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/   |   Difficulty: Hard
#
# Problem Description:
# Given a rectangle of size n x m, return the minimum number of integer-sided squares that tile the rectangle.
#
# Example:
# Input: n = 2, m = 3
# Output: 3
# Explanation: 3 squares are necessary to cover the rectangle.
# 2 (squares of 1x1)
# 1 (square of 2x2)
#
# Constraints:
# 1 <= n, m <= 13
#

class Solution(object):
    def tilingRectangle(self, n, m):
        """
        :type n: int
        :type m: int
        :rtype: int
        """
        self.res = n * m
        def backtrack(heights, count):
            if count >= self.res:
                return
            if all(h == m for h in heights):
                self.res = min(self.res, count)
                return
            min_h = min(heights)
            idx = heights.index(min_h)
            for size in range(min(m - min_h, n - idx), 0, -1):
                if all(heights[i] == min_h for i in range(idx, idx + size)):
                    for i in range(idx, idx + size):
                        heights[i] += size
                    backtrack(heights, count + 1)
                    for i in range(idx, idx + size):
                        heights[i] -= size
        backtrack([0] * n, 0)
        return self.res