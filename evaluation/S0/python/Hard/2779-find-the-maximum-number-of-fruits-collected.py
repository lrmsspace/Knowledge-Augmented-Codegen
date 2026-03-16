# Source: https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/   |   Difficulty: Hard
#
# Problem Description:
# There is a game dungeon comprised of n x n rooms arranged in a grid.
#
# You are given a 2D array fruits of size n x n, where fruits[i][j] represents the number of fruits in the room (i, j). Three children will play in the game dungeon, with initial positions at the corner rooms (0, 0), (0, n - 1), and (n - 1, 0).
#
# The children will make exactly n - 1 moves according to the following rules to reach the room (n - 1, n - 1):
#
#
# 	The child starting from (0, 0) must move from their current room (i, j) to one of the rooms (i + 1, j + 1), (i + 1, j), and (i, j + 1) if the target room exists.
# 	The child starting from (0, n - 1) must move from their current room (i, j) to one of the rooms (i + 1, j - 1), (i + 1, j), and (i + 1, j + 1) if the target room exists.
# 	The child starting from (n - 1, 0) must move from their current room (i, j) to one of the rooms (i - 1, j + 1), (i, j + 1), and (i + 1, j + 1) if the target room exists.
#
#
# When a child enters a room, they will collect all the fruits there. If two or more children enter the same room, only one child will collect the fruits, and the room will be emptied after they leave.
#
# Return the maximum number of fruits the children can collect from the dungeon.
#
# Example:
# Input: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]
#
# Output: 100
#
# Explanation:
#
#
#
# In this example:
#
#
# 	The 1st child (green) moves on the path (0,0) -> (1,1) -> (2,2) -> (3, 3).
# 	The 2nd child (red) moves on the path (0,3) -> (1,2) -> (2,3) -> (3, 3).
# 	The 3rd child (blue) moves on the path (3,0) -> (3,1) -> (3,2) -> (3, 3).
#
#
# In total they collect 1 + 6 + 11 + 16 + 4 + 8 + 12 + 13 + 14 + 15 = 100 fruits.
#
# Constraints:
# 2 <= n == fruits.length == fruits[i].length <= 1000
# 	0 <= fruits[i][j] <= 1000
#

class Solution(object):
    def maxCollectedFruits(self, fruits):
        """
        :type fruits: List[List[int]]
        :rtype: int
        """
        n = len(fruits)
        dp = [[[-1] * n for _ in range(n)] for _ in range(n)]
        dp[0][0][n - 1] = fruits[0][0] + fruits[0][n - 1] if n > 1 else fruits[0][0]

        for step in range(1, n):
            for x1 in range(max(0, step - (n - 1)), min(n, step + 1)):
                y1 = step - x1
                if y1 < 0 or y1 >= n:
                    continue
                for x2 in range(max(0, step - (n - 1)), min(n, step + 1)):
                    y2 = (n - 1 - step) + x2
                    if y2 < 0 or y2 >= n:
                        continue
                    for x3 in range(max(0, (n - 1) - step), min(n, (n - 1) - step + 1)):
                        y3 = step - (n - 1 - x3)
                        if y3 < 0 or y3 >= n:
                            continue

                        max_prev = -1
                        for dx1 in [0, -1]:
                            for dx2 in [0, -1]:
                                for dx3 in [0, 1]:
                                    px1, py1 = x1 + dx1, y1 - (step - (x1 + dx1))
                                    px2, py2 = x2 + dx2, y2 - (step - (x2 + dx2))
                                    px3, py3 = x3 + dx3, y3 - ((n - 1) - (x3 + dx3))
                                    if 0 <= px1 < n and 0 <= py1 < n and 0 <= px2 < n and 0 <= py2 < n and 0 <= px3 < n and 0 <= py3 < n:
                                        if dp[px1][px2][px3] != -1:
                                            max_prev = max(max_prev, dp[px1][px2][px3])
                        if max_prev == -1:
                            continue
                        collected = fruits[x1][y1]
                        if (x2, y2) != (x1, y1):
                            collected += fruits[x2][y2]
                        if (x3, y3) != (x1, y1) and (
                            x3, y3) != (x2, y2):
                            collected += fruits[x3][y3]             
                        dp[x1][x2][x3] = max_prev + collected
        return dp[n - 1][n - 1][0]  