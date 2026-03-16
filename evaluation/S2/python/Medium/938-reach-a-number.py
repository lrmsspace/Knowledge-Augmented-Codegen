# Source: https://leetcode.com/problems/reach-a-number/   |   Difficulty: Medium
#
# Problem Description:
# You are standing at position 0 on an infinite number line. There is a destination at position target.
#
# You can make some number of moves numMoves so that:
#
#
# 	On each move, you can either go left or right.
# 	During the ith move (starting from i == 1 to i == numMoves), you take i steps in the chosen direction.
#
#
# Given the integer target, return the minimum number of moves required (i.e., the minimum numMoves) to reach the destination.
#
# Example:
# Input: target = 2
# Output: 3
# Explanation:
# On the 1st move, we step from 0 to 1 (1 step).
# On the 2nd move, we step from 1 to -1 (2 steps).
# On the 3rd move, we step from -1 to 2 (3 steps).
#
# Constraints:
# -109 <= target <= 109
# 	target != 0
#
# Helpful references (internal KB):
# - Manhattan Distance (geometry, number, coordinate-compress)
#   • When to use: Use when calculating distance between two points on a grid where movement is restricted to horizontal and vertical directions. It is also useful for problems involving maximizing or minimizing sums of absolute coordinate differences, often transformable to Chebyshev distance.
#   • Idea: Manhattan distance measures the sum of absolute differences of Cartesian coordinates between two points. It can be transformed into a Chebyshev distance problem by rotating coordinates, enabling efficient O(N) max/min distance calculations.
#   • Invariants: For any two points P1=(x1, y1) and P2=(x2, y2), the Manhattan distance is always non-negative.; The transformed points P1'=(x1+y1, y1-x1) and P2'=(x2+y2, y2-x2) satisfy Chebyshev(P1', P2') == Manhattan(P1, P2).
#   • Tips: Consider transforming to Chebyshev distance for max/min distance problems.; The transformation involves rotating coordinates: (x, y) -> (x+y, y-x).
#   • Pitfalls: Confusing with Euclidean distance, which allows diagonal movement.; Incorrectly applying coordinate transformation (e.g., wrong signs).
# - Binary search (interval, number, binary-search-answer, enumeration)
#   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
#   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
#   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
#   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
#   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def reachNumber(self, target):
        """
        :type target: int
        :rtype: int
        """
        target = abs(target)
        step = 0
        while True:
            step += 1
            sum_so_far = step * (step + 1) // 2
            if sum_so_far >= target and (sum_so_far - target) % 2 == 0:
                return step