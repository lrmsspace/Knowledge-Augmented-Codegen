# Source: https://leetcode.com/problems/number-of-paths-with-max-score/   |   Difficulty: Hard
#
# Problem Description:
# You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.
#
# You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.
#
# Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.
#
# In case there is no path, return [0, 0].
#
# Example:
# Input: board = ["E23","2X2","12S"]
# Output: [7,1]
#
# Constraints:
# 2 <= board.length == board[i].length <= 100
#

class Solution(object):
    def pathsWithMaxScore(self, board):
        """
        :type board: List[str]
        :rtype: List[int]
        """
        MOD = 10**9 + 7
        n = len(board)
        dp = [[(0, 0) for _ in range(n)] for _ in range(n)]
        dp[n-1][n-1] = (0, 1)

        for i in range(n-1, -1, -1):
            for j in range(n-1, -1, -1):
                if board[i][j] == 'X' or (i == n-1 and j == n-1):
                    continue

                max_score = -1
                path_count = 0

                for di, dj in [(-1, 0), (0, -1), (-1, -1)]:
                    ni, nj = i + di, j + dj
                    if 0 <= ni < n and 0 <= nj < n:
                        score, count = dp[ni][nj]
                        if score > max_score:
                            max_score = score
                            path_count = count
                        elif score == max_score:
                            path_count = (path_count + count) % MOD

                if max_score == -1:
                    dp[i][j] = (0, 0)
                else:
                    cell_value = 0 if board[i][j] in 'ES' else int(board[i][j])
                    dp[i][j] = (max_score + cell_value, path_count)

        return list(dp[0][0])