# Source: https://leetcode.com/problems/check-if-word-can-be-placed-in-crossword/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n matrix board, representing the current state of a crossword puzzle. The crossword contains lowercase English letters (from solved words), ' ' to represent any empty cells, and '#' to represent any blocked cells.
#
# A word can be placed horizontally (left to right or right to left) or vertically (top to bottom or bottom to top) in the board if:
#
#
# 	It does not occupy a cell containing the character '#'.
# 	The cell each letter is placed in must either be ' ' (empty) or match the letter already on the board.
# 	There must not be any empty cells ' ' or other lowercase letters directly left or right of the word if the word was placed horizontally.
# 	There must not be any empty cells ' ' or other lowercase letters directly above or below the word if the word was placed vertically.
#
#
# Given a string word, return true if word can be placed in board, or false otherwise.
#
# Example:
# Input: board = [["#", " ", "#"], [" ", " ", "#"], ["#", "c", " "]], word = "abc"
# Output: true
# Explanation: The word "abc" can be placed as shown above (top to bottom).
#
# Constraints:
# m == board.length
# 	n == board[i].length
# 	1 <= m * n <= 2 * 105
# 	board[i][j] will be ' ', '#', or a lowercase English letter.
# 	1 <= word.length <= max(m, n)
# 	word will contain only lowercase English letters.
#

class Solution(object):
    def placeWordInCrossword(self, board, word):
        """
        :type board: List[List[str]]
        :type word: str
        :rtype: bool
        """
        def check(line):
            n = len(line)
            m = len(word)
            i = 0
            while i <= n - m:
                if (i > 0 and line[i - 1] != '#') or (i + m < n and line[i + m] != '#'):
                    i += 1
                    continue
                match = True
                for j in range(m):
                    if line[i + j] != ' ' and line[i + j] != word[j]:
                        match = False
                        break
                if match:
                    return True
                i += 1
            return False

        for row in board:
            if check(row) or check(row[::-1]):
                return True

        for col in zip(*board):
            if check(col) or check(col[::-1]):
                return True

        return False