# Source: https://leetcode.com/problems/count-stepping-numbers-in-range/   |   Difficulty: Hard
#
# Problem Description:
# Given two positive integers low and high represented as strings, find the count of stepping numbers in the inclusive range [low, high].
#
# A stepping number is an integer such that all of its adjacent digits have an absolute difference of exactly 1.
#
# Return an integer denoting the count of stepping numbers in the inclusive range [low, high]. 
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Note: A stepping number should not have a leading zero.
#
# Example:
# Input: low = "1", high = "11"
# Output: 10
# Explanation: The stepping numbers in the range [1,11] are 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10. There are a total of 10 stepping numbers in the range. Hence, the output is 10.
#
# Constraints:
# 1 <= int(low) <= int(high) < 10100
# 	1 <= low.length, high.length <= 100
# 	low and high consist of only digits.
# 	low and high don't have any leading zeros.
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
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
    def countSteppingNumbers(self, low, high):
        """
        :type low: str
        :type high: str
        :rtype: int
        """
        MOD = 10**9 + 7

        def count_stepping_numbers(num_str):
            digits = list(map(int, num_str))
            n = len(digits)
            memo = {}

            def dp(idx, prev_digit, is_tight, is_leading_zero):
                if idx == n:
                    return 1

                if (idx, prev_digit, is_tight, is_leading_zero) in memo:
                    return memo[(idx, prev_digit, is_tight, is_leading_zero)]

                limit = digits[idx] if is_tight else 9
                total_count = 0

                for digit in range(0, limit + 1):
                    if is_leading_zero and digit == 0:
                        total_count += dp(idx + 1, -1, is_tight and digit == limit, True)
                    elif prev_digit == -1 or abs(digit - prev_digit) == 1:
                        total_count += dp(idx + 1, digit, is_tight and digit == limit, False)

                memo[(idx, prev_digit, is_tight, is_leading_zero)] = total_count % MOD
                return memo[(idx, prev_digit, is_tight, is_leading_zero)]

            return dp(0, -1, True, True)

        low_count = count_stepping_numbers(low)
        high_count = count_stepping_numbers(high)
        result = (high_count - low_count) % MOD

        # Check if low itself is a stepping number
        if self.is_stepping_number(low):
            result = (result + 1) % MOD

        return result