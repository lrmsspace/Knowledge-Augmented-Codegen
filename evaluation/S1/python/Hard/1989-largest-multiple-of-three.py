# Source: https://leetcode.com/problems/largest-multiple-of-three/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of digits digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order. If there is no answer return an empty string.
#
# Since the answer may not fit in an integer data type, return the answer as a string. Note that the returning answer must not contain unnecessary leading zeros.
#
# Example:
# Input: digits = [8,1,9]
# Output: "981"
#
# Constraints:
# 1 <= digits.length <= 104
# 	0 <= digits[i] <= 9
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
# - Linear Diophantine Equation (number, greedy)
#   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
#   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
#   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
#   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
#   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def largestMultipleOfThree(self, digits):
        """
        :type digits: List[int]
        :rtype: str
        """
        count = [0] * 10
        for d in digits:
            count[d] += 1

        total_sum = sum(d * count[d] for d in range(10))
        if total_sum % 3 == 1:
            if not self.remove_digits(count, [1, 4, 7]):
                self.remove_digits(count, [2, 5, 8], 2)
        elif total_sum % 3 == 2:
            if not self.remove_digits(count, [2, 5, 8]):
                self.remove_digits(count, [1, 4, 7], 2)

        result = []
        for d in range(9, -1, -1):
            result.extend(str(d) * count[d])

        return ''.join(result) if result and result[0] != '0' else '0'