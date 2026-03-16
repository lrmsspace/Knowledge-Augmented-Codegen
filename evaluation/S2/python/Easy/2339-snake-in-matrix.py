# Source: https://leetcode.com/problems/snake-in-matrix/   |   Difficulty: Easy
#
# Problem Description:
# There is a snake in an n x n matrix grid and can move in four possible directions. Each cell in the grid is identified by the position: grid[i][j] = (i * n) + j.
#
# The snake starts at cell 0 and follows a sequence of commands.
#
# You are given an integer n representing the size of the grid and an array of strings commands where each command[i] is either "UP", "RIGHT", "DOWN", and "LEFT". It's guaranteed that the snake will remain within the grid boundaries throughout its movement.
#
# Return the position of the final cell where the snake ends up after executing commands.
#
# Example:
# Input: n = 2, commands = ["RIGHT","DOWN"]
#
# Output: 3
#
# Explanation:
#
#
#
# 	
# 		
# 			0
# 			1
# 		
# 		
# 			2
# 			3
# 		
# 	
#
#
#
# 	
# 		
# 			0
# 			1
# 		
# 		
# 			2
# 			3
# 		
# 	
#
#
#
# 	
# 		
# 			0
# 			1
# 		
# 		
# 			2
# 			3
#
# Constraints:
# 2 <= n <= 10
# 	1 <= commands.length <= 100
# 	commands consists only of "UP", "RIGHT", "DOWN", and "LEFT".
# 	The input is generated such the snake will not move outside of the boundaries.
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
    def finalPositionOfSnake(self, n, commands):
        """
        :type n: int
        :type commands: List[str]
        :rtype: int
        """
        # Initialize the starting position of the snake
        x, y = 0, 0
        
        # Define the movement directions for each command
        directions = {
            "UP": (-1, 0),
            "RIGHT": (0, 1),
            "DOWN": (1, 0),
            "LEFT": (0, -1)
        }
        
        # Process each command
        for command in commands:
            dx, dy = directions[command]
            x += dx
            y += dy
            
            # Ensure the snake stays within the grid boundaries
            x = max(0, min(n - 1, x))
            y = max(0, min(n - 1, y))
        
        # Calculate the final cell position
        return x * n + y