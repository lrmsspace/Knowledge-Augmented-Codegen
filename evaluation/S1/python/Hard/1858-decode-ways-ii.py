# Source: https://leetcode.com/problems/decode-ways-ii/   |   Difficulty: Hard
#
# Problem Description:
# A message containing letters from A-Z can be encoded into numbers using the following mapping:
#
#
# 'A' -> "1"
# 'B' -> "2"
# ...
# 'Z' -> "26"
#
#
# To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped into:
#
#
# 	"AAJF" with the grouping (1 1 10 6)
# 	"KJF" with the grouping (11 10 6)
#
#
# Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is different from "06".
#
# In addition to the mapping above, an encoded message may contain the '*' character, which can represent any digit from '1' to '9' ('0' is excluded). For example, the encoded message "1*" may represent any of the encoded messages "11", "12", "13", "14", "15", "16", "17", "18", or "19". Decoding "1*" is equivalent to decoding any of the encoded messages it can represent.
#
# Given a string s consisting of digits and '*' characters, return the number of ways to decode it.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: s = "*"
# Output: 9
# Explanation: The encoded message can represent any of the encoded messages "1", "2", "3", "4", "5", "6", "7", "8", or "9".
# Each of these can be decoded to the strings "A", "B", "C", "D", "E", "F", "G", "H", and "I" respectively.
# Hence, there are a total of 9 ways to decode "*".
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is a digit or '*'.
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Modular Multiplicative Inverse (array, number, dp-1d)
#   • When to use: Use when division operations are required in modular arithmetic, especially for combinatorics or probability problems under a modulus. It's crucial for precomputing inverses efficiently for a range of numbers.
#   • Idea: Calculates the modular multiplicative inverse of a number 'a' modulo 'm', which is an integer 'x' such that (a * x) % m == 1. When precomputing inverses for a range [1, N], a linear time O(N) dynamic programming approach can be used.
#   • Invariants: For all k in [1, i-1], inv[k] correctly stores k^(-1) % m.; inv[i] is computed using previously calculated inv[m % i].
#   • Tips: For prime modulus 'm', a^(m-2) % m (Fermat's Little Theorem) is efficient for a single inverse.; The Extended Euclidean Algorithm works for any 'm' if gcd(a, m) = 1.
#   • Pitfalls: A modular inverse only exists if gcd(a, m) == 1.; Fermat's Little Theorem is only applicable when the modulus 'm' is prime.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numDecodings(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)

        # dp[i] will store the number of ways to decode the substring s[:i]
        dp = [0] * (n + 1)
        dp[0] = 1  # Base case: there's one way to decode an empty string

        # Handle the first character
        if s[0] == '0':
            return 0
        elif s[0] == '*':
            dp[1] = 9  # '*' can represent digits '1' to '9'
        else:
            dp[1] = 1  # Any non-zero digit can be decoded as a single character

        for i in range(2, n + 1):
            current_char = s[i - 1]
            prev_char = s[i - 2]

            # Single character decoding
            if current_char == '*':
                dp[i] += 9 * dp[i - 1]  # '*' can be '1' to '9'
            elif current_char != '0':
                dp[i] += dp[i - 1]  # Non-zero digit can be decoded as a single character

            # Two character decoding
            if prev_char == '*':
                if current_char == '*':
                    dp[i] += 15 * dp[i - 2]  # '**' can represent '11' to '19' and '21' to '26'
                elif current_char <= '6':
                    dp[i] += 2 * dp[i - 2]  # '*x' can represent '1x' and '2x'
                else:
                    dp[i] += dp[i - 2]  # '*x' can only represent '1x'
            elif prev_char == '1':
                if current_char == '*':
                    dp[i] += 9 * dp[i - 2]  # '1*' can represent '11' to '19'
                else:
                    dp[i] += dp[i - 2]  # '1x' can represent a valid two-digit number
            elif prev_char == '2':
                if current_char == '*':
                    dp[i] += 6 * dp[i - 2]  # '2*' can represent '21' to '26'
                elif current_char <= '6':
                    dp[i] += dp[i - 2]  # '2x' can represent a valid two-digit number
            # No need to handle cases where prev_char > '2' since they can't form valid two-digit numbers
            dp[i] %= MOD
        return dp[n] % MOD  