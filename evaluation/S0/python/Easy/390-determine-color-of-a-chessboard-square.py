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

class Solution(object):
    def squareIsWhite(self, coordinates):
        """
        :type coordinates: str
        :rtype: bool
        """
        col = ord(coordinates[0]) - ord('a') + 1
        row = int(coordinates[1])
        
        return (col + row) % 2 == 1