# Source: https://leetcode.com/problems/24-game/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array cards of length 4. You have four cards, each containing a number in the range [1, 9]. You should arrange the numbers on these cards in a mathematical expression using the operators ['+', '-', '*', '/'] and the parentheses '(' and ')' to get the value 24.
#
# You are restricted with the following rules:
#
#
# 	The division operator '/' represents real division, not integer division.
#
# 	
# 		For example, 4 / (1 - 2 / 3) = 4 / (1 / 3) = 12.
# 	
# 	
# 	Every operation done is between two numbers. In particular, we cannot use '-' as a unary operator.
# 	
# 		For example, if cards = [1, 1, 1, 1], the expression "-1 - 1 - 1 - 1" is not allowed.
# 	
# 	
# 	You cannot concatenate numbers together
# 	
# 		For example, if cards = [1, 2, 1, 2], the expression "12 + 12" is not valid.
# 	
# 	
#
#
# Return true if you can get such expression that evaluates to 24, and false otherwise.
#
# Example:
# Input: cards = [4,1,8,7]
# Output: true
# Explanation: (8-4) * (7-1) = 24
#
# Constraints:
# cards.length == 4
# 	1 <= cards[i] <= 9
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Generating all K-combinations (bitset, recursion, enumeration)
#   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
#   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
#   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
#   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
#   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
# - Backtracking Algorithm (graph, backtracking, recursion, dfs)
#   • When to use: Used when exploring multiple possibilities to find a solution incrementally, often involving undoing choices if they lead to a dead end.
#   • Idea: Backtracking is a problem-solving technique that incrementally builds a solution by trying options and undoing them upon reaching a dead end. It typically explores a search space in a depth-first manner, often resulting in exponential time complexity.
#   • Invariants: The current partial solution is valid up to the current decision point.; All choices made to reach the current state can be systematically undone.
#   • Tips: Define clear base cases for recursive termination.; Identify decision points and available choices at each step.
#   • Pitfalls: Forgetting to undo changes (backtrack) after exploring a path.; Incorrectly defining base cases, leading to infinite recursion or wrong results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def judgePoint24(self, cards):
        """
        :type cards: List[int]
        :rtype: bool
        """
        from itertools import permutations, product

        def apply_op(a, b, op):
            if op == '+':
                return a + b
            elif op == '-':
                return a - b
            elif op == '*':
                return a * b
            elif op == '/':
                if b == 0:
                    return None
                return a / b

        ops = ['+', '-', '*', '/']
        for nums in permutations(cards):
            for op_combo in product(ops, repeat=3):
                # Check all parenthesizations
                if abs(apply_op(apply_op(apply_op(nums[0], nums[1], op_combo[0]), nums[2], op_combo[1]), nums[3], op_combo[2]) - 24) < 1e-6:
                    return True
                if abs(apply_op(apply_op(nums[0], apply_op(nums[1], nums[2], op_combo[1]), op_combo[0]), nums[3], op_combo[2]) - 24) < 1e-6:
                    return True
                if abs(apply_op(nums[0], apply_op(apply_op(nums[1], nums[2], op_combo[1]), nums[3], op_combo[2]), op_combo[0]) - 24) < 1e-6:
                    return True
                if abs(apply_op(nums[0], apply_op(nums[1], apply_op(nums[2], nums[3], op_combo[2]), op_combo[1]), op_combo[0]) - 24) < 1e-6:
                    return True
                if abs(apply_op(apply_op(nums[0], nums[1], op_combo[0]), apply_op(nums[2], nums[3], op_combo[2]), op_combo[1]) - 24) < 1e-6:
                    return True

        return False