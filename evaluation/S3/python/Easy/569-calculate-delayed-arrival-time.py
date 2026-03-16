# Source: https://leetcode.com/problems/calculate-delayed-arrival-time/   |   Difficulty: Easy
#
# Problem Description:
# You are given a positive integer arrivalTime denoting the arrival time of a train in hours, and another positive integer delayedTime denoting the amount of delay in hours.
#
# Return the time when the train will arrive at the station.
#
# Note that the time in this problem is in 24-hours format.
#
# Example:
# Input: arrivalTime = 15, delayedTime = 5 
# Output: 20 
# Explanation: Arrival time of the train was 15:00 hours. It is delayed by 5 hours. Now it will reach at 15+5 = 20 (20:00 hours).
#
# Constraints:
# 1 <= arrivaltime < 24
# 	1 <= delayedTime <= 24
#
# Helpful references (internal KB):
# - Josephus Problem (number, simulation, recursion)
#   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
#   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
#   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
#   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
#   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
# - Gray code (number, simulation)
#   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
#   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
#   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
#   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
#   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
# - Gauss method for solving system of linea (matrix, number, simulation)
#   • When to use: Use when solving systems of linear equations, including those over finite fields (modulo p), to find unique, multiple, or no solutions.
#   • Idea: Gauss-Jordan elimination systematically transforms a system of linear equations into an equivalent, simpler form (row echelon or reduced row echelon) using elementary row operations to find solutions. This process typically has a time complexity of O(N^2 * M) for an N x M matrix.
#   • Invariants: After k steps, the first k columns form an identity submatrix (or a column with 1 at pivot and 0s elsewhere) in the upper-left kxk block.; The system of equations represented by the augmented matrix remains equivalent to the original system.
#   • Tips: Always perform row operations on the augmented matrix (A|b) to ensure consistency.; Choose a pivot with the largest absolute value to improve numerical stability and reduce error propagation.
#   • Pitfalls: Division by zero if a pivot element is zero and no suitable row swap is found.; Numerical instability with floating-point numbers if pivots are very small, leading to precision issues.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findDelayedArrivalTime(self, arrivalTime, delayedTime):
        """
        :type arrivalTime: int
        :type delayedTime: int
        :rtype: int
        """
        return (arrivalTime + delayedTime) % 24