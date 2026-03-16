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
# - Finding the equation of a line for a segment (geometry, number, enumeration)
#   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
#   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
#   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
#   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
#   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
# - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
#   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
#   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
#   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
#   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
#   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
#   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
#   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
#   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
#   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
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
        row, col = 0, 0
        
        # Define the movement directions for each command
        directions = {
            "UP": (-1, 0),
            "RIGHT": (0, 1),
            "DOWN": (1, 0),
            "LEFT": (0, -1)
        }
        
        # Process each command to update the snake's position
        for command in commands:
            dr, dc = directions[command]
            row += dr
            col += dc
            
            # Ensure the snake stays within the grid boundaries
            row = max(0, min(n - 1, row))
            col = max(0, min(n - 1, col))
        
        # Calculate the final cell position based on row and column
        return row * n + col