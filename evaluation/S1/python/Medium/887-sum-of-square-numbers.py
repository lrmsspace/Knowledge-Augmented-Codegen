# Source: https://leetcode.com/problems/sum-of-square-numbers/   |   Difficulty: Medium
#
# Problem Description:
# Given a non-negative integer c, decide whether there're two integers a and b such that a2 + b2 = c.
#
# Example:
# Input: c = 5
# Output: true
# Explanation: 1 * 1 + 2 * 2 = 5
#
# Constraints:
# 0 <= c <= 231 - 1
#
# Helpful references (internal KB):
# - Circle-Circle Intersection (geometry, number, simulation, enumeration)
#   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
#   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
#   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
#   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
#   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
# - Integer factorization (number, randomized, gcd, two-pointers)
#   • When to use: Used to find non-trivial factors of a large composite number, especially when trial division is too slow. It's effective for numbers with relatively small prime factors or factors whose predecessors are powersmooth.
#   • Idea: Integer factorization algorithms like Pollard's p-1 and Pollard's Rho probabilistically find factors of composite numbers. Pollard's p-1 leverages modular exponentiation and GCD, while Pollard's Rho uses cycle detection on a pseudo-random sequence.
#   • Invariants: For Pollard's p-1, a^M mod p remains 1 for any prime factor p where p-1 divides M.; For Pollard's p-1, M is always a multiple of lcm(1, 2, ..., B) for the current B.
#   • Tips: Pollard's p-1 is effective when p-1 is B-powersmooth for a factor p.; Pollard's Rho is generally more robust for arbitrary composite numbers.
#   • Pitfalls: Algorithms are probabilistic; no guarantee of finding a factor.; May return n (the number itself) or 1, requiring retry with different parameters.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def judgeSquareSum(self, c):
        """
        :type c: int
        :rtype: bool
        """
        left = 0
        right = int(c**0.5)
        
        while left <= right:
            current_sum = left * left + right * right
            if current_sum == c:
                return True
            elif current_sum < c:
                left += 1
            else:
                right -= 1
        
        return False