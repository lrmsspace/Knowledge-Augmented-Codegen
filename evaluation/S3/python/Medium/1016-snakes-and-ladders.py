# Source: https://leetcode.com/problems/snakes-and-ladders/   |   Difficulty: Medium
#
# Problem Description:
# You are given an n x n integer matrix board where the cells are labeled from 1 to n2 in a Boustrophedon style starting from the bottom left of the board (i.e. board[n - 1][0]) and alternating direction each row.
#
# You start on square 1 of the board. In each move, starting from square curr, do the following:
#
#
# 	Choose a destination square next with a label in the range [curr + 1, min(curr + 6, n2)].
#
# 	
# 		This choice simulates the result of a standard 6-sided die roll: i.e., there are always at most 6 destinations, regardless of the size of the board.
# 	
# 	
# 	If next has a snake or ladder, you must move to the destination of that snake or ladder. Otherwise, you move to next.
# 	The game ends when you reach the square n2.
#
#
# A board square on row r and column c has a snake or ladder if board[r][c] != -1. The destination of that snake or ladder is board[r][c]. Squares 1 and n2 are not the starting points of any snake or ladder.
#
# Note that you only take a snake or ladder at most once per dice roll. If the destination to a snake or ladder is the start of another snake or ladder, you do not follow the subsequent snake or ladder.
#
#
# 	For example, suppose the board is [[-1,4],[-1,3]], and on the first move, your destination square is 2. You follow the ladder to square 3, but do not follow the subsequent ladder to 4.
#
#
# Return the least number of dice rolls required to reach the square n2. If it is not possible to reach the square, return -1.
#
# Example:
# Input: board = [[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
# Output: 4
# Explanation: 
# In the beginning, you start at square 1 (at row 5, column 0).
# You decide to move to square 2 and must take the ladder to square 15.
# You then decide to move to square 17 and must take the snake to square 13.
# You then decide to move to square 14 and must take the ladder to square 35.
# You then decide to move to square 36, ending the game.
# This is the lowest possible number of moves to reach the last square, so return 4.
#
# Constraints:
# n == board.length == board[i].length
# 	2 <= n <= 20
# 	board[i][j] is either -1 or in the range [1, n2].
# 	The squares labeled 1 and n2 are not the starting points of any snake or ladder.
#
# Helpful references (internal KB):
# - Gray code (number, simulation)
#   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
#   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
#   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
#   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
#   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
# - Josephus Problem (number, recursion, counting)
#   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
#   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
#   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
#   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
#   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
# - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
#   • When to use: Use when you need to represent all positive irreducible fractions in a structured tree or efficiently search for a specific fraction. It's also useful for generating Farey sequences or understanding rational number properties.
#   • Idea: The Stern-Brocot tree is an infinite binary tree containing every positive irreducible fraction exactly once, ordered by value. Searching for a fraction or generating parts of the tree typically involves a logarithmic number of steps relative to the sum of the numerator and denominator, making it efficient for O(log(x+y)) operations.
#   • Invariants: For any node m/n, all fractions in its left subtree are strictly less than m/n.; For any node m/n, all fractions in its right subtree are strictly greater than m/n.
#   • Tips: The mediant of a/b and c/d is (a+c)/(b+d), which is always irreducible if a/b and c/d are.; All fractions in the Stern-Brocot tree are inherently irreducible.
#   • Pitfalls: Integer overflow when calculating mediants if numerators or denominators are very large.; Incorrectly handling the initial 'infinite' fractions (0/1 and 1/0) as boundary conditions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def snakesAndLadders(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        n = len(board)
        target = n * n
        visited = set()
        queue = [(1, 0)]  # (current square, moves)

        while queue:
            curr, moves = queue.pop(0)
            if curr == target:
                return moves

            for next_square in range(curr + 1, min(curr + 6, target) + 1):
                r, c = divmod(next_square - 1, n)
                r = n - 1 - r
                if board[r][c] != -1:
                    next_square = board[r][c]

                if next_square not in visited:
                    visited.add(next_square)
                    queue.append((next_square, moves + 1))

        return -1