# Source: https://leetcode.com/problems/happy-number/   |   Difficulty: Easy
#
# Problem Description:
# Write an algorithm to determine if a number n is happy.
#
# A happy number is a number defined by the following process:
#
#
# 	Starting with any positive integer, replace the number by the sum of the squares of its digits.
# 	Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
# 	Those numbers for which this process ends in 1 are happy.
#
#
# Return true if n is a happy number, and false if not.
#
# Example:
# Input: n = 19
# Output: true
# Explanation:
# 12 + 92 = 82
# 82 + 22 = 68
# 62 + 82 = 100
# 12 + 02 + 02 = 1
#
# Constraints:
# 1 <= n <= 231 - 1
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Number of divisors / sum of divisors (number, counting, enumeration)
#   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
#   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
#   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
#   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
#   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
# - Digit DP (array, number, digit-dp)
#   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
#   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
#   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
#   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
#   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isHappy(self, n):
        """
        :type n: int
        :rtype: bool
        """
        def get_next(n):
            total_sum = 0
            while n > 0:
                n, digit = divmod(n, 10)
                total_sum += digit ** 2
            return total_sum
        seen = set()
        while n != 1 and n not in seen:
            seen.add(n)
            n = get_next(n)
        return n == 1