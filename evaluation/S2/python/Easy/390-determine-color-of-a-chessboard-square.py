# Source: https://leetcode.com/problems/determine-color-of-a-chessboard-square/   |   Difficulty: Easy
#
# Problem Description:
# You are given coordinates, a string that represents the coordinates of a square of the chessboard. Below is a chessboard for your reference.
#
#
#
# Return true if the square is white, and false if the square is black.
#
# The coordinate will always represent a valid chessboard square. The coordinate will always have the letter first, and the number second.
#
# Example:
# Input: coordinates = "a1"
# Output: false
# Explanation: From the chessboard above, the square with coordinates "a1" is black, so return false.
#
# Constraints:
# coordinates.length == 2
# 	'a' <= coordinates[0] <= 'h'
# 	'1' <= coordinates[1] <= '8'
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def squareIsWhite(self, coordinates):
        """
        :type coordinates: str
        :rtype: bool
        """
        # The color of the square can be determined by the sum of the row and column indices.
        # If the sum is even, the square is black; if it's odd, the square is white.
        
        # Convert the letter to a number (a=1, b=2, ..., h=8)
        column = ord(coordinates[0]) - ord('a') + 1
        # Convert the number character to an integer
        row = int(coordinates[1])
        
        # Determine the color based on the parity of the sum of row and column
        return (row + column) % 2 == 1