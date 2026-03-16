# Source: https://leetcode.com/problems/distribute-money-to-maximum-children/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer money denoting the amount of money (in dollars) that you have and another integer children denoting the number of children that you must distribute the money to.
#
# You have to distribute the money according to the following rules:
#
#
# 	All money must be distributed.
# 	Everyone must receive at least 1 dollar.
# 	Nobody receives 4 dollars.
#
#
# Return the maximum number of children who may receive exactly 8 dollars if you distribute the money according to the aforementioned rules. If there is no way to distribute the money, return -1.
#
# Example:
# Input: money = 20, children = 3
# Output: 1
# Explanation: 
# The maximum number of children with 8 dollars will be 1. One of the ways to distribute the money is:
# - 8 dollars to the first child.
# - 9 dollars to the second child. 
# - 3 dollars to the third child.
# It can be proven that no distribution exists such that number of children getting 8 dollars is greater than 1.
#
# Constraints:
# 1 <= money <= 200
# 	2 <= children <= 30
#
# Helpful references (internal KB):
# - Linear Diophantine Equation (number, greedy)
#   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
#   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
#   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
#   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
#   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
# - Stars and bars (number, counting)
#   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative integer solutions to a linear equation. It is also applicable for problems with lower bounds on variables.
#   • Idea: Stars and bars is a combinatorial technique used to count the number of ways to place 'n' identical items into 'k' distinct bins, or equivalently, to find the number of non-negative integer solutions to x1 + ... + xk = n.
#   • Invariants: The total number of 'stars' (items) remains constant throughout any transformation.; The number of 'bars' (separators) is always one less than the number of bins (variables).
#   • Tips: Visualize items as 'stars' and separators as 'bars' to understand the arrangement.; Transform problems with lower bounds (x_i >= a_i) into non-negative solutions (x_i' >= 0).
#   • Pitfalls: Confusing identical items with distinct items, which requires a different counting method.; Incorrectly applying the formula when variables have lower bounds other than zero without transformation.
# - Josephus Problem (number, simulation, recursion)
#   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
#   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
#   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
#   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
#   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def distMoney(self, money, children):
        """
        :type money: int
        :type children: int
        :rtype: int
        """
        max_eight = money // 8
        if max_eight > children:
            return children
        remaining_money = money - max_eight * 8
        remaining_children = children - max_eight
        if remaining_children == 0:
            if remaining_money == 0:
                return max_eight
            else:
                return -1
        if remaining_money >= remaining_children:
            if remaining_money == remaining_children and remaining_children == 1:
                return max_eight - 1
            return max_eight
        else:
            return max_eight - 1