# Source: https://leetcode.com/problems/building-boxes/   |   Difficulty: Hard
#
# Problem Description:
# You have a cubic storeroom where the width, length, and height of the room are all equal to n units. You are asked to place n boxes in this room where each box is a cube of unit side length. There are however some rules to placing the boxes:
#
#
# 	You can place the boxes anywhere on the floor.
# 	If box x is placed on top of the box y, then each side of the four vertical sides of the box y must either be adjacent to another box or to a wall.
#
#
# Given an integer n, return the minimum possible number of boxes touching the floor.
#
# Example:
# Input: n = 3
# Output: 3
# Explanation: The figure above is for the placement of the three boxes.
# These boxes are placed in the corner of the room, where the corner is on the left side.
#
# Constraints:
# 1 <= n <= 109
#
# Helpful references (internal KB):
# -  
# Kth order statistic in O(N) (array, enumeration)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
#   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
#   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
#   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
# - Binomial Coefficients (number, enumeration)
#   • When to use: Use when needing to calculate multiple binomial coefficients or when a single coefficient is required and N and K are not excessively large, allowing for table precomputation.
#   • Idea: This method computes binomial coefficients C(n, k) using Pascal's recurrence relation C(n, k) = C(n-1, k-1) + C(n-1, k), typically building a table. It has a time complexity of O(N*K) or O(N^2) for building the full triangle up to N.
#   • Invariants: C[i][0] is always 1 for any row i.; C[i][i] is always 1 for any row i.
#   • Tips: Intermediate results for Pascal's Triangle never exceed the final answer, simplifying overflow checks if not using modular arithmetic.; Each new table element requires only one addition, making it computationally efficient per element.
#   • Pitfalls: Building the entire Pascal's Triangle for a single C(N, K) can be slow for large N and K, as it computes many unnecessary values.; Directly computing C(N, K) using factorials can lead to overflow issues for large N, even if the final result fits.
# - Josephus Problem (number, recursion, counting)
#   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
#   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
#   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
#   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
#   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumBoxes(self, n):
        """
        :type n: int
        :rtype: int
        """
        # The number of boxes in a complete k-layer pyramid is given by the formula: k*(k+1)*(k+2)/6
        # We need to find the largest k such that k*(k+1)*(k+2)/6 <= n
        k = 0
        while (k * (k + 1) * (k + 2)) // 6 <= n:
            k += 1
        k -= 1  # Decrement to get the last valid k

        # Calculate the number of boxes in the complete k-layer pyramid
        boxes_in_pyramid = (k * (k + 1) * (k + 2)) // 6

        # Remaining boxes after filling the complete pyramid
        remaining_boxes = n - boxes_in_pyramid

        # The next layer (k+1) can hold at most (k+1) boxes on the floor
        additional_boxes_on_floor = min(remaining_boxes, k + 1)

        return (k * (k + 1)) // 2 + additional_boxes_on_floor